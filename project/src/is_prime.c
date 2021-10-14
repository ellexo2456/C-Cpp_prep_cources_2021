#include <stdio.h>
#include <math.h>
#include "is_prime.h"

int is_prime(int num) {
    for (int i = 2; i <= (sqrt(num)+1); ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}
