#include "utils.h"
#include <stdio.h>

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        if ((i-1) >= 0)  // Условие, позволяющее произвести вывод, необходимый для теста 1.0
            printf("%i ", i);
        else
            printf("%i\n", i);
    }
    return counter;
}
