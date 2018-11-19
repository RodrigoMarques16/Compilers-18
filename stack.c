#include "stack.h"

InstrList* compile_pcode(Node* root) {
    InstrList* pcode = NULL;
    Node* node = root;
    dbgprintf("Compiling declaration\n");
    // Iterate the declaration list
    while(node != NULL) {
        switch(node->kind.decl) {
            case DECL_VAR: {
                dbgprintf("Compiling var decl\n");
                break;
            }
            case DECL_FUNCTION: {
                dbgprintf("Compiling function decl\n");
                compile_function(node->body);
                break;
            }
        }
        node = node->next;
    }
}

InstrList* compile_stmt(Node* body) {
    // For now this function only looks for exprs
    InstrList* pcode = NULL;
    Node* node = body;
    while(node != NULL) {
        switch(node->kind.stmt) {
            case STMT_BLOCK {
                compile_block(node->next);
            }
        }
        if (node->attr != NULL) {
            dbgprintf("Compiling expr\n");
            append(pcode, compile_expr(node->attr));
        }
        node = node->next;
    }
    return pcode;
}

InstrList* compile_expr(Expr* expr) {
    if (expr == NULL) {
        printf("ERROR: CONVERTING NULL EXPR TO INSTR\n");
        return NULL;
    }
    switch(expr->kind) {
        case EXPR_ID: {
            // nothing yet
            break;
        }
        case EXPR_CONSTANT: {
            // hardcoded for ints
            Instr* instr = make_instr(LDC, expr->val.int_value);
            return make_instrlist(instr, NULL);
        }
        case EXPR_ARITHMETIC: {
            InstrList* left = compile_expr(expr->left);
            InstrList* right = compile_expr(expr->right);
            Instr* instr = make_instr(ADI, -1);
            InstrList* list = make_instrlist(instr, NULL);
            left = append(right, left);
            left = append(list, left);
            return left;
        }
        case EXPR_RELATIONAL: {
            // nothing yet
            break;
        }
        case EXPR_ASSIGN: {
            // nothing yet
            break;
        }
    }
}

Instr* make_instr(instr_t kind, int arg) {
    Instr* instr = (Instr*) malloc(sizeof(Instr));
    instr->kind = kind;
    instr->arg  = arg;
    return instr;
}

InstrList* make_instrlist(Instr* instr, InstrList* next) {
    InstrList* list = (InstrList*) malloc(sizeof(InstrList));
    list->instr = instr;
    list->next  = NULL;
    return list;
}

Instr* head(InstrList* list) {
    if (list != NULL) {
        return list->instr;
    }
    return NULL;
}

InstrList* tail(InstrList* list) {
    if (list != NULL) {
        return list->next;
    }
    return NULL;
}

/*InstrList* append(Instr* instr, InstrList* list) {
    InstrList* tmp = list;
    if (list == NULL){
        return make_instrlist(instr, NULL);
    }
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = make_instrlist(instr, NULL);
    return list;
}*/

InstrList* append(InstrList* list, InstrList* next) {
    InstrList* tmp = list;
    if (list == NULL){
        return next;
    }
    if(next == NULL) {
        return list;
    }
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = next;
    return list;
}

void printInstr(Instr* instr) {
    switch(instr->kind) {
        case LDC: {
            printf("LDC %d\n", instr->arg);
            break;
        }
        case ADI: {
            printf("ADI %d\n", instr->arg);
            break;
        }
        case MPI: {
            printf("MPI %d\n", instr->arg);
            break;
        }
        case SBI: {
            printf("SBI %d\n", instr->arg);
            break;
        }                                                                                                                                            
    }
}

void printListIntrs(InstrList* list) {
    printf("P-CODE:\n");
    while(list != NULL){
        printInstr(list->instr);
        list = list->next;                                                        
    }
}