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
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

//TODO: Step 0: Figure out how to make methods in C
//TODO: Step 1: ---DONE---Read in the file, don't worry about terminal input yet
//TODO: Step 1.1: Figure out how to display in hex and binary
//TODO: Step 2: Figure out how to output the file contents into both hex and binary
//TODO: Step 3: Figure out how to run in terminal with user argument parameters
//TODO: Step 4: When done, clean up header comments, move Assignment Instructions to README file
//Make sure that main does not have a  lot of contents

int getChar();

int main () {
    getChar();
}

int getChar() {

    char line[255];

    FILE * fp;
    fp = fopen("helloworld.txt", "r");
    int ch = 0;
    int lines = 0;

    lines++;
    while(!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            lines++;
        }
    }
    fclose(fp);
    return lines;





}




