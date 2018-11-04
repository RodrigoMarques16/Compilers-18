#ifndef __stmt_h__
#define __stmt_h__

typedef enum {
  STMT_EXPR,
  STMT_ASSIGN,
  STMT_IFELSE,
  STMT_WHILE,
  STMT_RETURN,
  STMT_DECL,
  STMT_BLOCK,
  STMT_READ,
  STMT_WRITE
} stmt_t;

#include "ast.h"
#include "type.h"
#include "decl.h"
/*
Node* make_stmt(stmt_t kind, Type* type, char* name, Node* expr,
                Node* body, Node* else_body, Node* next);
Node* make_stmt_block(Node* body);
Node* make_stmt_assign(char* name, Node* expr);
Node* make_stmt_decl(Node* decl);
Node* make_stmt_while(Node* expr, Node* body);
Node* make_stmt_return(Node* expr);
Node* make_stmt_ifelse(Node* expr, Node* body, Node* else_body);
Node* make_stmt_io(stmt_t kind, Node* expr);
Node* make_stmt_expr(Node* expr);
Node* append_stmt(Node* node, Node* next);
*/
Node* make_stmt(stmt_t kind, Type* type, Expr* expr,
                Node* body, Node* else_body, Node* next);
Node* make_stmt_block(Node* body);
Node* make_stmt_assign(char* name, Expr* expr);
Node* make_stmt_decl(Node* decl);
Node* make_stmt_while(Expr* expr, Node* body);
Node* make_stmt_return(Expr* expr);
Node* make_stmt_ifelse(Expr* expr, Node* body, Node* else_body);
Node* make_stmt_io(stmt_t kind, Expr* expr);
Node* make_stmt_expr(Expr* expr);
Node* append_stmt(Node* node, Node* next);

void print_stmt(Node* node, int indent);

#endif