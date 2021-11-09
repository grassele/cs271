#include "parser.h"


void parse(FILE * file) {
    char line[MAX_LINE_LENGTH] = {0};
        unsigned int line_num = 0;
        while (fgets(line, sizeof(line), file)) {
            line_num ++;
            strip(line);
            if (!*line) {
                continue;
            }
            char inst_type;
            if (is_Atype(line)) {
                inst_type = 'A';
            }
            if (is_label(line)) {
                inst_type = 'L';
                char label[MAX_LABEL_LENGTH] = {0};
                strcpy(line, extract_label(line, label));
            }
            if (is_Ctype(line)) {
                inst_type = 'C';
            }
            printf("%c  %s\n", inst_type, line); 
        }
}

char *strip(char *s) {
    char s_new[strlen(s) + 1];
    int i = 0;
    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2+1) == '/') {
            break;
        }
        else if (!isspace(*s2)) {
            s_new[i++] = *s2;
        } 
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

char *extract_label(const char *line, char *label) {
    int i = 0;
    if (line[0] == '(') {
        for (int j = 1; j < strlen(line); line++) {
            if (line[j] != ')') {
                label[i++] = line[j];
            }
        }
    }
    label[i] = '\0';
    return label;
}

/*
char *extract_label(const char *line, char* label) {
    int i = 0;
    for (const char *s = line; *s; s++) {
        if (*s == '(' || *s == ')') {
            continue;
        }
        else {
            label[i++] = s*;
        }
    }
    label[i] = '\0';
    return label;
}
*/

bool is_Atype(const char *line) {
    return line[0] == '@';
}

bool is_label(const char *line) {
    return ((line[0] == '(') && line[strlen(line)-1] == ')');
}

bool is_Ctype(const char *line) {
    return (is_Atype(line) == false && is_label(line) == false);
}