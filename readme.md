# Assignment
Make a CLI program that connects to the API at https://open-meteo.com/

## Description
Program does the following:
1. Loads cities from any DSV of this format: "Stockholm:59.3293:18.0686\n". (Name, latitude, longitude). Currently read from a  test string, but next step is from a file.
2. Builds a URL.
3. Sends URL to [openmeteo.com](https://open-meteo.com/) via [libcurl](https://curl.se/libcurl/) and prints the raw JSON response.


## Feature ideas 
### Autocomplete
There is a huge database (~400MiB) of all location names on earth at [opengeo](https://www.geonames.org/).
I will use the list of all locations (and lat/long) with a population of minimum 500 (36MiB) to build a "trie" datastructure that is then used for the location autocomplete.

# Dev diary
2025-09-09 Finished the code for processing geonames files. I can now start on autocomplete / spelling suggestions.