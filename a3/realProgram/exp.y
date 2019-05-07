%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
extern FILE *yyin;
int yylex();
int yyerror(char *s);
int yydebug = 0;
%}

%error-verbose
%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON NEWLINE INVALIDCHAR
%%

stmt:     assignment
          | stmt assignment
          ;

assignment: ID EQUALS exp SEMICOLON NEWLINE{printf ("Valid Statement\n");}  /**TODO: FIGURE OUT HOW TO REPRINT STATEMENT**/
          | ID EQUALS error
          | error NEWLINE
          ;

exp:
          | ID OP exp
          | ID
          | prnthsis
          ;


prnthsis: OPARENTHESIS exp CPARENTHESIS
          | OP OPARENTHESIS exp SEMICOLON error { ; printf("ERROR: Missing closing parenthsesis. Expected')a'\n");}
          ;

%%
int yyerror(char *str)
{
  fprintf(stderr, "%s\n", str); /*TODO: FIGURE OUT HOW TO PROPERLY NAME ERRORS AND HAVE MULTIPLE ERRORS*/
  return 1;
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
