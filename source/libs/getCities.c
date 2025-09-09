#include "dataStructs.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

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

void getCitiesFromDB(cities* _selectableCities)
{
    /* if "swedishCitiesDataBase" is not a null terminated string we should exit */
    assert(swedishCitiesDataBase[strlen(swedishCitiesDataBase)] == '\0');

    /* Needed for sscanf to not just read the first line over and over agian */
    unsigned int lengthOfReadString = 0;
    unsigned int offset = 0;

    /* making sure its set to 0 since we start to count cities now */
    _selectableCities->count = 0;

    int i;
    for (i = 0; i < 999; i++)
    {
        /* sscanf return value is number of succesfull reads */
        if (3 == sscanf(swedishCitiesDataBase + offset, "%[^:]:%lf:%lf%n", _selectableCities->list[i].name, &_selectableCities->list[i].latitude, &_selectableCities->list[i].longitude,
                        &lengthOfReadString))
        {
            /* ID is just order read from DB */
            _selectableCities->list[i].ID = i;

            _selectableCities->count++;
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