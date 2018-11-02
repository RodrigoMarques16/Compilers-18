// Tokens
%token <stringValue> ID
%token INT FLOAT BOOLEAN
%token TYPE_INT TYPE_FLOAT TYPE_BOOLEAN
%token ASSIGN PLUS MINUS MULT DIV MOD EQ DIF LT LTE GT GTE
%token IF THEN ELSE WHILE RETURN TRUE FALSE
%token PAR_OPEN PAR_CLOSE RECT_OPEN RECT_CLOSE BRACKET_OPEN BRACKET_CLOSE
%token SEMI COMMA
%token COMMENT_BEGIN COMMENT_END
%token MAIN READ WRITE

// Operator associativity & precedence
%left PLUS MINUS
%left MULT DIV MOD
%left PAR_OPEN PAR_CLOSE
%left BRACKET_CLOSE
%right BRACKET_OPEN ELSE
%nonassoc ASSIGN

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
    int intValue;
    int boolValue;
    float floatValue;
    char charValue;
    char* stringValue;
    Node* nodeValue;
    Type* typeValue;
    ParamList* paramValue;
}

%type <intValue>   INT
%type <floatValue> FLOAT
%type <boolValue>  BOOLEAN
%type <nodeValue>  program decl-list decl fun-decl var-decl
%type <nodeValue>  expr statement statement-list compound-stmt
%type <nodeValue>  assign-stmt while-stmt return-stmt ifelse-stmt read-stmt write-stmt
%type <typeValue>  type
%type <paramValue> param-list params param

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Node* root;
}

%%
program: decl-list;
;
decl-list: { $$ = NULL; }
         | decl-list decl {  
             if ($1 == NULL) {
                 $$ = root = append_decl($2, $1); 
             } else $$ = append_decl($2, $1); 
         }
;
decl: var-decl 
    | fun-decl 
;
var-decl: type ID SEMI { 
    $$ = make_decl_var($1, $2);
}
;
fun-decl: type ID PAR_OPEN params PAR_CLOSE compound-stmt {
    $$ = make_decl_function($1, $2, $4, $6);
}
;
params: { $$ = NULL; }
      | param-list
;
param-list: param-list COMMA param { $$ = append_param($3, $1); }
          | param
;
param: type ID { $$ = make_param($2, $1); }
;

type: TYPE_INT     { $$ = make_type_simple(T_INTEGER); }
    | TYPE_FLOAT   { $$ = make_type_simple(T_FLOAT);   }
    | TYPE_BOOLEAN { $$ = make_type_simple(T_BOOL);    }
;
statement-list: { $$ = NULL; }
              | statement-list statement { $$ = append_stmt($2, $1); }
;
statement: assign-stmt 
         | compound-stmt
         | while-stmt
         | return-stmt
         | ifelse-stmt
         | SEMI { $$ = NULL; }
         | var-decl { $$ = make_stmt_decl($1); }
         | read-stmt
         | write-stmt
;
compound-stmt: BRACKET_OPEN statement-list BRACKET_CLOSE 
                { $$ = make_stmt_block($2); }
;
assign-stmt: ID ASSIGN expr SEMI 
                { $$ = make_stmt_assign($1, $3); }
;
while-stmt: WHILE PAR_OPEN expr PAR_CLOSE statement
                { $$ = make_stmt_while($3, $5); }
;
return-stmt: RETURN SEMI { $$ = make_stmt_return(NULL); }
           | RETURN expr SEMI { $$ = make_stmt_return($2); }
;
ifelse-stmt: IF PAR_OPEN expr PAR_CLOSE statement 
                { $$ = make_stmt_ifelse($3, $5, NULL); }
           | IF PAR_OPEN expr PAR_CLOSE statement ELSE statement
                { $$ = make_stmt_ifelse($3, $5, $7); }
;
read-stmt: READ PAR_OPEN expr PAR_CLOSE SEMI 
                { $$ = make_stmt_io(STMT_READ, $3); }
;
write-stmt: WRITE PAR_OPEN expr PAR_CLOSE SEMI 
                { $$ = make_stmt_io(STMT_WRITE, $3); }
;
expr: INT {}
;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
