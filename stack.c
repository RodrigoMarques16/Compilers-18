#include "stack.h"
#include "parser.h"
#include "symbol.h"

Scope* global_scope;
Scope* current_scope;
int label_count = 0;

void initSymbolTable() {
    global_scope = enterScope(NULL);
    current_scope = global_scope;
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
                InstrList* list = compile_var(node, global_scope);
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

    Symbol* symbol = make_symbol(func->attr->name, func->attr->type);
    bind(global_scope, symbol);

    Instr* label = make_instr_string(kLABEL, symbol->name);
    code = append(code, make_instrlist(label, NULL));

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
InstrList* compile_var(Node* var, Scope* scope) {
    dbgprintf("Compiling var decl\n");
    InstrList* code = NULL;
    
    // Bind variable to its scope
    bind(scope, var->symbol);

    // Vars don't have initilization yet
    //
    //if (var->attr != NULL) {
    //    code = compile_expr(var->attr);
    //}*/

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
                
                if(check_type(node->attr) == 0)
                    exit(-1);
                
                InstrList* list = compile_expr(node->attr->right);
                code = append(code, list);

                Instr* instr = make_instr_string(kSTO, node->attr->left->name);
                code = append_instr(code, instr);

                break;
            }
            case STMT_IFELSE: {
                InstrList* list = compile_expr(node->attr);
                code = append(code, list);

                char* label_false = generate_label();
                char* label_after = generate_label();

                Instr* instr = make_instr_string(kFJP, label_false);
                code = append_instr(code, instr);

                // If true
                list = compile_stmt(node->body);
                code = append(code, list);
                instr = make_instr_string(kUJP, label_after);
                code = append_instr(code, instr);

                // If false;
                instr = make_instr_string(kLABEL, label_false);
                code = append_instr(code, instr);
                list = compile_stmt(node->else_body);
                code = append(code, list);
                
                instr = make_instr_string(kLABEL, label_after);
                code = append_instr(code, instr);

                label_count++;
                break;
            }
            case STMT_WHILE: {
                break;
            }
            case STMT_RETURN: {
                break;
            }
            case STMT_DECL: {
                dbgprintf("Compiling local declaration\n");
                Symbol* symbol = make_symbol(node->attr->name, node->attr->type);
                bind(current_scope, symbol);
                break;
            }
            case STMT_BLOCK: {
                current_scope = enterScope(current_scope);
                InstrList* list = compile_stmt(node->body);
                code = append(code, list);
                current_scope = leaveScope(current_scope);
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
            Symbol* symbol = lookup(current_scope, expr->name);
            if (symbol == NULL) {
                printf("'%s' is undefined\n", expr->name);
            }else { 
                Instr* instr = make_instr_string(kLOD, expr->name);
                return make_instrlist(instr, NULL); 
            }
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
            printf("!!!!!!!!!!!!!!!\n");
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

Instr* make_instr_string(instr_t kind, char* arg) {
    Instr* instr = (Instr*) malloc(sizeof(Instr));
    instr->kind  = kind;
    instr->name  = arg;
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

InstrList* append_instr(InstrList* list, Instr* next) {
    return append(list, make_instrlist(next, NULL));
}

int check_type(Expr* expr) {
    Symbol* symbol = lookup(current_scope, expr->left->name);

    if (symbol == NULL)
        return 0;

    /*
    if( symbol->type->kind == expr->right->type->kind) {
        return 1;
    }

    printf("!!Mismatching types!!\n");*/
    return 1;
}

void printInstr(Instr* instr) {
    switch(instr->kind) {
        case kLABEL: {
            printf("%s:\n", instr->name);
            break;
        }
        case kLDC: {
            printf("LDC %d\n", instr->arg);
            break;
        }
        case kLOD: {
            printf("LOD '%s'\n", instr->name);
            break;
        } 
        case kRDI: {
            printf("RDI %d\n", instr->arg);
            break;
        }
        case kWRI: {
            printf("WRI %d\n", instr->arg);
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
            printf("STO '%s'\n", instr->name);
            break;
        }                 
        case kFJP: {
            printf("FJP %s\n", instr->name);
            break;
        }                 
        case kUJP: {
            printf("UJP %s\n", instr->name);
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


char* generate_label() {
    char* label = (char*) malloc(12);
    sprintf(label, "label_%d", label_count++);
    return label;
}