#include <curl/curl.h>

size_t callback_handleResponse(void* _recievedChunk, size_t _size, size_t _numberOfMembers)
{
    /* calculate size required for return, must match otherwise CURL errors*/
    size_t realSize = _size * _numberOfMembers;
    fwrite(_recievedChunk, _size, _numberOfMembers, stdout);

    return realSize;
}

void sendRequest(char* _URL)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURLcode res;
    CURL* curl = curl_easy_init();

    if (curl == NULL)
    {
        printf("Failed to init curl");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, _URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_handleResponse);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        fprintf(stdout, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);
}

void cleanup()
{
    printf("running CURL global cleanup\n");
    curl_global_cleanup();
}