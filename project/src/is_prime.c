#include <math.h>
#include <stdio.h>

#include "is_prime.h"


int is_prime(int number) {
    if (number <= 1) {
        return 0;
    }
    int flag = 1;
    for (int delimiter = 2; delimiter*delimiter <= number; ++delimiter) {
        if (number % delimiter == 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}
