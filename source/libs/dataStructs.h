#ifndef __dataStructs__
#define __dataStructs__

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
    city list[999];
    size_t count;
    /* Här kan man lägga till föregående API calls resultat också */

} cities;

#endif