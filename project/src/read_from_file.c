#include <stdio.h>
#include "read_from_file.h"
#include "struct_test_data.h"

some read_from_file (const char *filename, some got_data) {
    FILE *ptr = fopen (filename, "r");
    fscanf (ptr, "%i %i %i", &got_data.artist, &got_data.song, &got_data.year);
    fclose(ptr);
}