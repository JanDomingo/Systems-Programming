%{
  #include "bnfcalculator.tab.h"
%};

  int yylval;
%}

%%
"+"     { printf("PLUS\n"); }
"-"     { printf("MINUS\n"); }
"*"     { printf("TIMES\n"); }
"/"     { printf("DIVIDE\n"); }
"|"     { printf("ABS\n"); }
[0-9]+  { yylval = atoi(yytext); return NUMBER;}
\n      { return EOL; }
[ \t]   { }
.       { printf("Mystery character %c\n", *yytext); }
%%
