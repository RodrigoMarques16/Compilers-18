#include "stmt.h"

Node* append_stmt(Node* node, Node* list) {
    if (list == NULL) return node;
    Node *temp = list;
    while(list->next != NULL)
        list = list->next;
    list->next = node;
    return temp;
}

Node* make_stmt(stmt_t kind, Type* type, char* name, Node* expr, 
                Node* body, Node* else_body, Node* next) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->type = type;
    node->nodekind = K_STMT;
    node->kind.stmt = kind;
    if (kind == STMT_DECL || kind == STMT_ASSIGN)
        node->attr.name = name;
    node->expr = expr;
    node->body = body;
    node->else_body = else_body;
    node->next = next;
    return node;
}

Node* make_stmt_block(Node* body) {
    return make_stmt(STMT_BLOCK, NULL, NULL, NULL, body, NULL, NULL);
}

Node* make_stmt_assign(char* name, Node* expr) {
    // type checking
    return make_stmt(STMT_ASSIGN, NULL, name, expr, NULL, NULL, NULL);
}

Node* make_stmt_decl(Node* decl) {
    return make_stmt(STMT_DECL, decl->type, decl->attr.name, NULL, NULL, NULL, NULL);
}

Node* make_stmt_while(Node* expr, Node* body) {
    return make_stmt(STMT_WHILE, NULL, NULL, expr, body, NULL, NULL);
}

Node* make_stmt_return(Node* expr) {
    // type checking
    return make_stmt(STMT_RETURN, NULL, NULL, expr, NULL, NULL, NULL);
}

Node* make_stmt_ifelse(Node* expr, Node* body, Node* else_body) {
    return make_stmt(STMT_IFELSE, NULL, NULL, expr, body, else_body, NULL);
}

Node* make_stmt_io(stmt_t kind, Node* expr) {
    // use param list for args
    return make_stmt(kind, NULL, NULL, NULL, NULL, NULL, NULL);
}


void print_stmt(Node* node, int indent) {
    while(node != NULL) {
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
                print_decl_var(node, indent);
                printf(";\n");
                break;
            }
            case STMT_ASSIGN: {
                doIndent(indent);
                printf("%s = ", node->attr.name);
                // print expression
                printf(";\n");
                break;
            }
            case STMT_WHILE: {
                doIndent(indent);
                printf("while (");
                // print expr
                printf(") {\n");
                print_stmt(node->body, indent+1);
                doIndent(indent);
                printf("}\n");
                break;
            }
            case STMT_RETURN: {
                doIndent(indent);
                printf("return ", node->attr.name);
                // print expr
                printf(";\n");
                break;
            }
            case STMT_IFELSE: {
                doIndent(indent);
                printf("if (");
                // print expr
                printf(") {\n");
                print_stmt(node->body, indent+1);
                doIndent(indent);
                printf("}\n");
                if (node->else_body != NULL) {
                    doIndent(indent);
                    printf("else {\n");
                    print_stmt(node->else_body, indent+1);
                    doIndent(indent);
                    printf("}\n");
                }
                break;
            }
            case STMT_READ: {
                doIndent(indent);
                printf("READ: ");
                // print expr
                printf("\n");
                break;
            }
            case STMT_WRITE: {
                doIndent(indent);
                printf("WRITE: ");
                // print expr
                printf("\n");
                break;
            }
        }
        node = node->next;
    }
}