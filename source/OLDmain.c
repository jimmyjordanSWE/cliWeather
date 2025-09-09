// detta är koden som claude spottade ut och som vi lämnade in på första grupparbetet på uppstartsveckan (Jimmy, kevin och leon)

// ================================
// DEL 1: INKLUDERINGAR OCH DATA
// ================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* cities = "Stockholm:59.3293:18.0686\n"
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

// ================================
// DEL 2: FUNKTIONER
// ================================
void print_cities()
{
    printf("Tillgängliga städer: ");

    const char* ptr = cities;
    char city_name[50];
    int chars_read;

    while (*ptr != '\0')
    {
        if (sscanf(ptr, "%49[^:]%n", city_name, &chars_read) == 1)
        {
            printf("%s ", city_name);
            ptr += chars_read;

            while (*ptr != '\n' && *ptr != '\0')
            {
                ptr++;
            }

            if (*ptr == '\n')
            {
                ptr++;
            }
        }
        else
        {
            break;
        }
    }

    printf("\n");
}

int find_city_coordinates(const char* search_city, double* lat, double* lon)
{
    const char* ptr = cities;
    char city_name[50];
    char line[100];
    int chars_read;

    while (*ptr != '\0')
    {
        int line_index = 0;

        while (*ptr != '\n' && *ptr != '\0')
        {
            line[line_index] = *ptr;
            line_index++;
            ptr++;
        }
        line[line_index] = '\0';

        if (sscanf(line, "%49[^:]:%lf:%lf", city_name, lat, lon) == 3)
        {
            if (strcasecmp(city_name, search_city) == 0)
            {
                return 1;
            }
        }

        if (*ptr == '\n')
        {
            ptr++;
        }
    }

    return 0;
}

// ================================
// DEL 3: HUVUDPROGRAM
// ================================
int main()
{
    char user_input[100];
    char url[256];
    double latitude, longitude;

    printf("Välkommen till Open-Meteo URL-byggaren!\n");

    while (1)
    {
        print_cities();

        printf("Välj en stad: ");

        if (fgets(user_input, sizeof(user_input), stdin) != NULL)
        {
            user_input[strcspn(user_input, "\n")] = '\0';

            if (find_city_coordinates(user_input, &latitude, &longitude))
            {
                sprintf(url, "https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f&current_weather=true", latitude, longitude);

                printf("URL: \"%s\"\r\n", url);
            }
            else
            {
                printf("Fel: Staden '%s' finns inte i listan över tillgängliga städer.\n", user_input);
            }
        }

        printf("\n");
    }

    return 0;
}