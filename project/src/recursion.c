#include <stdio.h>
#include "recursion.h"

void recursion(int n) {
    if (n >= 1) {
        for (int i = 1; i <= n; ++i) {
            if (i != n)
                printf("%i ", i);
            else
                printf("%i", i);
        }
    } else {
        for (int i = 1; i >= n; --i) {
            if (i != n)
                printf("%i ", i);
            else
                printf("%i", i);
        }
    }
}
