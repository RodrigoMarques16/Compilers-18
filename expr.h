#ifndef __expr_h__
#define __expr_h__

#include "type.h"

typedef enum {
  EXPR_ID,
  EXPR_CONSTANT,
  EXPR_ARITHMETIC,
  EXPR_RELATIONAL,
  EXPR_ASSIGN
} expr_t;

typedef struct _Expr Expr;

#include "ast.h"
#include "parser.h"

typedef struct _Expr {
    expr_t kind;    
    Type* type;
    struct _Expr* left;  // Left expression
    struct _Expr* right; // Right expression
    int op;              // Operator
    char* name;          // Variable name
    Constant val;        // Value
} Expr;

/*
Node* make_expr(expr_t kind, char*name);
Node* make_literal(type_t type, Constant val);
Node* make_int_literal(int value);
Node* make_float_literal(float value);
Node* make_bool_literal(boolean value);
*/ 
Expr* make_expr(expr_t kind, Type* type, char* name, Constant val, 
                int op, Expr* left, Expr* right);
                
Expr* make_literal(type_t type, Constant val);
Expr* make_int_literal(int value);
Expr* make_float_literal(float value);
Expr* make_bool_literal(boolean value); 
Expr* make_expr_var(char* name);
Expr* make_expr_relational(int op, Expr* left, Expr* right);
Expr* make_expr_arithmetic(int op, Expr* left, Expr* right);
Expr* make_expr_assign(int op, Expr* left, Expr* right);

void print_expr(Expr* expr);
void print_literal(Expr* expr);

#endif