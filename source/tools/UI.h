#include "types.h"

int promptAndGetSelectionFromUser(cities* _selectableCities, city* _selectedCity);

/* for when user types in multiple invalid charachters also quit if any char is Q or q*/
int clearInputBuffer();