#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checked_memcpy(void* _to, void* _from, size_t _bytes_to_copy)
{
    if (_to == NULL)
    {
        fprintf(stderr, "Error: Destination pointer is NULL.\n");
        return -1;
    }

    if (_from == NULL)
    {
        fprintf(stderr, "Error: Source pointer is NULL.\n");
        return -1;
    }

    memcpy(_to, _from, _bytes_to_copy);
    return 1;
}