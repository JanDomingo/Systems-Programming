%{
#include <stdio.h>
#include <string.h>

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
          | identifier expression
          ;

expression:
          | ID OP ID
          {
            printf("expression created\n"); 
          }
          ;
%%
