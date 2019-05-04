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
statement:
          | statement assignment
          ;

assignment: ID EQUALS exp
  {
    printf("That is a valid assignment\n");
  }

/**TODO: CHECK IF THIS LOGIC IS RIGHT**/
exp:
  |ID exp
  |OP exp
  |ID SEMICOLON

  {
    printf("Expression valid\n");
  }


%%
