#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>

enum exitcode {
    EXIT_INCORRECT_ARGUMENTS = 1,   // means that the given file does not exist
}

void exit_program(enum exitcode code, ...); // dot-dot-dot means it supports a variable-length argument list 

#endif