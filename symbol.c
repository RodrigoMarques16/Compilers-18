#include "symbol.h"

Symbol* make_symbol(char* name, Type* type) {
    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    //symbol->kind = kind;
    symbol->type = type;
    symbol->name = name;
    return symbol;
}

void print_symbol(Symbol* symbol) {
    printf("%s: ", symbol->name);
    print_type(symbol->type);
}