%{
#include <stdio.h>
%}

%%
[a-z][a-zA-z0-9]* printf("Valid variable name");
[A-Z0-9][a-zA-z0-9]*  printf("Invalid variable name");
%%
