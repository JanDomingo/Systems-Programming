%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
int yydebug = 1;
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
          | stmt error '\n'
          ;

stmt:
          | assignment
          | exp
          | stmt error ';'
          ;

assignment: ID EQUALS exp

/**TODO: CHECK IF THIS LOGIC IS RIGHT**/
exp:
  |ID OP exp
  |ID
  |OPARENTHESIS exp CPARENTHESIS
  {
    printf("That is a valid expression");
  }
  ;

prnthsis:
  |ID OP prnthsis
  |ID CPARENTHESIS
  {
    printf("parenthsis grouped");
  }
  ;



%%
