#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "print_sequence.h"


void print_sequence(int end_of_sequence) {
    if (end_of_sequence == 1) {
        printf("1");
    } else if (end_of_sequence > 1) {
        print_sequence(end_of_sequence - 1);
        printf(" %i", end_of_sequence);
    } else {
        print_sequence(end_of_sequence + 1);
        printf(" %i", end_of_sequence);
    }
}
