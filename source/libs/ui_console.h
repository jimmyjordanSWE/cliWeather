#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

int get_selection_from_user(cities*, city*);

/* for when user types in multiple invalid charachters also quit if any char is Q or q*/
int clear_buffer_stdin();

void print_cities(size_t, city*);

void print_open_meteo_url(char*);

void build_open_meteo_url(char*, city*);

void print_selected_city(city*);

#endif /* CONSOLE_UI_H */