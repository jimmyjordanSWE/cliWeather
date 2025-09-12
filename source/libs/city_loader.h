#ifndef CITY_LOADER_H
#define CITY_LOADER_H

#include <stddef.h>

typedef struct
{
    /* todo: allocate strings dynamically */
    size_t id;
    char name[256]; /* geonames stores max 200 */
    double latitude;
    double longitude;
    char country[4];
    size_t population;
    char time_zone[64];
    /* should allocate these strings dynamically */
    /* also, add fields for weather data */
} city;

typedef struct
{
    city* list;
    size_t count;
} cities;

void load_cities_testdata(cities*);

void cleanup_city_loader(cities*);

#endif /* CITY_LOADER_H */
