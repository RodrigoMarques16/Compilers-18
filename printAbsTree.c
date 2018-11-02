#include "ast.h"
#include "parser.h"
#include <string.h>

#ifndef __PRINT_EXPR
#define __PRINT_EXPR

void printExprTab(Node* exp, char tab[]);

void printOp(int op) {
    /*
    switch(op) {
        case 259:
            printf("PLUS");
            break;
        case 260:
            printf("MINUS");
            break;
        case 261:
            printf("MULT");
            break;
        case 262:
            printf("DIV");
            break;
        case 263:
            printf("MOD");
            break;
        default: yyerror("Unknown operator!");
    }
    printf("\n");*/
}

void printExprTab(Node* exp, char tab[]) {
    /*char str[100];
    sprintf(str, "%s ", tab);
    if (exp->kind == E_INTEGER) {
        printf("INT %d\n", exp->attr.value);
    } else {
        printf("(\n%s", str);
        printExprTab(exp->attr.op.left, str);
        printf("%s", str);
        printOp(exp->attr.op.operator);
        printf("%s", str);
        printExprTab(exp->attr.op.right, str);
        printf("%s)\n", str);
    }*/
}

void printTree(Node* node) {
    printf("Abstract Syntax Tree:\n");
    while(node != NULL) {
        printf(".");
        print_type(node->type);
        node = node->next;
    }
    /*char tab[100] = " ";
    if (exp->kind == E_INTEGER) {
        printf("INT %d", exp->attr.value);
    } else {
        printf("(\n ");
        printExprTab(exp->attr.op.left, tab);
        printOp(exp->attr.op.operator);
        printExprTab(exp->attr.op.right, tab);
        printf(")\n");
    }*/
}

#endif