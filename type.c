#include "type.h"

// Create complex types, eg: functions, arrays
Type* make_type(type_t kind, Type* subtype, ParamList* params) {
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = kind;
    type->subtype = subtype;
    type->params = params;
    return type;
}

// Create simple types, eg: int, char
Type* make_type_simple(type_t kind) {
    return make_type(kind, NULL, NULL);
}

ParamList* make_param(char* name, struct type* type) {
    ParamList* param = (ParamList*) malloc(sizeof(ParamList));
    param->name = name;
    param->type = type;
    param->next = NULL;
    return param;
}

ParamList* append_param(ParamList* param, ParamList* next) {
    ParamList* temp = next;
    while(next->next != NULL)
        next = next->next;
    next->next = param;
    return temp;
}

void print_params(ParamList* params) {
    if (params == NULL) return;
    print_type(params->type);
    printf(" %s", params->name);
    if (params->next != NULL) {
        printf(", ");
        print_params(params->next);
    }
}

void print_type(Type* t) {
    switch(t->kind) {
        case T_FUNCTION: {
            printf("function (");
            print_params(t->params);
            printf(") -> ");
            print_type(t->subtype);
            break;
        }
        case T_INTEGER: {
            printf("int");
            break;
        }
        case T_BOOL: {
            printf("bool");
            break;
        }
        case T_VOID: {
            printf("void");
            break;
        }
    }
}