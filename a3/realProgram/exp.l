%{
#include <stdio.h>
%}

%%
                                                  /*TODO: DOUBLE CHECK IF VALID VARIABLE NAMES ARE ACTUALLY VALID ACCORDING TO EX.TXT*/
[_]*[a-z][a-zA-z0-9]*     printf("VALID ");        /*Valid variable name if start with a lowercase letter or underscore*/
[_]*[A-Z]*                printf("VALID  ");       /*Valid if all caps*/
[A-Z0-9][a-zA-z0-9]*      printf("INVALID ");      /*Invalid if start with an uppercase char or number*/
[=]                       printf("EQUALS ");
[+\-\*\%\/]               printf("OP ");            /*Operand*/
\(                        printf("OPARENTHESIS "); /*Opening parenthesis*/
\)                        printf("EPARENTHESIS "); /*Ending parenthsesis*/
;                         printf("SEMICOLON ");
\n                        printf("\n");
[ \t]+                    /*Ignore whitespace*/
%%
