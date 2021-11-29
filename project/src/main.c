#include <stdlib.h>
#include <stdio.h>

#include "/home/alexey/First/project/include/email_parser.h"

#ifndef ERROR
#define ERROR -1
#endif

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_email = argv[1];
    if (email_parser(path_to_email) == ERROR) {
        puts("\nERROR");
    }
    return 0;
}
