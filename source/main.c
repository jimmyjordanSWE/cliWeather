#include "libs/city_loader.h"
#include "libs/ui_console.h"
#include "libs/weather_api.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main()
{
    cities all_cities;
    city selected_city;
    char open_meteo_url[1024];

    response_buffer open_meteo_response = {NULL, 0};

    do
    {
        load_cities_testdata(&all_cities);
        print_cities(all_cities.count, all_cities.list);
        if (get_selection_from_user(&all_cities, &selected_city) < 1)
        {
            printf("Exiting...\n");
            break;
        }

        build_open_meteo_url(open_meteo_url, &selected_city);

        print_open_meteo_url(open_meteo_url);
        print_selected_city(&selected_city);

        /* todo: add error handling, request can fail, then we to retry, not  use data */
        send_request(open_meteo_url, &open_meteo_response);

        printf("%s\n", open_meteo_response.data);

    } while (1);

    global_curl_cleanup_curl();
    printf("Done\n");
    return 0;
}