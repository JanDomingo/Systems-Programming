/*************************************************************
 Name: Jan Domingo
 Class Account: CSSC0463
 Class Information: CS570, Spring 2019, Section 1
 Project: CS530 Assignment 1
 Assignment Information: Assignment #1, Hexadecimal Dump File
 File: xbd.c - Source Code
 Notes: Output should match that as the unix command "xxd <filename> or xxd -b <filename>"
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
#include <string.h>
#include <ctype.h>
#include "xbd.h"

/*************************************************************
function: printHex
Notes: This function prints the hexadecimal value of ascii
 characters specified in the input file
*************************************************************/
int printHex(FILE *fp) {
    int ch = 0;
    int p = 0;  //Acts as a pointer for the textPrint array
    int index = 0;  //Index is the value that is displayed in the leftmost column on the output
    char textPrint[16]; //Will hold the char values needed to print after displaying the hex values

    while (!feof(fp)) {
        ch = fgetc(fp);

        if (index % 16 == 0 || feof(fp)) {  //Print the address every 16 bytes, create a new line
            if (index != 0) {   //Prevents uninitialized array from being outputted in the beginning of the program
                if (feof(fp)) {
                    /*Formats the amount of space needed to properly align user string display
                    %16 gives the amount of leftover bytes. There are 3 spaces in a tab and 7 spaces between each
                    hex cluster. Combined, it is an additional 10 spaces. */
                    printf("%*s", (10 + (index % 16)), "");
                }
                //If the character is a non printable character, replace it with a "."
                int i = 0;
                for (i = 0; i < 16; i++) {
                    if (isprint(textPrint[i]) == 0 && (textPrint[i] != 0)) {
                        textPrint[i] = 46;
                    }
                }
                printf(" %s", textPrint);  //Prints the string of the user input
            }
            printf("\n");
            printf("%08x: ", index);    //Appends 0's in front of the address and prints in hex
            memset(textPrint, 0, sizeof textPrint); //Clears the textPrint array
            p = 0;
        }
        textPrint[p] = ch;
        printf("%02x", ch); //Appends a zero if value is one digit. Prints the hexadecimal character of each character in a string
        index++;
        p++;
        if (index % 2 == 0) {   //After every 2 characters, print a space
            printf(" ");
        }
    }
    printf("\n");
}

/*************************************************************
function: printBin
Notes: This function prints the binary values of ascii
 characters specified in the input file
*************************************************************/
int printBin(FILE *fp) {
    int ch = 0;
    int p = 0;  //Acts as a pointer for the textPrint array
    int index = 0;  //Index is the value that is displayed in the leftmost column on the output
    int chInt;  //chInt stands for Char Integer and will store the integer value of the character
    int c,k;    //Variables used in the bitwise shift right operation to convert integers to binary
    char textPrint[5];  //Will hold the char values needed to print after displaying the binary values

    while(!feof(fp)) {
        ch = fgetc(fp);
        if (index % 6 == 0 || feof(fp)) {   //Prints every 6 octets
            if (feof(fp)) {

                /*Formats the right column, text file information
                  index % 6 gets half of the the amount of octets left needed to display
                  Each octet is 8 bytes long and index % 6 is multiplied by 2 to get the total amount of octets needed
                  In this case 8 * 2 = 16 and that is multiplied by index % 6. 5 is added to offset the amount of spaces
                  between each octet*/
                printf("%*s", 8 * (index % 6) + 5, "");

                //When the program ends with an odd amount of characters, an extra char of the last char is added.
                //This removes that extra char
                if (index % 2 == 1) {
                    textPrint[5] = 0;
                }
            }
            int i = 0;
            for (i = 0; i < 5; i++) {
                if (isprint(textPrint[i]) == 0 && (textPrint[i] != 0)) {
                    textPrint[i] = 46;
                }
            }
            printf(" %s", textPrint);
            printf("\n");
            printf("%08x: ", index);    //Appends 0's in front of the address and prints in hexadecimal
            memset(textPrint, 0, sizeof textPrint); //Clears the textPrint array
            p = 0;
        }
        //*******Converts integer value into Binary using bitwise shift*******
        chInt = (int)ch;  //chInt stands for Char Integer and will store the integer value of the character
        for (c = 7; c >= 0; c--)
        {
            k = chInt >> c;
            if (k & 1)
                printf("1");
            else
                printf("0");
        }
        textPrint[p] = ch;
        index++;
        p++;
        printf(" ") ;   //After each char, print a space

    }
    printf("\n");
}


/*************************************************************
main
Notes: Main holds the open file function which executes the
 specified input
*************************************************************/
int main (int argc,char *argv[]) {

/*************************************************************
function: fp (file open)
Notes: A sample of how to use embedded comments
I/O: input parameters: Flag -b for binary output or no flag for hex
     output: Either a hexdump in hexadecimal or in binary
*************************************************************/
    FILE *fp;

    if (argc == 2) {
        fp = fopen(argv[1], "r");
        printHex(fp);

    } else if (argc == 3 && (strcmp(argv[1], "-b") == 0)) {
        fp = fopen(argv[2], "r'");
        printBin(fp);

    } else {
        printf("Try again. Specify either with flag -b or no flags.\n");
    }

    if (fp == NULL) {
        printf("File not found, check filename.\n");
        exit(1);
    }
    fclose(fp);
}