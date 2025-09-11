#ifndef CITY_LOADER_H
#define CITY_LOADER_H

#include <stddef.h>

typedef struct
{
    size_t id;
    char name[1024];
    double latitude;
    double longitude;
    char country[1024];
    size_t population;
    char time_zone[1024];
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

void load_cities_testdata(cities*);
#endif /* CITY_LOADER_H */