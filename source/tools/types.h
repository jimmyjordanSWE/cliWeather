#ifndef __types_h__
#define __types_h__

#include <stddef.h>

typedef struct
{
    size_t ID;
    char name[64];
    double latitude;
    double longitude;
} city;

typedef struct
{
    city listOfCities[999];
    size_t numberOfCities;
    /* Här kan man lägga till föregående API calls resultat också */

} cities;

#endif