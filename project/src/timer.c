#include <stdio.h>

#include "timer.h"


size_t timer(int from) {
    size_t counter = 0;
    for (int i = from; i > 0; --i) {
        ++counter;
        printf("%i ", i);
    }
    if (from >= 0) {
        ++counter;
        puts("0");
    }
    return counter;
}
