/*
ANTECKNINGAR:
    - Vore kul att bygga upp egna tools som man kan återanvända i andra CLI program
    - hackig GUI och input hantering. Kul att prova goto men måste ju göra riktiga funktioner och överskådligtbart flöde.
    - Speciellt rörigt att ha en rekursiv funktion som huvudsaklig inputhanterare.
    - Kanske hämta lat och long och stadsnamn från apiet själv?

TO DO:
    - Strukturera om
    - Speciellt input hanteringen. Är nu i en rekursiv funktion där även quit logiken ligger och flippar en global variabel.
    - Kanske kan flusha buffern och göra carriage return äm amn inte skriver in sifforr?

NÄSTA STEG:
    - Plocka stadsnamn från geonames listan istället, 36mb textfil men mycket data som kan tas bort. (alla städer med fler än 500 invånare.)
    - Läs in API-svaret till en fil / buffer och parsa sedan med jansson
    - lägg till val för att hämta temp för alla städer och sedan spara in det i strukturen med städer.
    - loggfil med allt som händer, typ nått enkelt eventsystem?

*/

/*
    2025-09-05 Jimmy Jordan, skoluppgift Chas Academy
    CLI app som hämtar väderdata från ett API

FUNGERAR:
    - Läsa in städer och kordinater från en specifikt formaterad sträng.
    - användaren ka nvälja vilken stad. Felaktiga inputs hanteras.
    - Programmet producerar en korrekt URL för framtida kontakt med API på https://open-meteo.com/

SLASK:
    https://api.open-meteo.com/v1/forecast?latitude=<lat>&longitude=<lon>&current_weather=true

    - uses "WGS84 coordinates" so 6 decimal places is OK (https://en.wikipedia.org/wiki/World_Geodetic_System)

    TESTED URL: https://api.open-meteo.com/v1/forecast?latitude=59.3293&longitude=18.0686&current_weather=true

    GIVES RESPONSE:
    {
    "latitude": 59.3289,
    "longitude": 18.072357,
    "generationtime_ms": 0.0623464584350586,
    "utc_offset_seconds": 0, n
    "timezone": "GMT",
    "timezone_abbreviation": "GMT",
    "elevation": 24,
    "current_weather_units":
        {
            "time": "iso8601",
            "interval": "seconds",
            "temperature": "°C",
            "windspeed": "km/h",
            "winddirection": "°",
            "is_day": "",
            "weathercode": "wmo code"
        },
    "current_weather":
        {
            "time": "2025-09-05T13:15",
            "interval": 900,
            "temperature": 24.2,
            "windspeed": 11.9,
            "winddirection": 154,
            "is_day": 1,
            "weathercode": 2
        }
    }

*/
#include <assert.h>
#include <curl/curl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h> /* funkar bara på unix/linux */

#define MAX_CITIES 999
#define MAX_CITY_NAME_LENGTH 30

/* Simulated DB*/
const char swedishCitiesDataBase[] = "Stockholm:59.3293:18.0686\n"
                                     "Göteborg:57.7089:11.9746\n"
                                     "Malmö:55.6050:13.0038\n"
                                     "Uppsala:59.8586:17.6389\n"
                                     "Västerås:59.6099:16.5448\n"
                                     "Örebro:59.2741:15.2066\n"
                                     "Linköping:58.4109:15.6216\n"
                                     "Helsingborg:56.0465:12.6945\n"
                                     "Jönköping:57.7815:14.1562\n"
                                     "Norrköping:58.5877:16.1924\n"
                                     "Lund:55.7047:13.1910\n"
                                     "Gävle:60.6749:17.1413\n"
                                     "Sundsvall:62.3908:17.3069\n"
                                     "Umeå:63.8258:20.2630\n"
                                     "Luleå:65.5848:22.1567\n"
                                     "Kiruna:67.8558:20.2253\n";

typedef struct
{
    size_t ID;
    char name[MAX_CITY_NAME_LENGTH];
    double latitude;
    double longitude;
} city;

typedef struct
{
    city listOfCities[MAX_CITIES];
    size_t numberOfCities; /* Använder size_t för det är vad den är till för */
    /* Här kan man lägga till föregående API calls resultat också */

} cities;

/* GLOBAL VARAIBLES */
int exitCode = 0; /* sätts till -1 när ma nska stänga ned */
struct timeval timeStart, timeEnd;

void printSelectableCities(int _nrCities, city* _listOfCities)
{
    int i = 0;
    for (; i < _nrCities; i++)
    {
        printf("%3d: %s\n", i + 1, _listOfCities[i].name);
    }
    printf("SELECT A CITY (1-%d): ", _nrCities);
}

/* for when user types in multiple invalid charachters also quit if any char is Q or q*/
int clearInputBuffer()
{
    int currentChar; // Måste vara int för att kunna hålla EOF tror jag
    while ((currentChar = getchar()) != '\n' && currentChar != EOF)
    {
        if (currentChar == 'Q' || currentChar == 'q')
        {
            exitCode = -1;
            return -1;
        }
    }
    return 0;
}
/* Denna funktion gör nu två (nu 3) saker, men man vill aldrig prompta användaren utan att också läsa input, och vise versa. Så mejkar inte sense att dela upp. Ifs så lade jag nu
 * till att quit logiken bubblar upp härifrån också så är nog dags att dela upp den  */
int promptAndGetSelectionFromUser(cities* _selectableCities, city* _selectedCity)
{
    int selection = 0;

    if (!(scanf("%d", &selection)) || selection > _selectableCities->numberOfCities || selection < 1)
    {
        /* if user types in letters, clear input buffer and retry  */
        if (clearInputBuffer() == -1)
        {
            return -1;
        }
        printf("INVALID INPUT, RETRY: ");
        selection = promptAndGetSelectionFromUser(_selectableCities, _selectedCity);
    }

    /* -1 because the citites are zero indexed internally and 1 indexed in the GUI  */
    selection--;

    _selectedCity->ID = selection;
    strcpy(_selectedCity->name, _selectableCities->listOfCities[selection].name);
    _selectedCity->latitude = _selectableCities->listOfCities[selection].latitude;
    _selectedCity->longitude = _selectableCities->listOfCities[selection].longitude;

    return selection - 1;
}

size_t callback_handleResponse(void* _recievedChunk, size_t _size, size_t _numberOfMembers, void* _userPointer)
{
    gettimeofday(&timeEnd, NULL);
    long int seconds = timeEnd.tv_sec - timeStart.tv_sec;
    long int microseconds = timeEnd.tv_usec - timeStart.tv_usec;

    /* Fix for negative microseconds. They reset every second, so if a execution starts in one second and ends during the next, microseconds will be a negative value */
    if (microseconds < 0)
    {
        seconds--;
        microseconds += 1000000;
    }

    printf("\n=== RESPONSE RECEIVED ============== (%li s %li ms)\n", seconds, microseconds / 1000);

    /* NOllställ alla timers nu när vi läst ut en tid */
    timerclear(&timeStart);
    timerclear(&timeEnd);

    /* calculate size required for return, must match therwise CURL errors*/
    size_t realSize = _size * _numberOfMembers;
    fwrite(_recievedChunk, _size, _numberOfMembers, stdout);

    return realSize;
}

void getCitiesFromStringDataBase(cities* _selectableCities)
{
    /* if "swedishCitiesDataBase" is not a null terminated string we should exit */
    assert(swedishCitiesDataBase[strlen(swedishCitiesDataBase)] == '\0');

    /* Needed for sscanf to not just read the first line over and over agian */
    unsigned int lengthOfReadString = 0;
    unsigned int offset = 0;

    /* making sure its set to 0 since we start to count cities now */
    _selectableCities->numberOfCities = 0;

    int i;
    for (i = 0; i < MAX_CITIES; i++)
    {
        /* sscanf return value is number of succesfull reads */
        if (3 == sscanf(swedishCitiesDataBase + offset, "%[^:]:%lf:%lf%n", _selectableCities->listOfCities[i].name, &_selectableCities->listOfCities[i].latitude,
                        &_selectableCities->listOfCities[i].longitude, &lengthOfReadString))
        {
            /* ID is just order read from DB */
            _selectableCities->listOfCities[i].ID = i;

            _selectableCities->numberOfCities++;
            /* +1 to skip over the '\n' at the end of each row in the provided "database" string */
            offset = offset + lengthOfReadString + 1;
        }
        else
        {
            /* Stop reading if we cant read any more 3 value rows (str, f, f)*/
            break;
        }
    }
}

int main()
{
    /* one time setup */
    cities selectableCities;
    city selectedCity;

    getCitiesFromStringDataBase(&selectableCities);

main_program_loop:
    printf("  q: Exit program\n");
    printSelectableCities(selectableCities.numberOfCities, selectableCities.listOfCities);

    promptAndGetSelectionFromUser(&selectableCities, &selectedCity);
    if (exitCode == -1)
    {
        goto program_exit;
    }

    /* Build URL */
    char URL[1024];
    /* Sample DB only have 4 decimal places, but 6 are needed for meter acuracy */
    sprintf(URL, "https://api.open-meteo.com/v1/forecast?latitude=%.4lf&longitude=%.4lf&current_weather=true", selectedCity.latitude, selectedCity.longitude);

    printf("\n=== SELECTION ======================\n City name: %s (# %zu)\n", selectedCity.name, selectedCity.ID + 1);
    printf("  latitude: %lf\n", selectedCity.latitude);
    printf(" longitude: %lf\n", selectedCity.longitude);
    printf("   API URL: %s\n", URL);

    printf("\n=== SENDING REQUEST =================\n");

    /* CURL grejjer */
    /*
    This function sets up the program environment that libcurl needs. Think of it as an extension of the library loader.
    This function must be called at least once.
    */
    curl_global_init(CURL_GLOBAL_DEFAULT);
    /*
    Allocates and returns an easy handle that is used as input to other functions in the easy interface.
    The easy handle is used to hold and control a single network transfer. It is encouraged to reuse easy handles for repeated transfers with curl_easy_duphandle()
    */
    CURL* curl = curl_easy_init();
    CURLcode res;

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_handleResponse);

    gettimeofday(&timeStart, NULL); /* Startar timer  */
    res = curl_easy_perform(curl);  /* This calls the API and then executes the above supplied callback function when data is recieved */

    clearInputBuffer();
    printf("\n\nPress ENTER to go again or 'q' to exit: ");
    if (getchar() == 'q')
    {
        goto program_exit;
    }

    goto main_program_loop;

program_exit:

    /* exit cleanup */
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}