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
    Type*  type;             // unecessary but code isn't updated yet
    node_t nodekind;         // merge nodekind with kind?
    node_k kind;             
    Expr*  attr;             // Value, id and expressions
    struct _Node* body;      // For compound, loop, if-else
    struct _Node* else_body; // For if-else
    struct _Node* next;      // Next in sequence
} Node;

void doIndent(int indent);
void printTree(Node* node);

#endif

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