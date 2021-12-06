#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>

enum exitcode {
    EXIT_INCORRECT_ARGUMENTS = 1,   // means that the given file does not exist
    EXIT_CANNOT_OPEN_FILE = 2,      // means file cannot be opened
    EXIT_TOO_MANY_INSTRUCTIONS = 3,     // max num instructions is exceeded
    EXIT_INVALID_LABEL = 4,
    EXIT_SYMBOL_ALREADY_EXISTS = 5
};

void exit_program(enum exitcode code, ...); // dot-dot-dot means it supports a variable-length argument list 

#endif