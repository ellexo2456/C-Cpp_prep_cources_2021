#include <stdio.h>
#include <stdlib.h>

#include "custom_pow.h"
#include "is_prime.h"
#include "print_sequence.h"
#include "timer.h"


enum Errors {
    ERROR_ARGUMENTS_COUNT = -1,
    ERROR_WRONG_FLAG = -2,
};

enum Cases {
    TIMER = 1,
    CUSTOM_POW,
    IS_PRIME,
    PRINT_SEQUENCE,
};


int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERROR_ARGUMENTS_COUNT;
    }

    int test_case = atoi(argv[1]);
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TIMER: {
            int from = atoi(data);
            size_t ticks_count = timer(from);
            printf("%zu", ticks_count);
            break;
        }
        case CUSTOM_POW: {
            if (argc != 4) {
                return ERROR_ARGUMENTS_COUNT;
            }
            int base = atoi(data);
            int pow = atoi(argv[3]);
            int res = custom_pow(base, pow);
            printf("%i\n", res);
            break;
        }
        case IS_PRIME: {
            int number = atoi(data);
            printf("%i", is_prime(number));
            break;
        }
        case PRINT_SEQUENCE: {
            int end_of_sequence = atoi(data);
            print_sequence(end_of_sequence);
            break;
        }
        default: {
            return ERROR_WRONG_FLAG;
        }
    }
}
