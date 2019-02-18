/*************************************************************
Name: Jan Domingo
Class Account: CSSC0463
Class Information: CS570, Spring 2019, Section 1
Project: CS530 Assignment 1
Assignment Information: Assignment #1, Hexadecimal Dump File
File: Makefile
*************************************************************/

//Anytime xbd.c changes, it gets recompiled
xbd: xbd.c
    gcc xbd.c -o xbd

//Compiles the xbd.c file into a xbd.o object file
xbd.o: xbd.c
    gcc -c xbd.c

clean:
    rm *.o xbd