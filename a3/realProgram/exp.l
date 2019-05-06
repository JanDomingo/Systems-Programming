%{
#include <stdio.h>
#include "y.tab.h"

%}

%%
                                    /*TODO: DOUBLE CHECK IF VALID VARIABLE NAMES ARE ACTUALLY VALID ACCORDING TO EX.TXT*/
[a-z][a-zA-Z0-9]*|[_]*[A-Z]*        yylval=strdup(yytext); return ID;      /*Valid variable name if start with a lowercase letter or underscore or valid if all caps*/
[=]                                 return EQUALS;
[+\-\*\%\/]                         return OP;              /*Operand*/
\(                                  return OPARENTHESIS;    /*Opening parenthesis*/
\)                                  return CPARENTHESIS;    /*Closing parenthsesis*/
;                                   return SEMICOLON;
\n                                  return NEWLINE;
[ \t]+                              /*Ignore whitespace*/
[?]                                 return INVALIDCHAR;
%%
