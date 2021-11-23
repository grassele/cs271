#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;

typedef enum instr_type {
    INVALID = -1, 
    A_TYPE, 
    C_TYPE
} instr_type;

typedef struct a_instruction {
    union {
        hack_addr address;
        char *label;
    } operand;
    bool is_addr;
} a_instruction;

typedef struct c_instruction {
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
} c_instruction;

typedef struct instruction {
    union {
        a_instruction a;
        c_instruction c;
    } instr;
    instr_type itipe;
} instruction;

char *strip(char *s); // char* strip(char*;)
void parse(FILE * file);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

// takes a line and extracts the label name from the parentheses
char *extract_label(const char *line, char* label);
