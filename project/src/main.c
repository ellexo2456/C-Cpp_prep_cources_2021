#include <stdlib.h>
#include <stdio.h>

#include "email_parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_email = argv[1];
    if (email_parser(path_to_email) == -1) {
        puts("\nERROR");
    }
    puts("SUCCESS");
    return 0;
}
