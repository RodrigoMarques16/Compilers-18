#include "scope.h"
#include "ast.h"

Scope* enterScope(Scope* parent) {
    Scope* scope = (Scope*) malloc(sizeof(Scope));
    scope->symbols = hash_table_create(0,0);
    scope->level = 0;
    scope->parent = parent;

    if (parent != NULL){
        scope->level = parent->level + 1;
        dbgprintf("Entering new scope at depth %d\n", scope->level);
    }
    return scope;
}

Scope* leaveScope(Scope* scope) {
    dbgprintf("Leaving current scope at depth %d\n", scope->level);

    if (scope->parent != NULL) {
        scope = scope->parent;
    } else {
        printf("Trying to leave global scope\n");
    }

    return scope;
}

Symbol* lookup(Scope* scope, char* name) {
    if (scope == NULL) {
        printf("'%s' undefined\n");
        return NULL;
    }

    //dbgprintf("Looking up '%s' at level %d\n", name, scope->level);
    Symbol* symbol = hash_table_lookup(scope->symbols, name);

    if (symbol == NULL) {
        return lookup(scope->parent, name);
    }
    return symbol;
}

void bind(Scope* scope, Symbol* symbol) {
    dbgprintf("Binding '%s' to current scope\n", symbol->name);
    hash_table_insert(scope->symbols, symbol->name, symbol);
}