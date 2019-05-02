%{
  /****C stuff (headers, declarations, etc.) ****/
  #include <stdio.h>
  #include "test.tab.h"
  void showError();
%}

/*** Regular Expressions***/
numbers ([0-9])+

%%
/***Token specifications***/
"hello"   {return (STRING);}
{numbers} {return (NUM);}
";"       {return (SEMICOLON);}
.         {showError()}; return(OTHER);}

%%

/***C Functions (can be main or others)***/
void showError() {
  printf("Other input");
}
