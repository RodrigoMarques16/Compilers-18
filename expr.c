#include "expr.h"

Expr* make_expr(expr_t kind, Type* type, char* name, Constant val, 
                int op, Expr* left, Expr* right) {
    Expr* expr  = (Expr*) malloc(sizeof(Expr));
    expr->kind  = kind;
    expr->type  = type;
    expr->name  = name;
    expr->val   = val;
    expr->op    = op;
    expr->left  = left;
    expr->right = right;
    return expr;
}

Expr* make_literal(type_t _type, Constant val) {
    Type* type = make_type_simple(_type);
    return make_expr(EXPR_CONSTANT, type, NULL, val, -1, NULL, NULL);
}

Expr* make_int_literal(int value) {
    Constant val;
    val.int_value = value;
    return make_literal(T_INTEGER, val);
}

Expr* make_float_literal(float value) {
    Constant val;
    val.float_value = value;
    return make_literal(T_FLOAT, val);
}

Expr* make_bool_literal(boolean value) {
    Constant val;
    val.bool_value = value;
    return make_literal(T_BOOL, val);
}

Expr* make_expr_var(char* name) {
    Type*    type = NULL;
    Constant val;         
    return make_expr(EXPR_ID, type, name, val, -1, NULL, NULL);
}

void print_literal(Expr* expr) {
    switch(expr->type->kind) {
        case T_INTEGER: {
            printf("%d", expr->val.int_value);
            break;
        }
        case T_FLOAT: {
            printf("%f", expr->val.float_value);
            break;
        }
        case T_BOOL: {
            if (expr->val.bool_value)
                printf("TRUE");
            else printf("FALSE");
            break;
        }
    }
}

void print_expr(Expr* expr) {
    switch(expr->kind) {
        case EXPR_CONSTANT: {
            print_literal(expr);
            break;
        }
        case EXPR_ID: {
            printf("%s", expr->name);
            break;
        }
    }
}

/*
Node* make_expr(expr_t kind, char*name) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->nodekind = K_EXPR;
    node->kind.expr = kind;
    return node;
}

Node* make_literal(type_t type, Constant val) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->nodekind = K_EXPR;
    node->kind.expr = EXPR_CONSTANT;
    node->type = make_type_simple(type);
    node->attr.val = val;
    node->body = NULL;
    node->else_body = NULL;
    node->next = NULL;
    return node;
}

Node* make_int_literal(int value) {
    Constant val;
    val.int_value = value;
    return make_literal(T_INTEGER, val);
}

Node* make_float_literal(float value) {
    Constant val;
    val.float_value = value;
    return make_literal(T_FLOAT, val);
}

Node* make_bool_literal(boolean value) {
    Constant val;
    val.bool_value = value;
    return make_literal(T_BOOL, val);
}

Node* make_expr_var(char* name) {
    Node* node = (Node*) malloc(sizeof(Node));

    node->attr.name = name;
    return node;
}

void print_literal(Node* node) {
    switch(node->type->kind) {
        case T_INTEGER: {
            printf("%d", node->attr.val.int_value);
            break;
        }
        case T_FLOAT: {
            printf("%f", node->attr.val.float_value);
            break;
        }
        case T_BOOL: {
            if (node->attr.val.bool_value)
                printf("TRUE");
            else printf("FALSE");
            break;
        }
    }
}

void print_expr(Node* node) {
    switch(node->kind.expr) {
        case EXPR_CONSTANT: {
            print_literal(node);
            break;
        }
    }
}*/