#include "stmt.h"

Node* append_stmt(Node* node, Node* list) {
    if (list == NULL) return node;
    Node *temp = list;
    while(list->next != NULL)
        list = list->next;
    list->next = node;
    return temp;
}

Node* make_stmt(stmt_t kind, Type* type, Expr* expr, 
                Node* body, Node* else_body, Node* next) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->type = type;
    node->nodekind = K_STMT;
    node->kind.stmt = kind;
    node->attr = expr;
    node->body = body;
    node->else_body = else_body;
    node->next = next;
    return node;
}

Node* make_stmt_block(Node* body) {
    return make_stmt(STMT_BLOCK, NULL, NULL, body, NULL, NULL);
}

Node* make_stmt_assign(Expr* expr) {
    /* make assignments binary expressions */
    Symbol* symbol = make_symbol(expr->left->name, expr->type);
    Node* stmt = make_stmt(STMT_ASSIGN, NULL, expr, NULL, NULL, NULL);
    stmt->symbol = symbol;
    return stmt;
}

Node* make_stmt_decl(Node* decl) {
    return make_stmt(STMT_DECL, decl->type, decl->attr, NULL, NULL, NULL);
}

Node* make_stmt_while(Expr* expr, Node* body) {
    return make_stmt(STMT_WHILE, NULL, expr, body, NULL, NULL);
}

Node* make_stmt_return(Expr* expr) {
    // type checking
    return make_stmt(STMT_RETURN, NULL, expr, NULL, NULL, NULL);
}

Node* make_stmt_ifelse(Expr* expr, Node* body, Node* else_body) {
    return make_stmt(STMT_IFELSE, NULL, expr, body, else_body, NULL);
}

Node* make_stmt_io(stmt_t kind, Expr* expr) {
    // use param list for args
    return make_stmt(kind, NULL, expr, NULL, NULL, NULL);
}

Node* make_stmt_expr(Expr* expr) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->type = expr->type;
    node->nodekind = K_EXPR;
    node->kind.expr = expr->kind;
    node->attr = expr;
    node->body = NULL;
    node->else_body = NULL;
    node->next = NULL;
    return node;
}

void print_stmt(Node* node, int indent) {
    while(node != NULL) {
        if (node->nodekind == K_EXPR) {
            // Special case for expression statements
            doIndent(indent);
            print_expr(node->attr);
            printf(";\n");
            node = node->next;
            continue;
        }
        switch(node->kind.stmt) {
            case STMT_BLOCK: {
                doIndent(indent);
                printf("{\n");
                print_stmt(node->body, indent+1);
                doIndent(indent);
                printf("}\n");
                break;
            }
            case STMT_DECL: {
                doIndent(indent);
                dbgprintf("Declaration: ");
                print_decl_var(node, indent);
                printf(";\n");
                break;
            }
            case STMT_WHILE: {
                doIndent(indent);
                printf("while (");
                print_expr(node->attr);
                printf(")\n");
                print_stmt(node->body, indent);
                //doIndent(indent);
                //printf("}\n");
                break;
            }
            case STMT_RETURN: {
                doIndent(indent);
                printf("return ", node->attr->name);
                print_expr(node->attr);
                printf(";\n");
                break;
            }
            case STMT_IFELSE: {
                doIndent(indent);
                printf("if (");
                print_expr(node->attr);
                printf(")\n");
                print_stmt(node->body, indent);
                //doIndent(indent);
                //printf("}\n");
                if (node->else_body != NULL) {
                    doIndent(indent);
                    printf("else\n");
                    print_stmt(node->else_body, indent);
                    //doIndent(indent);
                    //printf("}\n");
                }
                break;
            }
            case STMT_READ: {
                doIndent(indent);
                printf("READ: ");
                print_expr(node->attr);
                printf("\n");
                break;
            }
            case STMT_WRITE: {
                doIndent(indent);
                printf("WRITE: ");
                print_expr(node->attr);
                printf("\n");
                break;
            }
            case STMT_ASSIGN: {
                doIndent(indent);
                print_expr(node->attr->left);
                printf(" = ");
                print_expr(node->attr->right);
                printf(";\n");
                break;
            }
        }
        node = node->next;
    }
}