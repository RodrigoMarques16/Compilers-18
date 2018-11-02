%{
// HEADERS
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {} // Whitespace

\n\r|\r\n|\n|\r { yyline++; } // Line breaks

#.*\n|\/\/.*\n {} // comments

"+"  { yylval.stringValue = strdup(yytext); return PLUS;   }
"-"  { yylval.stringValue = strdup(yytext); return MINUS;  }
"*"  { yylval.stringValue = strdup(yytext); return MULT;   }
"/"  { yylval.stringValue = strdup(yytext); return DIV;    }
"\%" { yylval.stringValue = strdup(yytext); return MOD;    } 
"="  { yylval.stringValue = strdup(yytext); return ASSIGN; }
"==" { yylval.stringValue = strdup(yytext); return EQ;     }
"!=" { yylval.stringValue = strdup(yytext); return DIF;    }
"<"  { yylval.stringValue = strdup(yytext); return LT;     }
"<=" { yylval.stringValue = strdup(yytext); return LTE;    } 
">"  { yylval.stringValue = strdup(yytext); return GT;     }
">=" { yylval.stringValue = strdup(yytext); return GTE;    }

"("  { return PAR_OPEN; }
")"  { return PAR_CLOSE; }
"["  { return RECT_OPEN; }
"]"  { return RECT_CLOSE; }
"{"  { return BRACKET_OPEN; }
"}"  { return BRACKET_CLOSE; }
"/*" { return COMMENT_BEGIN; }
"*/" { return COMMENT_END; }
";"  { return SEMI; }
","  { return COMMA; }
 
"int"    { return TYPE_INT; }
"float"  { return TYPE_FLOAT; }
"bool"   { return TYPE_BOOLEAN; }
"if"     { return IF; }
"then"   { return THEN; }
"else"   { return ELSE; }
"while"  { return WHILE; }
"return" { return RETURN; }
"printf" { return WRITE; }
"scanf"  { return READ; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);  
   return INT; 
}  // Integers

\-?[0-9].[0-9]+ {
    yylval.floatValue = atof(yytext);
    return FLOAT;
} // Floats

"true" { 
    yylval.boolValue = 1;
    return TRUE; 
}

"false" { 
    yylval.boolValue = 0;
    return FALSE;        
}

[a-zA-Z]+ { 
    yylval.stringValue = strdup(yytext); 
    return ID; 
}

.  { yyerror("unexpected character"); }

%%
