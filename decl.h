#ifndef __decl_h__
#define __decl_h__

typedef enum {
    DECL_VAR,
    DECL_FUNCTION
} decl_t;

#include "ast.h"
#include "type.h"

Node* make_decl(decl_t kind, Type* type, char* name, Node* body);
Node* make_decl_function(Type* subtype, char* name, ParamList* params, Node* body);
Node* make_decl_var(Type* type, char* name) ;
Node* append_decl(Node* node, Node* list);

void print_decl(Node* node, int indent);
void print_decl_function(Node* node, int indent);
void print_decl_var(Node* node, int indent);

#endif