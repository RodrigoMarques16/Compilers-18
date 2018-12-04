#ifndef __stack_h__
#define __stack_h__

#include "ast.h"
#include "symbol.h"
#include "scope.h"

typedef enum {
    kLDC,   // Load const
    kRDI,   // Read immediate
    kLOD,   // Load contents of address
    kADI,   // Add immediate
    kMPI,   // Mult immediate
    kSBI,   // Sub immediate
    kDVI,   // Integer division
    kMOD,   // Modulo
    kWRI,   // Write immediate
    kSTO,   // Stop
    kFJP,   // False Jump
    kUJP,   // Unconditional Jump
    kEQU,   // Equal
    kNEQ,   // Not Equal
    kLST,   // Lesser than
    kLEQ,   // Lesser or equal
    kGRT,   // Greater than
    kGEQ,   // Greater or equal
    kLABEL, // Label
    kMOV,   // Move
    kENT,   // Enter block
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
Instr* make_instr_simple(instr_t kind);
Instr* head(InstrList* list);
InstrList* make_instrlist(Instr* instr, InstrList* next);
InstrList* tail(InstrList* list);
InstrList* append(InstrList* list, InstrList* next);
//InstrList* append(Instr* instr, InstrList* list);

InstrList* compile_pcode(Node* root);
InstrList* compile_function(Node* func);
InstrList* compile_var(Node* func);
InstrList* compile_stmt(Node* body);
InstrList* compile_expr(Expr* expr);

void printInstr(Instr* instr);
void printListIntrs(InstrList* list);
expr_t opToInstr(int op);
void initSymbolTable();

#endif
