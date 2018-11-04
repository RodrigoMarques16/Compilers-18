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

"+"  { yylval.charValue = yytext[0]; return PLUS;   }
"-"  { yylval.charValue = yytext[0]; return MINUS;  }
"*"  { yylval.charValue = yytext[0]; return MULT;   }
"/"  { yylval.charValue = yytext[0]; return DIV;    }
"\%" { yylval.charValue = yytext[0]; return MOD;    } 
"="  { yylval.charValue = yytext[0]; return ASSIGN; }
"==" { yylval.charValue = yytext[0]; return EQ;     }
"!=" { yylval.charValue = yytext[0]; return DIF;    }
"<"  { yylval.charValue = yytext[0]; return LT;     }
"<=" { yylval.charValue = yytext[0]; return LTE;    } 
">"  { yylval.charValue = yytext[0]; return GT;     }
">=" { yylval.charValue = yytext[0]; return GTE;    }

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
   return TK_INT; 
}  // Integers

\-?[0-9].[0-9]+ {
    yylval.floatValue = atof(yytext);
    return TK_FLOAT;
} // Floats

"true" { 
    yylval.boolValue = 1;
    return TK_BOOLEAN; 
}

"false" { 
    yylval.boolValue = 0;
    return TK_BOOLEAN;        
}

[a-zA-Z]+ { 
    yylval.stringValue = strdup(yytext); 
    return ID; 
}

.  { yyerror("unexpected character"); }

%%
