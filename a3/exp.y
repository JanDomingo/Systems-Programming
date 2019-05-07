/*
NAME: JAN DOMINGO
CLASS ACCOUNT: CSSC0463
CLASS INFORMATION: CS570, SPRING 2019, SECTION 1
ASSIGNMENT INFORMATION: ASSIGNMENT #3, COMPILER PARSING AND GRAMMAR
FILENAME: exp.y: BISON GRAMMAR
*/

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

%error-verbose  /*PRINTS THE SPECIFICS OF THE SYNTAX ERROR*/
%token ID EQUALS OP OPARENTHESIS CPARENTHESIS SEMICOLON NEWLINE NUM INVALIDCHAR /*TOKEN DECLARATIONS FROM FLEX FILE*/
%% /*START OF BISON GRAMMAR SECTION*/

/*START OF PROGRAM TO READ IN ASSIGNMENT*/
stmt:     assignment
          | stmt assignment /*RECURSION TO KEEP READING ASSIGNMENT*/
          ;

/*THIS STATE PARSES THE ASSIGNMENT 'ID EQUALS exp SEMICOLON NEWLINE. ANYTHING ELSE IS AN ERROR'*/
assignment: ID EQUALS exp SEMICOLON NEWLINE{printf ("Statement #%d. Valid Statement\n\n", statementnum);}
          | ID EQUALS error NEWLINE
          | ID EQUALS error SEMICOLON NEWLINE
          | error NEWLINE
          | ID OP ID error
          ;

/*THIS STATE PARSES AN EXPRESSION WHICH CONSITS OF A RECUERSION OF ID OP ID OR WITH PARENTHESIS*/
exp:      ID OP exp
          | ID
          | OPARENTHESIS exp CPARENTHESIS
          ;

%% /*END OF BISON GRAMMAR SECTION*/

int yyerror(char *str)
{
  /*STDERR CONTAINS THE VERBOSE ERROR STATEMENTS*/
  fprintf(stderr, "\nStatement #%d. %s\n", statementnum+1, str);
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
