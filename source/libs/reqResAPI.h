#ifndef __sendResAPI__
#define __sendResAPI__

#include <stddef.h>

size_t callback_handleResponse(void*, size_t, size_t, void*);

void sendRequest(char*);
void cleanup();

#endif