%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
int yydebug = 0;
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

prog: stmts
     ;

stmts:
          | stmt SEMICOLON stmts
          {
            printf("stmts passed \n");
          }
          ;

stmt:
          | assignment
          | exp
          {
            printf("Assignment passed \n");
          }
          ;

assignment: ID EQUALS exp

/**TODO: CHECK IF THIS LOGIC IS RIGHT**/
exp:
  |ID OP exp
  |ID
  {
    printf("Statement Passed \n");
  }
  ;




%%
