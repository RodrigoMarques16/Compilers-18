#include "decl.h"

Node* make_decl(decl_t kind, Type* type, char* name, Node* body) {
    Node* node       = (Node*) malloc(sizeof(Node));
    node->attr       = (Expr*) malloc(sizeof(Expr));
    node->nodekind   = K_DECL;
    node->kind.decl  = kind;
    node->type       = type;
    node->attr->name = name;
    node->body       = body;
    node->next       = NULL;
    node->symbol     = make_symbol(name, type);
    return node;
}

Node* make_decl_function(Type* subtype, char* name, ParamList* params, Node* body) {
    Type* type = make_type(T_FUNCTION, subtype, params);
    return make_decl(DECL_FUNCTION, type, name,body);
}

Node* make_decl_var(Type* type, char* name) {
    return make_decl(DECL_VAR, type, name, NULL);
}

Node* append_decl(Node* node, Node* list) {
    if (list == NULL){
        return node;
    }
    while(list->next != NULL) {
        list = list->next;
    }
    list->next = node;
    return node;
}

void print_decl(Node* node, int indent) {
    dbgprintf("Declaration: ");
    switch(node->kind.decl) {
        case DECL_FUNCTION: {
            print_decl_function(node, indent);
            break;
        }
        case DECL_VAR: {
            print_decl_var(node, indent);
            break;
        }
    }
}

void print_decl_function(Node* node, int indent) {
    printf("function %s: ", node->attr->name);
    print_type(node->type);
    printf(" ");
    print_stmt(node->body, indent);
}

void print_decl_var(Node* node, int indent) {
    printf("var %s: ", node->attr->name);
    print_type(node->type);
}