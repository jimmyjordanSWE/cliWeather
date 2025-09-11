#ifndef __citiesStruct__
#define __citiesStruct__

#include <stddef.h>

typedef struct
{
    size_t ID;
    char name[1024];
    double latitude;
    double longitude;
    char country[1024];
    size_t population;
    char timeZone[1024];
    /* should allocate these strings dynamically */
    /* also, add fields for weather data */
} city;

typedef struct
{
    /* TODO: must be of known size to make test data work right now
    Must be remade to make 300k cities to work in the future */
    city list[300];
    size_t count;
} cities;

#endif