#include <stdio.h>

#include "custom_pow.h"


int custom_pow(int base, int pow) {
    const int start_number = base;
    if (pow < 0) {
        return 0;
    }
    if (!pow) {
        return 1;
    }
    for (int i = 1; i < pow; ++i) {
            base *= start_number;
        }
        return base;
}
