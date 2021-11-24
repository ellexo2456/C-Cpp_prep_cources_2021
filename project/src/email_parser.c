#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    STATE_HEADER,
    STATE_VALUE,
    STATE_COUNT,
    STATE_ERROR,
} state_type;

typedef enum {
    LEXEM_FROM_COLON,
    LEXEM_TO_COLON,
    LEXEM_DATE_COLON,
    LEXEM_CONTENT_TYPE_COLON,
    LEXEM_SKIP,
    LEXEM_HEADER_END,
    LEXEM_COUNT,
    LEXEM_END_SEARCHING,
} lexem_type;

typedef int (*action_type)(char *first_line, FILE *email);


typedef struct {
    state_type new_state;
    action_type action;
} rule_type;

int email_parser(const char *path_to_email);

int print_error(const char *function, FILE *email);
char *strdup(const char *s);
int check_line_count(FILE email);
void cut_line_breaker(char *line);
int print_value(char *first_line, FILE *email);
int is_boudary_in(char *line);
char *is_multipart(char *first_line, const int line_count, FILE *email);
void cut_qoutes_or_line_breaker(char *line);
int compute_part_count(char *boundary, FILE *email);
int print_part_count(char *line, FILE *email);
lexem_type check_header_end_or_skip(char *line);
lexem_type get_lexem(const char *initial_string, char *line, char **end, lexem_type *searching_lexem_pointer);

static rule_type syntax[STATE_COUNT][LEXEM_COUNT] = {
//		            LEXEM_FROM_COLON, 	        LEXEM_TO_COLON,            LEXEM_DATE_COLON,            LEXEM_CONTENT_TYPE_COLON, 	   	   LEXEM_SKIP, 	                     LEXEM_HEADER_END
/*STATE_HEADER*/	{{STATE_VALUE, NULL},	    {STATE_VALUE, NULL},       {STATE_VALUE, NULL},        	{STATE_VALUE, NULL},           	   {STATE_HEADER, NULL},   	         {STATE_HEADER, NULL}},
/*STATE_VALUE*/	    {{STATE_ERROR, NULL},	    {STATE_ERROR, NULL},       {STATE_ERROR, NULL},         {STATE_ERROR, NULL},	           {STATE_HEADER, print_value},      {STATE_ERROR, NULL}},
};

int print_error(const char *function, FILE *email) {
    if (ferror(email)) {
        printf("in %s", function);
        perror("*/*check_line_count ERROR*/*");
        fclose(email);
    }
    if(!strncmp(function, "compute_part_count", sizeof("compute_part_count") - 1) || !strncmp(function, "email_parser", sizeof("email_parser") - 1)) {
        return 1;
    }
    puts("check_line_count: File reading`s done");
    return -1;
}

char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p != NULL) {
        memcpy(p, s, size);
    }
    return p;
}

int check_line_count(FILE email) {
    int counter = 0;
    char line[100];
    int flag = 1;
    do {
        if (!fgets(line, 100, &email)) {
            print_error("check_line_count", &email);
            return -1;
        }
        char *temporary_line = line;
        while (*temporary_line && flag) {
            if (!isspace(*temporary_line)) {
                flag = 0;
            }
            ++temporary_line;
        }
        ++counter;
    } while (isspace(*line) && !flag);
    return counter;
}

void cut_line_breaker(char *line) {
    while (*line) {
        if (*line == '\r' || *line == '\n') {
            *line = '\0';
            --line;
        }
        ++line;
    }
}

int print_value(char *first_line, FILE *email) {
    while (isspace(*first_line)) {
        ++first_line;
    }
    cut_line_breaker(first_line);
    const int line_count = check_line_count(*email);
    if (line_count == -1) {
        return -1;
    }
    if (line_count == 1) {
        printf("%s|", first_line);
        return 1;
    }
    printf("%s ", first_line);
    for (int i = 0; i < line_count - 1; ++i) {
        char initial_string[100];
        char *line = fgets(initial_string, 100, email);
        if (!line) {
            print_error("print_value", email);
            return -1;
        }
        while (isspace(*line)) {
            ++line;
        }
        cut_line_breaker(line);
        if (i != line_count - 2) {
            printf("%s ", line);
        } else {
            printf("%s|", line);
        }
    }
    return 1;
}

int is_boudary_in(char *line) {
    return tolower(line[0]) == 'b' && tolower(line[1]) == 'o' && tolower(line[2]) == 'u' && tolower(line[3]) == 'n'\
        && tolower(line[4]) == 'd' && tolower(line[5]) == 'a' && tolower(line[6]) == 'r' && tolower(line[7]) == 'y' && line[8] == '=';
}

char *is_multipart(char *first_line, const int line_count, FILE *email) {
    char *boundary = NULL;
    for (; *first_line; ++first_line) {
            if (is_boudary_in(first_line)) {
                boundary = first_line;
            }
        }
    int i = 1;
    while (!boundary && (i < line_count)) {
        char initial_string[100];
        char *line = fgets(initial_string, 100, email);
        if (!line) {
            print_error("is_multipart", email);
            return NULL;
        }
        for (; *line; ++line) {
            if (is_boudary_in(line)) {
                boundary = line;
            }
        }
        ++i;
    }
    if (!boundary) {
        return NULL;
    }
    return strdup(boundary);
}

void cut_qoutes_or_line_breaker(char *line) {
    while (*line) {
        if (*line == '\"' || *line == '\r' || *line == '\n') {
            *line = '\0';
            --line;
        }
        ++line;
    }
    if (line[-1] == ' ') {
        line[-1] = '\0';
    }
}

int compute_part_count(char *boundary, FILE *email) {
    boundary += sizeof("boundary=") - 1;
    if (*boundary == '\"') {
        ++boundary;
    }
    cut_qoutes_or_line_breaker(boundary);
    int part_count = 0;
    while (1) {
        char line[100];
        if (!fgets(line, 100, email)) {
            if (print_error("compute_part_count", email) == -1) {
                return -1;
            }
            break;
        }
        char *boundary_start = strstr(line, boundary);
        if (boundary_start && line[0] == '-' && line[1] == '-'\
        && boundary_start[strlen(boundary)] != '-' && boundary_start[strlen(boundary) + 1] != '-') {
            ++part_count;
        }
    }
    return part_count;
}

int print_part_count(char *line, FILE *email) {
    const int line_count = check_line_count(*email);
    if (line_count == -1) {
        return -1;
    }
    char *boundary = is_multipart(line, line_count, email);
    if (!boundary) {
        printf("%s", "1");
        return 1;
    }
    int part_count = compute_part_count(boundary, email);
    free(boundary);
    if (part_count == -1) {
        return -1;
    }
    printf("%i", part_count);
    return 1;
}

lexem_type check_header_end_or_skip(char *line) {
    int flag = 1;
    while (*line && flag) {
        if (!isspace(*line)) {
                flag = 0;
        }
        ++line;
    }
    if (!flag) {
        return LEXEM_SKIP;
    }
    return LEXEM_HEADER_END;
}

lexem_type get_lexem(const char *initial_string, char *line, char **end, lexem_type *searching_lexem_pointer) {
    if (line == initial_string) {
        switch (*searching_lexem_pointer) {
            case LEXEM_FROM_COLON:
                if (tolower(line[0]) == 'f' && tolower(line[1]) == 'r' && tolower(line[2]) == 'o' && tolower(line[3]) == 'm' && line[4] == ':')  {
                    *searching_lexem_pointer = LEXEM_TO_COLON;
                    *end = line + 4;
                    return LEXEM_FROM_COLON;
                }
                break;
            case LEXEM_TO_COLON:
                if (tolower(line[0]) == 't' && tolower(line[1]) == 'o' && line[2] == ':') {
                    *searching_lexem_pointer = LEXEM_DATE_COLON;
                    *end = line + 2;
                    return LEXEM_TO_COLON;
                }
                break;
            case LEXEM_DATE_COLON:
                if (tolower(line[0]) == 'd' && tolower(line[1]) == 'a' && tolower(line[2]) == 't' && tolower(line[3]) == 'e' && line[4] == ':') {
                    *searching_lexem_pointer = LEXEM_CONTENT_TYPE_COLON;
                    *end = line + 4;
                    return LEXEM_DATE_COLON;
                }
                break;
            case LEXEM_CONTENT_TYPE_COLON:
                if (tolower(line[0]) == 'c' && tolower(line[1]) == 'o' && tolower(line[2]) == 'n'\
                && tolower(line[3]) == 't' && tolower(line[4]) == 'e' && tolower(line[5]) == 'n'\
                && tolower(line[6]) == 't' && line[7] == '-' && tolower(line[8]) == 't'\
                && tolower(line[9]) == 'y' && line[10] == 'p' && tolower(line[11]) == 'e' && line[12] == ':') {
                    *searching_lexem_pointer = LEXEM_END_SEARCHING;
                    *end = line + 12;
                    return LEXEM_CONTENT_TYPE_COLON;
                } 
                break;
            default:
                break;
            }
            return check_header_end_or_skip(line);
    }
    *end = line + 1;
    return LEXEM_SKIP;    
}
 
int email_parser(const char *path_to_email) {
    state_type current_state = STATE_HEADER;
    lexem_type searching_lexem = LEXEM_FROM_COLON;
    FILE *email = fopen(path_to_email, "r");
    if (!email) {
        perror("email_parser: */*ERROR*/*");
        return -1;
    }
    while (searching_lexem != LEXEM_END_SEARCHING) {
        char initial_string[3024*1000];
        char *line = fgets(initial_string, 3024*1000, email);
        if (!line) {
            if (print_error("email_parser", email) == -1) {
                return -1;
            }
            break;
        }
        while (*line) {
            char *end[] = {line};
            lexem_type current_lexem = get_lexem(initial_string, line, end, &searching_lexem);
            rule_type rule = syntax[current_state][current_lexem];
            if (rule.new_state == STATE_ERROR) {
                fclose(email);
                return -1;
            }
            if (searching_lexem == LEXEM_END_SEARCHING) {
                if (print_part_count(line,email) == -1) {
                    puts("Can`t print part count");
                }
                fclose(email);
                return 1;
            }
            if (rule.action != NULL) {
                ++line;
                if (rule.action(line, email) == -1) {
                    puts("Error with action");
                    fclose(email);
                    return -1;
                }
            }
            if (current_lexem == LEXEM_SKIP) {
                if (current_state == STATE_VALUE) {
                    fseek(email, 0, SEEK_SET);
                }
                current_state = STATE_HEADER;
                break;
            }
            if (current_lexem == LEXEM_HEADER_END) {
                fseek(email, 0, SEEK_SET);
                if (searching_lexem == LEXEM_CONTENT_TYPE_COLON) {
                    printf("%s", "1");
                    return 1;
                }
                printf("%s", "|");
                ++searching_lexem;
                break;
            }
            current_state = rule.new_state;
            line = *end;
        }
    }
    return -1;
}