#include "scope.h"

Scope* enterScope(Scope* parent) {
    Scope* scope = (Scope*) malloc(sizeof(Scope));
    scope->parent = parent;
    return scope;
}

Scope* leaveScope(Scope* scope) {
    if (scope->parent != NULL) {
        scope = scope->parent;
    }
    printf("Trying to leave global scope\n");
    return scope;
}