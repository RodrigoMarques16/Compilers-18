// AST definitions
#ifndef __ast_h__
#define __ast_h__

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node Node;

#include "type.h"
#include "decl.h"
#include "stmt.h"

#define MAXCHILDREN 3
#define INDENT_CHAR '-'

typedef enum {
  EXPR_ID,
  EXPR_CONSTANT,
  EXPR_ARITHMETIC,
  EXPR_RELATIONAL
} expr_t;

typedef enum { 
    K_EXPR, 
    K_STMT, 
    K_DECL 
} node_t;

// AST node
typedef struct _Node {
    Type* type;
    node_t nodekind;    
    union {
        stmt_t stmt;
        expr_t expr;
        decl_t decl;
    } kind;
    // Union of expression types
    union {
        int value; // for integer values
        char* name; // for variables
        struct { 
            int op;
            struct _Node* left;
            struct _Node* right;
        } op; // for binary expressions
    } attr;
    struct _Node* next;
    struct _Node* expr;
    struct _Node* body;
    struct _Node* else_body;
} Node;

void doIndent(int indent);
void printTree(Node* node);

#endif
