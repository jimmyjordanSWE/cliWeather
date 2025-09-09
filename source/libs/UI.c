#include "dataStructs.h"
#include <stdio.h>
#include <string.h>

/* for when user types in multiple invalid charachters any char is Q or q*/
int clearInputBuffer()
{
    char currentChar; // Måste vara int för att kunna hålla EOF
    while ((currentChar = getchar()) != '\n' && currentChar != EOF)
        ;

    return 0;
}
/* denna funktion slutar inte förens den kan returnera ett valid nummer eller 0 */
int getSelectionFromUser(cities* _allCities, city* _selectedCity)
{
    int selection = 0;

    scanf("%d", &selection);
    clearInputBuffer();

    if (selection < 1 || selection > _allCities->count)
        return 0;

    _selectedCity->ID = selection - 1;
    strcpy(_selectedCity->name, _allCities->list[selection - 1].name);
    _selectedCity->latitude = _allCities->list[selection - 1].latitude;
    _selectedCity->longitude = _allCities->list[selection - 1].longitude;

    return selection;
}

void printSelectableCities(int _count, city* _allCities)
{

    printf("\n"); /* Needed for repeat runs */
    int i = 0;
    for (; i < _count; i++)
    {
        printf("%3d: %s\n", i + 1, _allCities[i].name);
    }
    printf("Any other key for exit\n");
    printf("SELECT A CITY (1-%d): ", _count);
}

void printURL(char* _URL) { printf("API URL: %s\n", _URL); }

void buildURL(char* _URL, city* _selectedCity)
{
    sprintf(_URL, "https://api.open-meteo.com/v1/forecast?latitude=%.6lf&longitude=%.6lf&current_weather=true", _selectedCity->latitude, _selectedCity->longitude);
}

void printSelectionInfo(city* selectedCity) { printf("\n%s\n", selectedCity->name); }