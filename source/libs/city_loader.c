#include "city_loader.h"
#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Simulated DB */
const char test_data[] = "Stockholm:59.3293:18.0686\n"
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

void load_cities_testdata(cities* _selectable_cities)
{
    /* todo: dont use assert. if not a null terminated string, exit */
    /*  assert(test_data[strlen(test_data)] == '\0');
     */
    /* count cities in test_data string to know how much memory to allocate */
    _selectable_cities->count = 0;
    size_t i;
    for (i = 0; test_data[i] != '\0'; i++)
    {
        if (test_data[i] == '\n')
        {
            _selectable_cities->count++;
        }
    }

    /* allocate enough memory for storing all the cities */
    _selectable_cities->list = malloc(sizeof(city) * _selectable_cities->count);
    if (_selectable_cities->list == NULL)
    {
        fprintf(stderr, "Memory allocation failed for selectable_cities->list\nerrno: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Needed for sscanf to not just read the first line over and over again */
    int length_of_read_string = 0;
    size_t offset = 0;
    for (i = 0; i < _selectable_cities->count; i++)
    {
        /* sscanf return value is number of succesfull reads */
        if (3 == sscanf(test_data + offset, "%[^:]:%lf:%lf%n", _selectable_cities->list[i].name, &_selectable_cities->list[i].latitude, &_selectable_cities->list[i].longitude, &length_of_read_string))
        {
            /* for the testdata ID is just order read */
            _selectable_cities->list[i].id = i;

            /* +1 to skip over the '\n' at the end of each row */
            offset = offset + length_of_read_string + 1;
        }
        else
        {
            /* Stop reading if we cant read any more 3 value rows (str, f, f)*/
            break;
        }
    }
}

void cleanup_city_loader(cities* _selectable_cities) { free(_selectable_cities->list); }