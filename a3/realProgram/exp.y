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

prog:     stmts
          ;

stmts:
          | stmt stmts
          ;

stmt:
          | assignment
          | exp
          ;

assignment: ID EQUALS exp SEMICOLON
          {
            printf("Assignment passed \n");
          }

/**TODO: CHECK IF THIS LOGIC IS RIGHT**/
exp:
  |ID OP exp
  |ID
  |OPARENTHESIS exp CPARENTHESIS
  {
    printf("Expression passed \n");
  }
  ;




%%
