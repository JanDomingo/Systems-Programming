%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
extern FILE *yyin;
int yylex();
int yyerror(char *s);
int yydebug = 0;
%}

%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON OTHER
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
            printf("Assignment passed \n"); /*TODO: LOW PRIORITY: FIGURE OUT HOW TO PRINT ENTIRE STATEMENT*/
          }

exp:
          | ID OP exp
          | ID
          | prnthsis
          | exp error '\n'  /**TODO: CHANGE THIS ERROR TO A PRINT STATEMENT. his error occurs when there is a double == in assignment. This continues token input after an error occurs */
          {
            printf("Expression passed \n");
          }
          ;

prnthsis: OPARENTHESIS exp CPARENTHESIS
          ;
%%

int yyerror(char *str)
{
  fprintf(stderr, "YOU HAVE AN ERROR: %s\n", str); /*TODO: FIGURE OUT HOW TO PROPERLY NAME ERRORS AND HAVE MULTIPLE ERRORS*/
}

int yywrap()
{
  return 1;
}

int main()
{
  yyin = fopen("todelete.txt", "r");
  printf("NOW READING FILE INPUT\n");
  yyparse();
  return 0;
}
