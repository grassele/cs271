#include "parser.h"
#include "error.h"
#include "symtable.h"


void parse(FILE * file) {
    char line[MAX_LINE_LENGTH] = {0};
        unsigned int line_num = 0;
        unsigned int instr_num = 0;
        while (fgets(line, sizeof(line), file)) {
            line_num ++;
            if (instr_num > MAX_INSTRUCTIONS) {
                exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
            }
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
                if (!(isalpha(label[0])))   {
                    exit_program(EXIT_INVALID_LABEL, line_num, line);
                }
                if (symtable_find(label) !=  NULL) {
                    exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
                }
                symtable_insert(label, instr_num);
                continue;   // does continue actually exit the function?
            }
            if (is_Ctype(line)) {
                inst_type = 'C';
            }
            printf("%c  %s\n", inst_type, line); 
            instr_num ++;
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

bool is_Atype(const char *line) {
    return line[0] == '@';
}

bool is_label(const char *line) {
    return ((line[0] == '(') && line[strlen(line)-1] == ')');
}

bool is_Ctype(const char *line) {
    return (is_Atype(line) == false && is_label(line) == false);
}