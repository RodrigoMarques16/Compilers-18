#ifndef __scope_h__
#define __scope_h__

#include "hash_table.h"
#include "symbol.h"

typedef enum {
    GLOBAL,
    LOCAL, 
    PARAM
} scope_t;

typedef struct scope {
    char* name;
    struct hash_table* symbols;
    struct scope* parent;
} Scope;

Scope* enterScope(Scope* parent); // create new scope
Scope* leaveScope(Scope* scope); // pop list
Symbol* lookup(Scope* scope, char* name);
Symbol* bind(Scope* scope, Symbol* symbol);

#endif