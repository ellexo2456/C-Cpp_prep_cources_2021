#include "stdio.h"
#include "write_to_file.h"
#include "read_from_file.h"
#include "struct_test_data.h"

void data_write_read_test(void) {
    printf("0");
    char const *filename = "test_file";

    some expected_data = {231, 245, 1965};

    write_to_file(filename, expected_data);

    some got_data = {0, 0, 0};

    got_data =read_from_file(filename, got_data);
    printf("\n%i %i %i\n", expected_data.artist, expected_data.song, expected_data.year);
    printf("%i %i %i\n", got_data.artist, got_data.song, got_data.year);
    if ((got_data.artist == expected_data.artist) && (got_data.song == expected_data.song) && (got_data.year == expected_data.year))
        printf ("Successful");
    else 
        printf("Something`s wrong");
}

