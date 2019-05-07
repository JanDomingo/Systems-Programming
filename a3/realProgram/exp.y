%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *
extern FILE *yyin;
extern int statementnum;
int yylex();
int yyerror(char *s);
int yydebug = 0;
%}

%error-verbose
%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON NEWLINE NUM INVALIDCHAR
%%

stmt:     assignment
          | stmt assignment
          ;

assignment: ID EQUALS exp SEMICOLON NEWLINE{printf ("Statement #%d. Valid Statement\n\n", statementnum);}  /**TODO: FIGURE OUT HOW TO REPRINT STATEMENT**/
          | ID EQUALS error NEWLINE
          | ID EQUALS error SEMICOLON NEWLINE
          | error NEWLINE
          | ID OP ID error
          ;

exp:      ID OP exp
          | ID
          | OPARENTHESIS exp CPARENTHESIS
          ;


%%
int yyerror(char *str)
{
  fprintf(stderr, "\nStatement #%d. %s\n", statementnum+1, str); /*TODO: FIGURE OUT HOW TO PROPERLY NAME ERRORS AND HAVE MULTIPLE ERRORS*/
  return 1;
}
int yywrap()
{
  return 1;
}
int main()
{
  yyin = fopen("ex.txt", "r");
  printf("NOW READING FILE INPUT:\n\n");
  yyparse();
  return 0;
}
