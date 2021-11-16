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

typedef int (*action_type)(char *start, FILE *email);


typedef struct {
    state_type new_state;
    action_type action;
} rule_type;

int email_parser(const char *path_to_email);

char *strdup(const char *s);
int check_line_count(FILE start_point);
void cut_line_breaker(char *start);
int print_value(char *start, FILE *email);
int is_boudary(char *line);
char *is_multipart(char *start, const int line_count, FILE *email);
void cut_qoutes_or_line_breaker(char *start);
int compute_part_count(char *boundary, FILE *email);
int print_part_count(char *start, FILE *email);
lexem_type check_header_end(char *start);
lexem_type get_lexem(const char *initial_string, char *start, char **end, lexem_type *searching_lexem_pointer);

static rule_type syntax[STATE_COUNT][LEXEM_COUNT] = {
//		            LEXEM_FROM_COLON, 	        LEXEM_TO_COLON,            LEXEM_DATE_COLON,            LEXEM_CONTENT_TYPE_COLON, 	   	   LEXEM_SKIP, 	                     LEXEM_HEADER_END
/*STATE_HEADER*/	{{STATE_VALUE, NULL},	    {STATE_VALUE, NULL},       {STATE_VALUE, NULL},        	{STATE_VALUE, NULL},           	   {STATE_HEADER, NULL},   	         {STATE_HEADER, NULL}},
/*STATE_VALUE*/	    {{STATE_ERROR, NULL},	    {STATE_ERROR, NULL},       {STATE_ERROR, NULL},         {STATE_ERROR, NULL},	           {STATE_HEADER, print_value},      {STATE_ERROR, NULL}},
};

char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p != NULL) {
        memcpy(p, s, size);
    }
    return p;
}

int check_line_count(FILE start_point) {
    int counter = 0;
    char line[100];
    int flag = 1;
    do {
        if (!fgets(line, 100, &start_point)) {
            if (ferror(&start_point)) {
                perror("*/*check_line_count ERROR*/*");
                fclose(&start_point);
                return -1;
            }
            puts("check_line_count: File reading`s done");
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

void cut_line_breaker(char *start) {
    while (*start) {
        if (*start == '\r' || *start == '\n') {
            *start = '\0';
            --start;
        }
        ++start;
    }
}

int print_value(char *start, FILE *email) {
    while (isspace(*start)) {
        ++start;
    }
    cut_line_breaker(start);
    const int line_count = check_line_count(*email);
    if (line_count == -1) {
        return -1;
    }
    if (line_count == 1) {
        printf("%s|", start);
        return 1;
    }
    printf("%s ", start);
    FILE *start_point = email;
    for (int i = 0; i < line_count - 1; ++i) {
        char initial_string[100];
        char *line = fgets(initial_string, 100, start_point);
        if (!line) {
            if (ferror(start_point)) {
                perror("*/*ERROR*/*");
                fclose(start_point);
                return -1;
            }
            puts("email_parser: File reading`s done");
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

int is_boudary(char *line) {
    return tolower(line[0]) == 'b' && tolower(line[1]) == 'o' && tolower(line[2]) == 'u' && tolower(line[3]) == 'n'\
        && tolower(line[4]) == 'd' && tolower(line[5]) == 'a' && tolower(line[6]) == 'r' && tolower(line[7]) == 'y' && line[8] == '=';
}

char *is_multipart(char *start, const int line_count, FILE *email) {
    FILE *start_point = email;
    char *boundary = NULL;
    for (; *start; ++start) {
            if (is_boudary(start)) {
                boundary = start;
            }
        }
    int i = 1;
    while (!boundary && (i < line_count)) {
        char initial_string[100];
        char *line = fgets(initial_string, 100, start_point);
        if (!line) {
            if (ferror(start_point)) {
                perror("*/*ERROR*/*");
                fclose(start_point);
                return NULL;
            }
            puts("email_parser: File reading`s done");
            return NULL;
        }
        for (; *line; ++line) {
            if (is_boudary(line)) {
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

void cut_qoutes_or_line_breaker(char *start) {
    while (*start) {
        if (*start == '\"' || *start == '\r' || *start == '\n') {
            *start = '\0';
            --start;
        }
        ++start;
    }
    if (start[-1] == ' ') {
        start[-1] = '\0';
    }
}

int compute_part_count(char *boundary, FILE *email) {
    boundary += sizeof("boundary=") - 1;
    if (*boundary == '\"') {
        ++boundary;
    }
    cut_qoutes_or_line_breaker(boundary);
    FILE *start_point = email;
    int part_count = 0;
    while (1) {
        char line[100];
        if (!fgets(line, 100, start_point)) {
            if (ferror(start_point)) {
                perror("*/*print_value ERROR*/*");
                fclose(start_point);
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

int print_part_count(char *start, FILE *email) {
    const int line_count = check_line_count(*email);
    if (line_count == -1) {
        return -1;
    }
    char *boundary = is_multipart(start, line_count, email);
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

lexem_type check_header_end(char *start) {
    int flag = 1;
    while (*start && flag) {
        if (!isspace(*start)) {
                flag = 0;
        }
        ++start;
    }
    if (!flag) {
        return LEXEM_SKIP;
    }
    return LEXEM_HEADER_END;
}

lexem_type get_lexem(const char *initial_string, char *start, char **end, lexem_type *searching_lexem_pointer) {
    if (start == initial_string) {
        switch (*searching_lexem_pointer) {
            case LEXEM_FROM_COLON:
                if (tolower(start[0]) == 'f' && tolower(start[1]) == 'r' && tolower(start[2]) == 'o' && tolower(start[3]) == 'm' && start[4] == ':')  {
                    *searching_lexem_pointer = LEXEM_TO_COLON;
                    *end = start + 4;
                    return LEXEM_FROM_COLON;
                }
                break;
            case LEXEM_TO_COLON:
                if (tolower(start[0]) == 't' && tolower(start[1]) == 'o' && start[2] == ':') {
                    *searching_lexem_pointer = LEXEM_DATE_COLON;
                    *end = start + 2;
                    return LEXEM_TO_COLON;
                }
                break;
            case LEXEM_DATE_COLON:
                if (tolower(start[0]) == 'd' && tolower(start[1]) == 'a' && tolower(start[2]) == 't' && tolower(start[3]) == 'e' && start[4] == ':') {
                    *searching_lexem_pointer = LEXEM_CONTENT_TYPE_COLON;
                    *end = start + 4;
                    return LEXEM_DATE_COLON;
                }
                break;
            case LEXEM_CONTENT_TYPE_COLON:
                if (tolower(start[0]) == 'c' && tolower(start[1]) == 'o' && tolower(start[2]) == 'n'\
                && tolower(start[3]) == 't' && tolower(start[4]) == 'e' && tolower(start[5]) == 'n'\
                && tolower(start[6]) == 't' && start[7] == '-' && tolower(start[8]) == 't'\
                && tolower(start[9]) == 'y' && start[10] == 'p' && tolower(start[11]) == 'e' && start[12] == ':') {
                    *searching_lexem_pointer = LEXEM_END_SEARCHING;
                    *end = start + 12;
                    return LEXEM_CONTENT_TYPE_COLON;
                } 
                break;
            default:
                break;
            }
            return check_header_end(start);
    }
    *end = start + 1;
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
        char *start = fgets(initial_string, 3024*1000, email);
        if (!start) {
            if (ferror(email)) {
                perror("*/*ERROR*/*");
                fclose(email);
                return -1;
            }
            puts("email_parser: File reading`s done");
            break;
        }
        while (*start) {
            char *end[] = {start};
            lexem_type current_lexem = get_lexem(initial_string, start, end, &searching_lexem);
            rule_type rule = syntax[current_state][current_lexem];
            if (rule.new_state == STATE_ERROR) {
                fclose(email);
                return -1;
            }
            if (searching_lexem == LEXEM_END_SEARCHING) {
                if (print_part_count(start,email) == -1) {
                    puts("Can`t print part count");
                }
                fclose(email);
                return 1;
            }
            if (rule.action != NULL) {
                ++start;
                if (rule.action(start, email) == -1) {
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
            start = *end;
        }
    }
    return -1;
}