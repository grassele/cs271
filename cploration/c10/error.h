#ifndef __ERROR_H__
#define __ERROR_H__

#include "hack.h"
#include "symtable.h"
#include "parser.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum exitcode {
    EXIT_INCORRECT_ARGUMENTS = 1,   // means that the given file does not exist
    EXIT_CANNOT_OPEN_FILE,      // means file cannot be opened
    EXIT_TOO_MANY_INSTRUCTIONS,     // max num instructions is exceeded
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
    EXIT_INVALID_A_INSTR,
    EXIT_INVALID_C_DEST,
    EXIT_INVALID_C_COMP,
    EXIT_INVALID_C_JUMP
};

void exit_program(enum exitcode code, ...); // dot-dot-dot means it supports a variable-length argument list 

#endif