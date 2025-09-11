#ifndef WEATHER_API_H
#define WEATHER_API_H

#include <stddef.h>

typedef struct
{
    char* data;
    size_t size;
} response_buffer;

size_t handle_response(void*, size_t, size_t, response_buffer*);

int send_request(char*, response_buffer*);

void global_curl_cleanup_curl();

#endif /* WEATHER_API_H */