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

void printOperator(int opcode) {
    char* op = "(OPCODE N/A)";
    switch(opcode) {
        case 265: { op = "=";  break;  } 
        case 266: { op = "+";  break;  } 
        case 267: { op = "-";  break;  } 
        case 268: { op = "*";  break;  } 
        case 269: { op = "/";  break;  } 
        case 270: { op = "%";  break;  } 
        case 271: { op = "=="; break;  }
        case 272: { op = "!="; break;  }
        case LT: { op = "<";  break;  }
        case 274: { op = "<="; break;  }
        case 275: { op = ">";  break;  }
        case 276: { op = ">="; break;  }
    }
    printf("%s", op);
}