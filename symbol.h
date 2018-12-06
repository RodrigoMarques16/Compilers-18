#ifndef __symbol_h__
#define __symbol_h__

#include "type.h"

//typedef enum {
//    kLOCAL,
//    kGLOBAL,
//    kPARAM, 
//} symbol_t;

typedef struct symbol {
    //symbol_t kind;
    Type* type;
    char* name;
} Symbol;

Symbol* make_symbol(char* name, Type* type);
void print_symbol(Symbol* symbol);

#endif