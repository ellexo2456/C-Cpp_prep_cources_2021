#include <stdio.h>
#include <math.h>
#include "is_prime.h"

int is_prime(int num) {
    if (num <= 1) {
        return 0;
    } else {
        for (int i = 2; i <= sqrt(num); ++i) {  // Поиск делителей, для ускорение цикл до корня из числа
            if (num % i == 0)
                return 0;
        }
    }
    return 1;
}
