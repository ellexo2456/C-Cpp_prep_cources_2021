#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "custom_pow.h"
#include "is_prime.h"
#include "print_seq.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_REC_IMPL    4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int test_case = atoi(argv[1]);  // Первый аргумент: определяет, какой кейс будет выполняться
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {                          // 1й кейс - "таймер"
            int to = atoi(data);
            size_t ticks_count = timer_from(to);
            printf("%zu", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {                         // 2й кейс - функция возведения в степень
            if (argc == 4) {
                int base = atoi(data);
                int pow = atoi(argv[3]);
                int res = custom_pow(base, pow);
                printf("%i\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {                          // 3й кейс "проверка числа на простоту
            int num = atoi(data);
            printf("%i", is_prime(num));
            break;
        }
        case TST_REC_IMPL: {                          // 4й кейс рекурсивный вывод последовательности
            int const end_of_seq = atoi(data);        // целых чисел до end_of_seq включительно
            print_seq(end_of_seq);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
