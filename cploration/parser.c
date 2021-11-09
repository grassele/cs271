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
            if (is_Atype == true) {
                inst_type = 'A';
            }
            if (is_label == true) {
                inst_type = 'L';
            }
            if (is_Ctype == true) {
                inst_type == 'C';
            }
            printf("%c  ", "%s\n", inst_type, line); 
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

bool is_Atype(const char *line) {
    if (*(line[0]) == '@') {
        return true;
    }
    else {
        return false;
    }
}

bool is_label(const char *line) {
    if ((*(line[0]) == '(') && *(line[strlen((*line)-1)] == ')')) {
        return true;
    }
    else {
        return false;
    }
}

bool is_Ctype(const char *line);
    if (is_Atype == false && is_label == false) {
        return true;
    }
    else {
        return false;
    }
}