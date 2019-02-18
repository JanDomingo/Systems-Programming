Name: Jan Domingo
Class Account: CSSC0463
Class Information: CS570, Spring 2019, Section 1
Assignment Information: Assignment #1, Hexadecimal Dump File
Filename: README.txt

File Manifest:
Makefile
README.txt
xbd.h	//Header File
xbd.c	//Source Code


Compile Instructions:
If a xbd.exe file is not created yet or cannot be located, locate the working directory of xbd.c using the command line and run "gcc xbd.c -o xbd" to create an executable file name xbd from the xbd.c program. 
Compiling can be done by also just typing "make" as long as the xbd.c, xbd.h, and Makefile are all in the same directory.

Operating Instructions:
After compiling, locate the working directory of the xbd.exe file. The program is ran by typing "xbd <filename>" or "xbd -b <filename". Specifying the -b flag will only print the results of the ascii characters in <filename> in binary values instead of hexadecimal. 

List/description of novel/significant design decisions:
1. The main function runs the file pointer and can choose between two functions. If the user specified "-b" it will run the printBin function. If no flags were specified, then it will run the printHex function. 
2. To print the binary numbers, a bitwise shift right was performed and printed each binary number as the pointer iterated through the characters. On the contrary, to print out the ASCII values from the file, the characters were saved into an array of characters, evaluated for non-printable characters, then printed.

List/description of any extra features/algorithms/functionality you included which were not required:
No extra features/functionalities were implemented in this program. The only algorithm included is found in line 41 and 92 which calculates the amount of spaces needed to print in order to display and align the user input string in the proper column. 

List/description of all known deficiencies or bugs:
1. The said algorithm above does not work properly with all string lengths. The last set of characters or strings may appear to be out of alignment with the column in which it is supposed to be displayed in. There is a problem with the algorithms in both the printHex() and printBin() functions.
2. A few characters may appear before printing the first address in the -b mode possibly due to printing an uninitialized textPrint array. This error was found after creating the header file. 
3. The EOF marker prints as the last character either as ffffffff or in -b mode as 11111111. 


Lessons Learned:
Basics of C, how to read files, pass in arguments in command line, syntax, compiling, built in libraries, header files, and make files. 