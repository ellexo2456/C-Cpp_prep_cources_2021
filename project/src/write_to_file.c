#include <stdio.h>
#include "write_to_file.h"
#include "struct_test_data.h"

void write_to_file(const char *filename, some expected_data) {
    FILE *ptr = fopen (filename, "w");
    fprintf (ptr, "%i %i %i", expected_data.artist, expected_data.song, expected_data.year);
    fclose(ptr);
}