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
%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON
%%
start:
          | assignment
          ;

assignment: ID EQUALS exp
  {
    printf("That is a valid assignment\n");
  }

/**TODO: CHECK IF THIS LOGIC IS RIGHT**/
exp: exp SEMICOLON
  |ID OP exp
  |ID

  {
    printf("Expression valid\n");
  }


%%
