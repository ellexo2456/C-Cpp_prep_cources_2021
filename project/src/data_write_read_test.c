#include <string.h> 
#include <stdio.h>
#include "write_to_file.h"
#include "read_from_file.h"
#include "struct_test_data.h"

void data_write_read_test(void) {
    char const *filename = "test_file";

    some expected_data = {231, 245.0, "now"};

    write_to_file(filename, expected_data);

    some got_data = {0, 0.0, "00"};
    some *ptr_got_data = &got_data;

    read_from_file(filename, ptr_got_data);

    if ((got_data.num_int == expected_data.num_int) && (got_data.num_float == expected_data.num_float) && (strcmp(got_data.str, expected_data.str) == 0))
        printf ("Successful\n");
    else 
        printf("Something`s wrong\n");
}

