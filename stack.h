#ifndef __stack_h__
#define __stack_h__

#include "ast.h"

typedef enum {
    kLDC,   // Load const
    kRDI,   // Read immediate
    kADI,   // Add immediate
    kMPI,   // Mult immediate
    kSBI,   // Sub immediate
    kLOD,   // Load contents of address
    kWRI,   // Write immediate
    kSTO,   // Stop
    kFJP,   // False Jump
    kUJP,   // Unconditional Jump
    kGRT,   // Greater than
    kLST,   // Lesser than
    kLEQ,   // Lesser or equal
    kGEQ,   // Greater or equal
    kEQU,   // Equal
    kNEQ,   // Not Equal
    kLABEL, // Label
    kMOV,   // Move
    kMOD,   // Modulo
    kENT,   // Enter block
    kNOT    // Boolean not
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
InstrList* compile_function(Node* func);
InstrList* compile_var(Node* func);
InstrList* compile_stmt(Node* body);
InstrList* compile_expr(Expr* expr);

void printInstr(Instr* instr);
void printListIntrs(InstrList* list);

#endif
