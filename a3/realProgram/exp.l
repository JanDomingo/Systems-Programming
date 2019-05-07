/*
NAME: JAN DOMINGO
CLASS ACCOUNT: CSSC0463
CLASS INFORMATION: CS570, SPRING 2019, SECTION 1
ASSIGNMENT INFORMATION: ASSIGNMENT #3, COMPILER PARSING AND GRAMMAR
FILENAME: exp.L: FLEX PARSING
*/

%{
#include <stdio.h>
#include "y.tab.h"
extern int statementnum = 0;
%}

%%
                                    /*TODO: DOUBLE CHECK IF VALID VARIABLE NAMES ARE ACTUALLY VALID ACCORDING TO EX.TXT*/
[a-z][a-zA-Z0-9]*|[_]*[A-Z]*        ECHO; return ID;      /*Valid variable name if start with a lowercase letter or underscore or valid if all caps*/
[=]                                 ECHO; return EQUALS;
[+\-\*\%\/]                         ECHO; return OP;              /*Operand*/
\(                                  ECHO; return OPARENTHESIS;    /*Opening parenthesis*/
\)                                  ECHO; return CPARENTHESIS;    /*Closing parenthsesis*/
;                                   ECHO; return SEMICOLON;
\n                                  ECHO; statementnum++; return NEWLINE;
[ \t]+                              /*Ignore whitespace*/
[0-9]                               ECHO; return NUM;
.                                   ECHO; return INVALIDCHAR;
%%
