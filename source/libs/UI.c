#include "citiesStruct.h"
#include <stdio.h>
#include <string.h>

/* for when user types in multiple invalid charachters any char is Q or q*/
int clearInputBuffer()
{
    char currentChar;
    while ((currentChar = getchar()) != '\n' && currentChar != EOF)
        ;

    return 0;
}
/* denna funktion slutar inte förens den kan returnera ett valid nummer eller 0 */
int getSelectionFromUser(cities* _allCities, city* _selectedCity)
{
    size_t selection = 0;

    scanf("%zu", &selection);
    clearInputBuffer();

    if (selection < 1 || selection > _allCities->count)
        return 0;

    _selectedCity->ID = selection - 1;
    strcpy(_selectedCity->name, _allCities->list[selection - 1].name);
    _selectedCity->latitude = _allCities->list[selection - 1].latitude;
    _selectedCity->longitude = _allCities->list[selection - 1].longitude;

    return selection;
}

void printSelectableCities(size_t _count, city* _allCities)
{

    printf("\n"); /* Needed for repeat runs */
    size_t i = 0;
    for (; i < _count; i++)
    {
        printf("%3zu: %s\n", i + 1, _allCities[i].name);
    }
    printf("Any other key for exit\n");
    printf("SELECT A CITY (1-%zu): ", _count);
}

void printURL(char* _URL) { printf("API URL: %s\n", _URL); }

void buildURL(char* _URL, city* _selectedCity)
{
    sprintf(_URL, "https://api.open-meteo.com/v1/forecast?latitude=%.6lf&longitude=%.6lf&current_weather=true", _selectedCity->latitude, _selectedCity->longitude);
}

void printSelectionInfo(city* selectedCity) { printf("\n%s\n", selectedCity->name); }