#include "weather_api.h"

#include <curl/curl.h>
#include <malloc.h>
#include <string.h>

size_t handle_response(void* _recieved_chunk, size_t _size, size_t _number_of_members, response_buffer* _response)
{
    /* calculate size required for return, must match otherwise CURL errors*/
    size_t real_size = _size * _number_of_members;

    /* här ville AI använda en tmp adress först för at trealloc can faila och sabba allt. samt att då kan memcpy skriva på fel adresser*/
    _response->data = realloc(_response->data, _response->size + real_size + 1);
    memcpy(_response->data + _response->size, _recieved_chunk, real_size);
    _response->size += real_size;
    _response->data[_response->size] = '\0';

    return real_size;
}

int send_request(char* _url, response_buffer* _response)
{
    CURL* curl = curl_easy_init();
    CURLcode res;

    if (curl == NULL)
    {
        printf("Failed to init curl");
        return -1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_easy_setopt(curl, CURLOPT_URL, _url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handle_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)_response); /* cast to void* because curl must work for all type of responses */

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stdout, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    /* cleanup because we make a new handle every call */
    curl_easy_cleanup(curl);

    return 0;
}

void global_curl_cleanup_curl()
{
    printf("running CURL global cleanup\n");
    curl_global_cleanup();
}