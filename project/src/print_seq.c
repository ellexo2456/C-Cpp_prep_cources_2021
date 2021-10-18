#include <stdio.h>
#include <math.h>
#include "print_seq.h"
#include <stdlib.h>

void print_seq(int const end_of_seq) {
    int step = end_of_seq / abs(end_of_seq);  // step позволяет уменьшать или увеличивать предыдущий член
    int number = 1 + step;                      // последовательности для получения текущего
    if (end_of_seq == 1) {
        printf("1");
    } else {
        printf("1 ");
        while (abs(number) < abs(end_of_seq)) {
            printf("%i ", number);
            int previous_number = number;
            number = previous_number + step;  // рекурсия
        }
        printf("%i", number);
    }
}
