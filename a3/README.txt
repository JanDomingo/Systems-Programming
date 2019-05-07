NAME: JAN DOMINGO
CLASS ACCOUNT: CSSC0463
CLASS INFORMATION: CS570, SPRING 2019, SECTION 1
ASSIGNMENT INFORMATION: ASSIGNMENT #3, COMPILER PARSING AND GRAMMAR
FILENAME: readme.txt

The Grammar:
This program follows the design of a BNF grammar for evaluating valid statements. The program starts with the stmt, a representation for the entire line statement in ex.txt. From stmt it can then shift into assignment, or recurse back to stmt and assignment. This allows for recursion to continuously read through the statement. Assignment then contains the recognition of ID EQUALS exp SEMICOLON NEWLINE. 
Example of a valid statement: 
first = a + b;
first   =     a + b     ;        \n
ID    EQUALS   exp  SEMICOLON  NEWLINE

This would return a valid statement, any other cases would return an error as it is not a valid assignment. The state exp evaluates the expression. Since an expression can be any amount of length of ID OP ID, exp is recursive with ID OP and the only other option must be an ID for the last variable in a statement. Other scenarios in exp may be an opening parenthesis with an exp in between with the closing parenthesis. 
Example of a valid expression:
a + b + (c + d)
a  +  b  +       (      c + d      )
ID OP ID OP OPARENTHESIS exp CPARENTHESIS


File Manifest (Files created by me):
exp.y
exp.l
Makefile
testfile.txt
ex.txt	(Statements given by instructor)
README.txt

Compile and Run Instructions:
Since the compile commands are included in the makefile, the steps to run the program is simplified:
1. Use the terminal and get in the same directory as exp.y and exp.l 
2. Type make
3. Type ./exp

Issues:
1. When the statements are printed, the valid statement message appears below the statement itself. However, on invalid statements, the message appears above the statement itself.
2. On invalid statement #9 the error should be expecting a CPARENTHESIS. The current print statement expects an ID OR OPARENTHESIS. 
3. On the last statement, a new line does not occur and is printed on the same line as the user command.

Lessons Learned/Significant Findings:
How make parse in Lex/Flex and how to produce grammar in Yacc/Bison. How recursion works in producing a syntax tree and how compilers identify proper syntax in programming languages. How to use the Atom text editor and install extensions, specifically for Flex and Bison. 

Additional Information:
N/A