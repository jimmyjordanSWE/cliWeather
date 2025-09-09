#include "types.h"
#include <stdio.h>
#include <string.h>
extern int exitCode; /* sätts till -1 när man ska stänga ned */

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