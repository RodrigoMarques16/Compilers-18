#include "stack.h"
#include "parser.h"
#include "symbol.h"

Scope* global_scope;

void initSymbolTable() {
    global_scope = enterScope(NULL);
}

/*
 * Iterate through a programs declarations and generate
 * for each of them generate their p-code.
 * 
 * root - First declaration of a program
 */
InstrList* compile_pcode(Node* root) {
    InstrList* pcode = NULL;
    Node* node = root;
    initSymbolTable();

    while(node != NULL) {
        switch(node->kind.decl) {
            case DECL_VAR: {
                InstrList* list = compile_var(node, GLOBAL);
                pcode = append(pcode, list);
                break;
            }
            case DECL_FUNCTION: {
                InstrList* list = compile_function(node);
                pcode = append(pcode, list);
                break;
            }
        }
        node = node->next;
    }
    return pcode;
}

/*
 * Translate a function and its descendents to p-code
 * 
 * func - Node of a function declaration
 */
InstrList* compile_function(Node* func) {
    dbgprintf("Compiling function decl\n");
    InstrList* code = NULL;
    // TODO: code for function declaration
    Node* node = func->body;
    while(node != NULL) {
        InstrList* list = compile_stmt(node);
        code = append(code, list);
        node = node->next;
    }
    return code;
}

/*
 * Translate a variable declaration to p-code
 * 
 * var - Node of a variable declaration
 */
InstrList* compile_var(Node* var, scope_t scope) {
    dbgprintf("Compiling var decl\n");
    InstrList* code = NULL;
    /*Symbol* symbol = make_symbol(
            kGLOBAL, 
            var->attr->type, 
            var->attr->name
    );
    */
    // Bind variable to its scope
    bind(global_scope, var->symbol);

    /* Vars don't have initilization
    if (var->attr != NULL) {
        code = compile_expr(var->attr);
    }*/

    return code;
}

/*
 * Translate a list of statements to p-code
 * 
 * stmt - Node of a statement
 */
InstrList* compile_stmt(Node* stmt) {
    InstrList* code = NULL;
    Node* node = stmt;
    while(node != NULL) {
        if (node->nodekind == K_EXPR) {
            dbgprintf("Compiling expr stmt\n");
            code = append(code, compile_expr(node->attr));
            node = node->next;
            continue;
        }
        switch(node->kind.stmt) {
            case STMT_ASSIGN: {
                dbgprintf("Compiling assignment\n");
                check_type(node->attr);
                InstrList* list = compile_expr(node->attr->right);
                Instr* instr = make_instr(kSTO, 1); // placeholder
                list = append(list, make_instrlist(instr, NULL));
                code = append(code, list);
                break;
            }
            case STMT_IFELSE: {
                break;
            }
            case STMT_WHILE: {
                break;
            }
            case STMT_RETURN: {
                break;
            }
            case STMT_DECL: {
                break;
            }
            case STMT_BLOCK: {
                InstrList* list = compile_stmt(node->body);
                code = append(code, list);
                break;
            }
            case STMT_READ: {
                break;
            }                   
            case STMT_WRITE: {
                break;
            }                                        
        }
        node = node->next;
    }
    return code;
}

/*
 * Translates an expression to P-code 
 */
InstrList* compile_expr(Expr* expr) {
    if (expr == NULL) {
        printf("ERROR: CONVERTING NULL EXPR TO INSTR\n");
        return NULL;
    }
    switch(expr->kind) {
        case EXPR_ID: {
            dbgprintf("Compiling variable symbol.\n");
            // TODO: symbol look up
            //Instr* instr = make_instr(kLOD, );
            break;
        }
        case EXPR_CONSTANT: {
            dbgprintf("Compiling constant value.\n");
            Instr* instr = make_instr(kLDC, expr->val.int_value);
            return make_instrlist(instr, NULL);
        }
        case EXPR_ARITHMETIC: {
            dbgprintf("Compiling arithmetic expression.\n");
            InstrList* left = compile_expr(expr->left);
            // save result to var   
            InstrList* right = compile_expr(expr->right);
            // save result to var
            left = append(left, right);
            instr_t kind = opToInstr(expr->op);
            Instr* instr = make_instr_simple(kind);
            InstrList* list = make_instrlist(instr, NULL);
            left = append(left, list);
            return left;
        }
        case EXPR_RELATIONAL: {
            InstrList* left = compile_expr(expr->left);
            // save result to var
            InstrList* right = compile_expr(expr->right);
            // save result to var
            instr_t kind = opToInstr(expr->op);
            Instr* instr = make_instr_simple(kind);
            InstrList* list = make_instrlist(instr, NULL);
            left = append(left, right);
            left = append(left, list);
            return left;
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

Instr* make_instr_simple(instr_t kind) {
    Instr* instr = (Instr*) malloc(sizeof(Instr));
    instr->kind = kind;
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
    if (list == NULL) {
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

int check_type(Expr* expr) {
    // Lookup expr->left
    return type == expr->right->type->kind;
}

void printInstr(Instr* instr) {
    switch(instr->kind) {
        case kLDC: {
            printf("LDC %d\n", instr->arg);
            break;
        }
        case kLOD: {
            printf("LOD %d\n", instr->arg);
            break;
        } 
        case kRDI: {
            printf("RDI %s\n", instr->arg);
            break;
        }
        case kWRI: {
            printf("WRI %s\n", instr->arg);
            break;
        }                         
        case kADI: {
            printf("ADI\n");
            break;
        }
        case kMPI: {
            printf("MPI\n");
            break;
        }
        case kSBI: {
            printf("SBI\n");
            break;
        }   
        case kDVI: {
            printf("DVI\n");
            break;
        }
        case kMOD: {
            printf("MOD\n");
            break;
        }     
        case kSTO: {
            printf("STO %d\n", instr->arg);
            break;
        }                 
        case kFJP: {
            printf("FJP %d\n", instr->arg);
            break;
        }                 
        case kUJP: {
            printf("UJP %d\n", instr->arg);
            break;
        }    
        case kEQU: {
            printf("EQU\n");
            break;
        }
        case kNEQ: {
            printf("NEQ\n");
            break;
        }
        case kLST: {
            printf("LST\n");
            break;
        }
        case kLEQ: {
            printf("LEQ\n");
        }
        case kGRT: {
            printf("GRT\n");
            break;
        }
        case kGEQ: {
            printf("GEQ\n");
            break;
        }
        case kMOV: {
            printf("MOV %d", instr->arg);
            break;
        }
        default: {
            printf("EXPR NOT FOUND\n");
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


expr_t opToInstr(int op) {
    switch(op) {
        case PLUS:  return kADI;
        case MINUS: return kSBI;
        case MULT:  return kMPI;
        case DIV:   return kDVI;
        case MOD:   return kMOD;
        case EQ:    return kEQU;
        case DIF:   return kNEQ;
        case LT:    return kLST;
        case LTE:   return kLEQ;
        case GT:    return kGRT;
        case GTE:   return kGEQ;
    }
}