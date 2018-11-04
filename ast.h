// AST definitions
#ifndef __ast_h__
#define __ast_h__

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node Node;

#include "type.h"
#include "expr.h"
#include "decl.h"
#include "stmt.h"

#define MAXCHILDREN 3
#define INDENT_CHAR '-'

typedef enum { 
    K_EXPR, 
    K_STMT, 
    K_DECL 
} node_t;

typedef union {
    stmt_t stmt;
    expr_t expr;
    decl_t decl;
} node_k;

// AST node
typedef struct _Node {
    Type* type;
    // merge nodekind with kind?
    node_t nodekind;    
    node_k kind;
    //Expr attr;
    /*union {
        Constant val;
        char* name; // for variables
        struct { 
            int op;
            struct _Node* left;
            struct _Node* right;
        } op; // for binary expressions
    } attr;*/
    Expr* attr;
    struct _Node* body;      // Comound, Loop, ifelse
    struct _Node* else_body; // ifelse
    struct _Node* next;      // Next in sequence
} Node;

void doIndent(int indent);
void printTree(Node* node);

#endif
