#ifndef __dataStructs__
#define __dataStructs__

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
    city* list;
    size_t count;
} cities;

#endif