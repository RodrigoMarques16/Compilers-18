#include "ast.h" // AST header

void doIndent(int indent) {
    for(int i = 0; i < indent*2; i++) {
        printf("%c", INDENT_CHAR);
    }
}

void printTree(Node* node) {
    printf("Abstract Syntax Tree:\n");
    while(node != NULL) {
        print_decl(node, 0);
        printf("\n");
        node = node->next;
    }
}