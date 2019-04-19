#include <stdio.h>
#include <stdlib.h>
#include <memory.h>



struct symTab {
    char label[17];
    char address[8];
}; typedef struct symTab symTable;

struct opTab {
    char instruction[7];
    int opCode;
    int format; //format 3 refers to format 3 or format 4
};

void symTabBuilder(struct symTab symTable[60]);

int main() {
    symTable symmie[60];
    symTabBuilder(symmie);

    //TODO: CLEAN UP THE PROGRAM INTO FUNCTIONS
    //TODO: CLEAN UP THE VARIABLES NAMES
    //TODO: FINISH THE SYMTAB
    //TODO: FINISH THE XBPE INPUT
    //TODO; LOCATION COUNTER - ADD BY SIZE OF FORMAT
    //TODO: CREATE COMMAND LINE ARGUMENT
    /******************************************/
    /************THIS IS THE OPTAB*************/
    /******************************************/


    const struct opTab opCodeTable [] = {
            {"ADD", 0x18, 3},  {"ADDF", 0x58, 3},   {"ADDR", 0x90, 2},   {"AND", 0x40, 3},  {"CLEAR", 0xB4, 2},
            {"COMP", 0x28, 3}, {"COMPF", 0x88, 3},  {"COMPR", 0xA0, 2},  {"DIV", 0x24, 3},  {"DIVF", 0x64, 3},
            {"DIVR", 0x9C, 2}, {"FIX", 0xC4, 1},    {"FLOAT", 0xC0, 1},  {"HIO", 0xF4, 1},  {"J", 0x3C, 3},
            {"JEQ", 0x30, 3},  {"JGT", 0x34, 3},    {"JLT", 0x38, 3},    {"JSUB", 0x48, 3}, {"LDA", 0x00, 3},
            {"LDB", 0x68, 3},  {"LDCH", 0x50, 3},   {"LDF", 0x70, 3},    {"LDL", 0x08, 3},  {"LDS", 0x6C, 3},
            {"LDT", 0x74, 3},  {"LDX", 0x04, 3},    {"LPS", 0xD0, 3},    {"MUL", 0x20, 3},  {"MULF", 0x60, 3},
            {"MULR", 0x98, 2}, {"NORM", 0xC8, 1},   {"OR", 0x44, 3},     {"RD", 0xD8, 3},   {"RMO", 0xAC, 2},
            {"RSUB", 0x4C, 3}, {"SHIFTL", 0xA4, 2}, {"SHIFTR", 0xA8, 2}, {"SIO", 0xF0, 1},  {"SSK", 0xEC, 3},
            {"STA", 0x0C, 3},  {"STB", 0x78, 3},    {"STCH", 0x54, 3},   {"STF", 0x80, 3},  {"STI", 0xD4, 3},
            {"STL", 0x14, 3},  {"STS", 0x7C, 3},    {"STSW", 0xE8, 3},   {"STT", 0x84, 3},  {"STX", 0x10, 3},
            {"SUB", 0x1C, 3},  {"SUBF", 0x5C, 3},   {"SUBR", 0x94, 2},   {"SVC", 0xB0, 2},  {"TD", 0xE0, 3},
            {"TIO", 0xF8, 1},  {"TIX", 0x2C, 3},    {"TIXR", 0xB8, 2},   {"WD", 0xDC, 3}
    };


    /******************************************/
    /************THIS IS THE SYMTAB************/
    /******************************************/




}	//creates array of symTab objects

//TODO: BUILD THE SYMTAB HERE
//TODO: STEP 1: READ IN THE NAME OF THE LABEL USING GETC
//TODO: STEP 1.1: READ IN THE VALUE OF THE LABEL
//TODO: STEP 2: PUT THE LABEL IN SYMTABLE[I].LABEL
//TODO: STEP 2.2: PUT THE ADDRESS IN SYMTABLE[I].ADDRESS

void symTabBuilder(struct symTab symTable[60]) {
    FILE *symfp;
    int labelflag=0;
    symfp = fopen("sample.sym", "r");

    //TODO: CREATE THE TABLE FOR THE SYMTAB
    int editor3;
    int getlab[8];
    char tempp[9];
    char editor2;
    int lineCtr;
    char linePtr;
    int i=0;
    int c=0;
    char *convert;
    int g=0;
    char buffer[80];
    char address[7];
    int z=0;
    char buffer2[50];

    for (i = 0; i < 2; i++) {   //This skips two line of the symbol table to skip the header labels and start directly at the body to copy symbols
        fgets(buffer, 80, symfp);
    }
    while (!(feof(symfp))) {

        for(g=0;g<8;++g) {
            tempp[g]=fgetc(symfp);


        }
        if(tempp[0]=='\n') {
            break;
        }
        tempp[8]='\0';
        memcpy(symTable[z].label, tempp,9);
        printf(symTable[z].label);
        for(c=0;c<7;++c) {
            address[c]=fgetc(symfp);
        }

        address[7]='\0';
        memcpy(symTable[z].address, address, 7);
        printf(symTable[z].address);


        while(getc(symfp)!='\n') {
            getc(symfp);
        }
        ++z;
        g=0;
        c=0;
        printf("\n"); //TODO: Copy the sample.sym contents into the symtab struct
    }
    int retr = strtol(symTable[4].address, &convert, 16);
    printf("%d",retr);




}




/******************************************/
/**THIS SECTION READS IN THE OPCODE AND FINDS THE CORRESPONDING STRING FROM THE OPCODETABLE**/
/******************************************/




