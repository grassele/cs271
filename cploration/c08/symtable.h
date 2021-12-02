#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SYMBOL_TABLE_SIZE 100

typedef int16_t hack_addr;

typedef struct Symbol {
    char *name;
    hack_addr addr;
} Symbol;

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str);
// Exercise 2: updating symtable functions
struct Symbol *symtable_find(char * key);   // old: struct Symbol *find(char * key);
void symtable_insert(char* key, hack_addr addr);    // old: void insert(char* key, hack_addr addr);
void symtable_display_table();  // old: void display_table();

#endif