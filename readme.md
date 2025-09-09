# First assignment at Chas Academy
Make a CLI program that connects to the API at https://open-meteo.com/

## Features
### Autocomplete
There is a huge database (~400MiB) of all location names on earth at [opengeo](https://www.geonames.org/).
I will use the list of all locations (and lat/long) with a population of minimum 500 (36MiB) to build a "trie" datastructure that is then used for the location autocomplete.

## Program needs to: 

### 1. Parse cities500.txt
Extract the following data fields:

    - city name
    - coordinates
    - timezone
    - country
    - population (used for autocomplete scoring)

### 2. Connect to API
Use libcurl easy mode to get the weather.





