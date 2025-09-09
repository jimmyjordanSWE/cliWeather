
/* Så här ska det se ut i slutet
geoID   Namn        lat         lon         Land    Befolkning  timezone
2673730	Stockholm   59.32938	18.06871    SE      1515017     Europe/Stockholm
*/
#include "../libs/dataStructs.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fileName = "../../data/cities500.txt";

int main()
{
    FILE* txtFile = fopen(fileName, "r");
    assert(txtFile);

    int currentChar;
    size_t fileSizeBytes = 0;
    size_t cityCount = 0;

    printf("Loaded: %s\n", fileName);

    /* measure input TXT file size */
    while ((currentChar = fgetc(txtFile)) != EOF)
    {

        if (currentChar == '\n') /* one city per row in file */
        {
            cityCount++;
        }
        fileSizeBytes++;
    }
    printf("\r     READ: %zu B\n", fileSizeBytes);

    char* inputBuffer = malloc(fileSizeBytes);
    assert(malloc_usable_size(inputBuffer) > fileSizeBytes); /* crasha om vi allokerat för litet */

    printf("ALLOCATED: %zu B\n", malloc_usable_size(inputBuffer)); /* oinly works on linux*/

    /* reset internal state of fgetc() */
    rewind(txtFile);

    /* Copy file into buffer */
    size_t i = 0;
    for (; i < fileSizeBytes; i++)
    {
        inputBuffer[i] = fgetc(txtFile);
    }
    printf("\r  WRITTEN: %zu B", i);

    inputBuffer[i] = '\0'; /* manuell noll terminering av inlästa strängen då EOF
                              != nullterminering */

    cities allCities;
    allCities.count = cityCount;
    allCities.list = malloc(sizeof(city) * cityCount);

    printf("\ncities.  : %zu B\n", malloc_usable_size(allCities.list));

    /* tokenize inputbuffer and copy relevant fields */
    char* delimiter = "\t\n";
    int fieldsPerRow = 19;
    int j = 0;
    char* currentToken;

    for (i = 0; i < cityCount; i++)
    {
        for (j = 0; j < fieldsPerRow; j++)
        {
            currentToken = strsep(inputBuffer, delimiter);

            if (currentToken == NULL)
                break;
            switch (j)
            {
            case 0:
                allCities.list[i].ID = (size_t)strtoul(currentToken, NULL, 10);
                break;
            case 2:
                strcpy(allCities.list[i].name, currentToken);
                break;
            case 4:
                allCities.list[i].latitude = atof(currentToken);
                break;
            case 5:
                allCities.list[i].longitude = atof(currentToken);
                break;
            case 8:
                strcpy(allCities.list[i].country, currentToken);
                break;
            case 14:
                allCities.list[i].population = (size_t)strtoul(currentToken, NULL, 10);
                break;
            case 17:
                strcpy(allCities.list[i].timeZone, currentToken);
                break;
            }
        }
        if (currentToken == NULL)
            break;
    }

    printf("\n\n%zu cities in dataset\n", cityCount);
    /* Write to new file */
    FILE* outputFile = fopen("aa.txt", "a");
    assert(outputFile);

    for (i = 0; i < cityCount; i++)
    {
        /* 4 decimal places gives ~10m accuracy */
        fprintf(outputFile, "%zu,%s,%.4lf,%.4lf,%s,%zu,%s\n", allCities.list[i].ID, allCities.list[i].name, allCities.list[i].latitude, allCities.list[i].longitude, allCities.list[i].country,
                allCities.list[i].population, allCities.list[i].timeZone);
    }

    fclose(txtFile);
    fclose(outputFile);
    free(inputBuffer);
    return 0;
}
