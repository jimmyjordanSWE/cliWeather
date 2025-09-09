
#include "libs/UI.h"
#include "libs/dataStructs.h"
#include "libs/getCities.h"
#include "libs/reqResAPI.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main()
{
    cities allCities;
    city selectedCity;
    char URL[1024];

    do
    {
        getCitiesFromDB(&allCities);
        printSelectableCities(allCities.count, allCities.list);
        if (getSelectionFromUser(&allCities, &selectedCity) < 1)
        {
            printf("Exiting...\n");
            break;
        }

        buildURL(URL, &selectedCity);

        printURL(URL);

        printSelectionInfo(&selectedCity);

        sendRequest(URL);

    } while (1);

    cleanup();
    printf("Done\n");
    return 0;
}