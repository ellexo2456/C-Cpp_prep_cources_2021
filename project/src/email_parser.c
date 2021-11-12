#include <ctype.h>
#include <stdio.h>

typedef enum {
    STATE_HEADER,
    STATE_VALUE,
    STATE_COUNT,
    STATE_ERROR,
    STATE_HEADER_END,
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

typedef int (*action_type)(const char *start, const char **end, FILE *email);

typedef struct {
    state_type new_state;
    action_type action;
} rule_type;

static rule_type syntax[STATE_COUNT][LEXEM_COUNT] = {
//		            LEXEM_FROM_COLON, 	        LEXEM_TO_COLON,            LEXEM_DATE_COLON,            LEXEM_CONTENT_TYPE_COLON, 	   	   LEXEM_SKIP, 	                     LEXEM_HEADER_END
/*STATE_HEADER*/	{{STATE_VALUE, NULL},	    {STATE_VALUE, NULL},       {STATE_VALUE, NULL},        	{STATE_VALUE, NULL},           	   {STATE_HEADER, NULL},   	         {STATE_HEADER_END, NULL}},
/*STATE_VALUE*/	    {{STATE_ERROR, NULL},	    {STATE_ERROR, NULL},       {STATE_ERROR, NULL},         {STATE_ERROR, NULL},	           {STATE_HEADER_END, print_value},  {STATE_ERROR, NULL}},
};

void cut_space(char **current) {
     while (isspace(**current)) {
        ++*current;
    }
}

int check_line_count(FILE *email) {
    int counter = 0;
    char next_line[100];
    FILE *start_point = email;
    do {
        if (!fgets(next_line, 100, start_point)) {
            if (ferror(start_point)) {
                perror("*/*check_line_count ERROR*/*");
                fclose(start_point);
                return -1;
            }
            puts("check_line_count: File reading`s done");
            return -1;
        }
        ++counter;
    } while (isspace(*next_line));
    return counter;
}

void cut_line_breaker(char *start) {
    while (*start) {
        if (*start == '\r' || *start == '\n' || *start == '\r\n' || *start == '\n\r') {
            *start = '\0';
            --start;
        }
        ++start;
    }
}

int print_value(char *start, const char **end, FILE *email) {
    cut_space(&start);
    cut_line_breaker(start);
    const int line_count = check_line_count(email);
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
        char next_line[100];
        if (!fgets(next_line, 100, start_point)) {
            if (ferror(start_point)) {
                perror("*/*print_value ERROR*/*");
                fclose(start_point);
                return -1;
            }
            puts("print_value: File reading`s done");
            return -1;
        }
        cut_space(&next_line);
        cut_line_breaker(next_line);
        if (i != line_count - 2) {
            printf("%s ", next_line);
        } else {
            printf("%s|", next_line);
        }
    }


}

const char *is_multipart(char *start, const int line_count) {
    
}

int print_part_count(char *start, FILE *email) {
    const int line_count = check_line_count(email);
    if (line_count == -1) {
        return -1;
    }
    const char *boundary = is_multipart(start, line_count);
    if (!boundary) {
        printf("%s", "1");
        return 1;
    }
    const int part_count = compute_part_count(boundary, email);
    if (part_count == -1) {
        return -1;
    }
    printf("%i", part_count);
    return 1;
}

lexem_type get_lexem(const char *initial_string, const char *start, char **end, lexem_type *searching_lexem_pointer) {
    if (start == initial_string) {
        switch (*searching_lexem_pointer) {
            case LEXEM_FROM_COLON:
                if (strcasestr(start, "from:")) {
                    *searching_lexem_pointer = LEXEM_TO_COLON;
                    *end = start + 4;
                    return LEXEM_FROM_COLON;
                }
                break;
            case LEXEM_TO_COLON:
                if (strcasestr(start, "to:")) {
                    *searching_lexem_pointer = LEXEM_DATE_COLON;
                    *end = start + 2;
                    return LEXEM_TO_COLON;
                }
                break;
            case LEXEM_DATE_COLON:
                if (strcasestr(start, "date:")) {
                    *searching_lexem_pointer = LEXEM_CONTENT_TYPE_COLON;
                    *end = start + 4;
                    return LEXEM_DATE_COLON;
                }
                break;
            case LEXEM_CONTENT_TYPE_COLON:
                if (strcasestr(start, "content-type:")) {
                    *searching_lexem_pointer = LEXEM_END_SEARCHING;
                    *end = start + 12;
                    return LEXEM_CONTENT_TYPE_COLON;
                }
                break;
            default:
                return check_header_end(start);
            }
    }
    *end = start + 1;
    return LEXEM_SKIP;    
}
 
int email_parser(const char *path_to_email) {
    state_type current_state = STATE_HEADER;
    lexem_type searching_lexem = LEXEM_FROM_COLON;
    FILE *email = fopen(path_to_email, "r");
    if (!email) {
        perror("*/*ERROR*/*");
        return -1;
    }
    while (searching_lexem != LEXEM_END_SEARCHING) {
        char initial_string[100];
        char *start = fgets(initial_string, 100, email);
        if (!start) {
            if (ferror(email)) {
                perror("*/*ERROR*/*");
                fclose(email);
                return -1;
            }
            puts("File reading`s done");
            return -1;
        }
        while (*start) {
            char **end;
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
                if (rule.action(start, end, email) == -1) {
                    puts("Error with action");
                    fclose(email);
                    return -1;
                }
            }
            current_state = rule.new_state;
            start = *end;
        }
    }
}