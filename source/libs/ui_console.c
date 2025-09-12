#include "city_loader.h"
#include <stdio.h>
#include <string.h>

/* for when user types in multiple invalid charachters any char is Q or q*/
int clear_buffer_stdin()
{
    int current_char;
    while ((current_char = getchar()) != '\n' && current_char != EOF)
        ;

    return 0;
}
/* denna funktion slutar inte förens den kan returnera ett valid nummer eller 0 */
int get_selection_from_user(cities* _allCities, city* _selectedCity)
{
    size_t selection = 0;

    scanf("%zu", &selection);
    clear_buffer_stdin();

    if (selection < 1 || selection > _allCities->count)
        return 0;

    _selectedCity->id = selection - 1;
    strcpy(_selectedCity->name, _allCities->list[selection - 1].name);
    _selectedCity->latitude = _allCities->list[selection - 1].latitude;
    _selectedCity->longitude = _allCities->list[selection - 1].longitude;

    return selection;
}

void print_cities(size_t _count, city* _allCities)
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

void print_open_meteo_url(char* _URL) { printf("API URL: %s\n", _URL); }

void print_selected_city(city* selectedCity) { printf("\n%s\n", selectedCity->name); }