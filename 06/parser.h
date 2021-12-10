#ifndef __PARSER_H__
#define __PARSER_H__

#include "hack.h"
#include "error.h"
#include "symtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

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
        char* label;
    } operand;
    bool is_addr;
} a_instruction;

typedef struct c_instruction {
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;
} c_instruction;

typedef struct instruction {
    union {
        a_instruction a;
        c_instruction c;
    } instr;
    instr_type itype;
} instruction;

char *strip(char *s);
int parse(FILE *file, instruction *instructions);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);

void add_predefined_symbols();

bool parse_A_instruction(const char *line, a_instruction *instr);

void parse_C_instruction(char *line, c_instruction *instr);

#endif