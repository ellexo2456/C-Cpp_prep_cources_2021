#include "custom_pow.h"
#include <stdio.h>

int custom_pow(int base, int pow) {
    if (pow > 0) {
        for (int i = 1; i <= pow; ++i) {
            base *= base;
        }
        return base;
    } else {
        return 1;
    }
}
