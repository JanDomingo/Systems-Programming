%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
extern FILE *yyin;
int yylex();
int yyerrork();
int yyerror(char *s);
int yydebug = 0;
%}

%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON NEWLINE INVALIDCHAR
%%

prog:     stmts
          ;

stmts:
          | stmt
          | stmts stmt
          ;

stmt:
          | assignment
          | exp
          ;

assignment: ID EQUALS exp SEMICOLON NEWLINE{printf ("Valid Statement\n");}  /**TODO: FIGURE OUT HOW TO REPRINT STATEMENT**/
          | assignmenterror
          ;

assignmenterror: ID EQUALS EQUALS error {yyerrork; printf("ERROR: Double equal sign. Expected '=' after ID\n");}
          | ID EQUALS exp NEWLINE error {yyerrork; printf("ERROR: No semicolon. Expected ';' after expression\n");}
          ;

exp:
          | ID OP exp
          | ID
          | prnthsis
          | experror
          ;

experror:
          | OP OP error {yyerrork; printf("ERROR: Double OP put together. Expected only one OP between ID\n");}
          | INVALIDCHAR error {yyerrork; printf("ERROR: Invalid OP. Expected '+, -, *, mod, or /' \n");}

prnthsis: OPARENTHESIS exp CPARENTHESIS
          | OP OPARENTHESIS exp SEMICOLON error {yyerrork; printf("ERROR: Missing closing parenthsesis. Expected')a'\n");}
          | prnthsiserror
          ;

prnthsiserror:
          | OPARENTHESIS exp SEMICOLON error {yyerrork; printf("ERROR: Missing closing parenthsesis. Expected ')b'\n");}
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
  yyin = fopen("ex.txt", "r");
  printf("NOW READING FILE INPUT\n");
  yyparse();
  return 0;
}
