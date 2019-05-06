%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
extern FILE *yyin;
int yylex();
int yyerrork();
int yyerror(char *s);
int yydebug = 1;
%}

%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON NEWLINE QUESTIONMARK
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

assignment: ID EQUALS exp SEMICOLON NEWLINE{printf ("Statement Passed\n");}  /**TODO: FIGURE OUT HOW TO REPRINT STATEMENT**/
          | assignmenterror
          ;

assignmenterror: ID EQUALS EQUALS error {yyerrork; yyclearin; printf("ERROR: Double equal sign. Expected '=' after ID\n");}
          | ID EQUALS exp NEWLINE error {yyerrork; yyclearin; printf("ERROR: No semicolon. Expected ';' after expression\n");}
          ;

exp:
          | ID OP exp
          | ID
          | prnthsis
          | experror
          {
            printf("Expression passed \n");
          }
          ;

experror:
          | OP OP error {yyerrork; yyclearin; printf("Double OP put together. Expected only one OP between ID");}
          | QUESTIONMARK error{yyerrork; yyclearin; printf("THERE IS A QUESTIONMARK INVALID!!!");}

prnthsis: OPARENTHESIS exp CPARENTHESIS
          ;
%%

int yyerror(char *str)
{
  fprintf(stderr, ""); /*TODO: FIGURE OUT HOW TO PROPERLY NAME ERRORS AND HAVE MULTIPLE ERRORS*/
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
