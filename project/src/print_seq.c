#include <stdio.h>
#include <math.h>
#include "print_seq.h"
#include <stdlib.h>

void print_seq(int const end_of_seq) {
    int step = end_of_seq / abs(end_of_seq);  // step позволяет уменьшать или увеличивать предыдущий член
    int numb = 1 + step;                      // последовательности для получения текущего
    if (end_of_seq == 1) {
        printf("1");
    } else {
        printf("1 ");
        while (abs(numb) < abs(end_of_seq)) {
            printf("%i ", numb);
            int previous_numb = numb;
            numb = previous_numb + step;  // рекурсия
        }
        printf("%i", numb);
    }
}
