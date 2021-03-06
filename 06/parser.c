#include "parser.h"

int parse(FILE *file, instruction *instructions) {
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;
    unsigned int instr_num = 0;
    instruction instr;
    add_predefined_symbols();
    symtable_display_table();
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
            if (!parse_A_instruction(line, &instr.instr.a)) {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.itype = A_TYPE;
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
            char tmp_line[MAX_LINE_LENGTH];
            strcpy(tmp_line, line);
            parse_C_instruction(tmp_line, &instr.instr.c);
            if (instr.instr.c.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }
            else if (instr.instr.c.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            }
            else if (instr.instr.c.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }
            instr.itype = C_TYPE;
            inst_type = 'C';
        }
        printf("%c  %s\n", inst_type, line); 
        instructions[instr_num++] = instr;
    }
    return instr_num;
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

// takes a line and extracts the label name from the parentheses
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

void add_predefined_symbols() {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
        predefined_symbol symbol_to_add = predefined_symbols[i];
        symtable_insert(symbol_to_add.name, symbol_to_add.address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
    char* s = (char*) malloc(strlen(line));
    strcpy(s, line + 1);
    char* s_end = NULL;
    long result = strtol(s, &s_end, 10);
    if (s_end == s) {
        // line is a string
        instr->operand.label = (char*) malloc(strlen(line));
        strcpy(instr->operand.label, s);
        instr->is_addr = false;
    }
    else if (*s_end != 0) {
        // line is a mix of strings and integers
        return false;
    }
    else {
        // line is a number
        instr->operand.address = result;
        instr->is_addr = true;
    }
    return true;
}


void parse_C_instruction(char *line, c_instruction *instr) {
    char* temp = strtok(line, ";");
    char* jump = strtok(NULL, ";");
    char* dest = strtok(temp, "=");
    char* comp = strtok(NULL, "=");
    int a;
    if (comp == NULL) {
        comp = dest;
        dest = NULL;
    }
    instr->jump = str_to_jumpid(jump);
    instr->dest = str_to_destid(dest);
    instr->comp = str_to_compid(comp, &a);
    instr->a = (a == 0 ? 0 : 1);
}


void assemble(const char * file_name, instruction* instructions, int num_instructions) {
    char *hack_file_name;
    strcpy(hack_file_name, file_name);
    strcat(hack_file_name, ".hack");
    opcode op;
    int new_address = 16;
    FILE * hack = fopen(hack_file_name, "w");
    for (int i = 0; i < num_instructions; i++) { // should this be < or <=
        instruction instr = instructions[i];
        if (instr.itype == 0) {
            if (instructions[i].instr.a.is_addr == false) {
                // a-instruction
                if (symtable_find(instr.instr.a.operand.label)) {
					op = symtable_find(instr.instr.a.operand.label) -> addr;
				}
                // c-instruction
                else {
                    symtable_insert(instr.instr.a.operand.label, new_address ++);
					op = symtable_find(instr.instr.a.operand.label)->addr;
                }
                free(instr.instr.a.operand.label);
            }
            else {
                op = instr.instr.a.operand.address;
            }
        }
        else if (instr.itype == 1) {
			op = instruction_to_opcode(instr.instr.c);
		}
		fprintf(hack, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", OPCODE_TO_BINARY(op));
    }
    fclose(hack);
}

opcode instruction_to_opcode(c_instruction instr) {
	opcode op = 0;
	op |= (7 << 13);
	op |= (instr.a << 12);
	op |= (instr.comp << 6);
	op |= (instr.dest << 3);
	op |= (instr.jump << 0);
	return op;
}

