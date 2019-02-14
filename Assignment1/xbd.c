/*************************************************************
 Name: Jan Domingo
 username: CSSC0463
 Project: CS530 Assignment 1
 File: xbd.c
 Notes: Output should match that as the unix command "xxd <filename>"
 Date Due: February 18, 2019
 Assignment Instructions:
    Develop, test and deliver a basic hexadecimal file dump 'xbd'
    The basic hexdump program will open a regular type file (containing binary or text/ASCII content),
    read every byte in the file and write both the ASCII hex value for that byte as well as it’s printable
    (human-readable) character (characters, digits, symbols) to standard output.
    For bytes forming non-printable characters, print a ‘.’ character (a dot/period character, i.e. hex value 2E).
*************************************************************/

#include <stdio.h>

//TODO: Figure out how to read files and get user input.
//TODO: Figure out how to run in terminal

int main (int argc, char **argv) {
    if (argc = 2) {
        FILE *fp = fopen(argv[1], "r");  //Reads the parameter in argv[1]. (arg[0] is the name of the program)
        if (fp == NULL) {
            printf("File could not be opened.");
            return -1;
        }
        while (!feof(fp)) {
            //fscanf(fp, "%d", &num);
            //printf("number = %d\n",num)
        }
    }
}