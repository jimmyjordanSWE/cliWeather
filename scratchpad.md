## notes
Use "gcc main.c libs/*.c  -Wall -lcurl" for compilation.


## Ideas
### Autocomplete from file
opengeo have txt files with all locations on earth. All citiues with +500 population is a couple of MiB. Use this data for autocomplete. Also contains coordinates, timezone and country.

### Eventsystem and log file?

## Open-meteo
They use "WGS84 coordinates" (https://en.wikipedia.org/wiki/World_Geodetic_System)

Example response:
{
    "latitude": 59.3289,
    "longitude": 18.072357,
    "generationtime_ms": 0.0623464584350586,
    "utc_offset_seconds": 0,
    "timezone": "GMT",
    "timezone_abbreviation": "GMT",
    "elevation": 24,
    "current_weather_units": {
        "time": "iso8601",
        "interval": "seconds",
        "temperature": "°C",
        "windspeed": "km/h",
        "winddirection": "°",
        "is_day": "",
        "weathercode": "wmo code"
    },
    "current_weather": {
        "time": "2025-09-05T13:15",
        "interval": 900,
        "temperature": 24.2,
        "windspeed": 11.9,
        "winddirection": 154,
        "is_day": 1,
        "weathercode": 2
    }
}