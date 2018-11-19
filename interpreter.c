#include <stdio.h>

#include "parser.h"

int eval(Node* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  switch(expr->nodekind) {
    case K_EXPR: {
      
      break;
    }
    case K_STMT: {

      break;
    }
  }
}
int main(int argc, char** argv) {
    --argc; ++argv;
    if (argc != 0) {
        yyin = fopen(*argv, "r");
        if (!yyin) {
            printf("'%s': could not open file\n", *argv);
            return 1;
        }
    } //  yyin = stdin
    if (yyparse() == 0) {
        printf("parse sucessful\n");
        printTree(root);
        InstrList* instrs = compile_pcode(root);
        //printListIntrs(instrs);
        //printf("\nResult = %d\n", eval(root));
    }
    return 0;
}
