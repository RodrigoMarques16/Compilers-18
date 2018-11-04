#ifndef _TYPE_H
#define _TYPE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FALSE,
    TRUE
} boolean;

typedef enum {
    T_VOID,
    T_BOOL,
    T_INTEGER,
    T_FLOAT,
    T_FUNCTION
} type_t;

typedef union {
    int     int_value;
    boolean bool_value;
    float   float_value;
} Constant;

typedef struct type {
    type_t kind;              // Which type it represents
    struct type* subtype;     // For functions and arrays
    struct paramlist* params; // Function parameters
} Type;

typedef struct paramlist {
    char* name;             // Identifer of the current parameter
    struct type* type;      // Type of the current paramater
    struct paramlist* next; // The rest of the parameters if they exist
} ParamList;

Type* make_type(type_t t, Type* subtype, ParamList* params);
Type* make_type_simple(type_t kind);
ParamList* make_param(char* name, struct type* type);
ParamList* append_param(ParamList* param, ParamList* next);

void print_type(Type* t);
void print_params(ParamList* params);

#endif