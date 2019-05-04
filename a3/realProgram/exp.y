%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *

void yyerror(const char *str)
{
  fprintf(stderr, "error: %s\n", str);
}

int yywrap()
{
  return 1;
}

main()
{
  yyparse();
}
%}

%token ID EQUALS OP OPARENTHESIS EPARENTHESIS SEMICOLON

%%
identifier:
          | identifier assignment
          ;

assignment:
          | ID EQUALS
          | expression
          ;

expression:
          | ID
          | OP
          | expression
          | prnthsis
          | SEMICOLON
          {
            printf("expression created\n");
          }
          ;

prnthsis:
          | OPARENTHESIS
          | expression
          | EPARENTHESIS
          {
            printf("parenthsis found\n");
          }
          ;
%%
