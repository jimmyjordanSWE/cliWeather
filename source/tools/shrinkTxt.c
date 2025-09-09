/* The main 'geoname' table has the following fields :
---------------------------------------------------
geonameid         : integer id of record in geonames database
name              : name of geographical point (utf8) varchar(200)
asciiname         : name of geographical point in plain ascii characters,
varchar(200) alternatenames    : alternatenames, comma separated, ascii names
automatically transliterated, convenience attribute from alternatename table,
varchar(10000) latitude          : latitude in decimal degrees (wgs84) longitude
: longitude in decimal degrees (wgs84) feature class     : see
http://www.geonames.org/export/codes.html, char(1) feature code      : see
http://www.geonames.org/export/codes.html, varchar(10) country code      :
ISO-3166 2-letter country code, 2 characters cc2               : alternate
country codes, comma separated, ISO-3166 2-letter country code, 200 characters
admin1 code       : fipscode (subject to change to iso code), see exceptions
below, see file admin1Codes.txt for display names of this code; varchar(20)
admin2 code       : code for the second administrative division, a county in the
US, see file admin2Codes.txt; varchar(80) admin3 code       : code for third
level administrative division, varchar(20) admin4 code       : code for fourth
level administrative division, varchar(20) population        : bigint (8 byte
int) elevation         : in meters, integer dem               : digital
elevation model, srtm3 or gtopo30, average elevation of 3''x3'' (ca 90mx90m) or
30''x30'' (ca 900mx900m) area in meters, integer. srtm processed by cgiar/ciat.
timezone          : the iana timezone id (see file timeZone.txt) varchar(40)
modification date : date of last modification in yyyy-MM-dd format
 */
/* Så här ska det se ut i slutet
geoID   Namn        lat         lon         Land    Befolkning  timezone
2673730	Stockholm   59.32938	18.06871    SE      1515017     Europe/Stockholm
*/
#include <assert.h>
#include <malloc.h> 3sdqcyXEO3
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char *fileName = "../../data/cities500.txt";
// char* fileName = "../../data/test.txt";

const char *inputBuffer;
size_t rows = 0;

/*
ANTECKNINGAR:
- Orginalfilen är UTF-8. Alla de första 256 tecknen är samma som ASCII så man
skippar bara alla chars med högre värde än 255.
- Man verkar kunna sätta locale med setlocale(LC_ALL, "sv_SE.ISO8859-1") och
sedan använda string.h funktionen strxfrm() för att konvertera.

Filen är nu inläst till en enda lång sting. Nu dags att klippa bort allt onödigt
och sedan skriva till en ny fil som jag kan använda i main programmet.
*/

int main() {
  /* measure input TXT file size */
  FILE *txtFile = fopen(fileName, "r");
  assert(txtFile);

  int currentChar;
  size_t fileSizeBytes = 0;

  printf("Loaded: %s\n", fileName);

  while ((currentChar = fgetc(txtFile)) != EOF) {
    if (currentChar == '\n') /* one city per row in file */
    {
      rows++;
    }
    fileSizeBytes++;
  }
  printf("\r     READ: %zu B\n", fileSizeBytes);

  char *inputBuffer = malloc(fileSizeBytes);
  assert(malloc_usable_size(inputBuffer) >
         fileSizeBytes); /* crasha om vi allokerat för litet */

  printf("ALLOCATED: %zu B\n",
         malloc_usable_size(inputBuffer)); /* oinly works on linux*/

  /* reset internal state of fgetc() */
  rewind(txtFile);

  /* Copy file into allocated buffer*/
  size_t i = 0;
  for (; i < fileSizeBytes; i++) {
    inputBuffer[i] = fgetc(txtFile);
  }
  printf("\r  WRITTEN: %zu B", i);

  inputBuffer[i] = '\0'; /* manuell noll terminering av inlästa strängen då EOF
                            != nullterminering */

  printf("\n\n%zu cities in dataset", rows);

  printf("\n\nASCII codes of Last 3 chars: \n%c", inputBuffer[i - 5]);
  printf("%d ", (int)inputBuffer[i - 2]);
  printf("%d ", (int)inputBuffer[i - 1]);
  printf("%d\n", (int)inputBuffer[i]);

  /* Write to new file */
  FILE *outputFile = fopen("aa.txt", "w");
  assert(outputFile);

  size_t longestCityName = 0;

  fputs(inputBuffer, outputFile);
  fclose(txtFile);
  fclose(outputFile);
  free(inputBuffer);
  return 0;
}
