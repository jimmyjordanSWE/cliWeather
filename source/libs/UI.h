#ifndef __UI__
#define __UI__

#include "citiesStruct.h"

int getSelectionFromUser(cities*, city*);

/* for when user types in multiple invalid charachters also quit if any char is Q or q*/
int clearInputBuffer();

void printSelectableCities(int, city*);

void printURL(char*);

void buildURL(char*, city*);

void printSelectionInfo(city*);

#endif