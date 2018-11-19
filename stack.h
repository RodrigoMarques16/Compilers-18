#ifndef __stack_h__
#define __stack_h__

#include "ast.h"

typedef enum {
    LDC,    // Load const
    ADI,    // Add immediate
    MPI,    // Mult immediate
    SBI     // Sub immediate
} instr_t;  

typedef struct _Instr {
    instr_t kind;
    int arg;
} Instr;

typedef struct _InstrList {
    Instr* instr;
    struct _InstrList* next;
} InstrList;

Instr* make_instr(instr_t kind, int arg);
Instr* head(InstrList* list);
InstrList* make_instrlist(Instr* instr, InstrList* next);
InstrList* tail(InstrList* list);
InstrList* append(InstrList* list, InstrList* next);
//InstrList* append(Instr* instr, InstrList* list);

InstrList* compile_pcode(Node* root);
InstrList* compile_stmt(Node* body);
InstrList* compile_expr(Expr* expr);

void printInstr(Instr* instr);
void printListIntrs(InstrList* list);

#endif
