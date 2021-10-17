#include <stdio.h>
#include "write_to_file.h"
#include "struct_test_data.h"

void write_to_file(const char *filename, some expected_data) {
    FILE *ptr = fopen (filename, "w");
    fprintf (ptr, "%i\n%i\n%s", expected_data.num_int, expected_data.num_float, expected_data.str);
    fclose(ptr);
}