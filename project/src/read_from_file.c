#include <stdio.h>
#include "read_from_file.h"
#include "struct_test_data.h"

some read_from_file (const char *filename, some *ptr_got_data) {
    FILE *ptr = fopen (filename, "r");
    fscanf (ptr, "%i\n%i\n%s", &(*ptr_got_data).num_int, &(*ptr_got_data).num_float, (*ptr_got_data).str);
    fclose(ptr);
}