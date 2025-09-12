#ifndef WEATHER_API_H
#define WEATHER_API_H

#include <city_loader.h>
#include <stddef.h>

typedef struct
{
    char* data;
    size_t size;
} response_buffer;

void build_open_meteo_url(char*, city*);

size_t handle_response(void*, size_t, size_t, response_buffer*);

int send_request(char*, response_buffer*);

void cleanup_weather_api();

#endif /* WEATHER_API_H */