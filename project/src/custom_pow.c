#include "custom_pow.h"
#include <stdio.h>

int custom_pow(int base, int pow) {
    int const start_number = base;
    if (pow > 0) {
        for (int i = 1; i < pow; ++i) {
            base *= start_number;
        }
        return base;
    }
    return 1;
}
