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

void format3();
void format4();
int locctr;
int pcctr;
int symTabSize;
symTable symmie[60];

int main() {


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
    //printf("%s\n",opCodeTable[1].instruction);
    //printf("%d\n",opCodeTable[1].opCode);
    //int test=opCodeTable[1].opCode-1;   //Subtracts 1 from the hex to check for n, i flags of the opcode
    //printf("%d\n",test);

    /******************************************/
    /************THIS IS THE SYMTAB************/
    /******************************************/

    FILE *symfp;

    symfp = fopen("sample.sym", "r");

    //TODO: CREATE THE TABLE FOR THE SYMTAB

    char tempp[9];
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

        memcpy(symmie[z].label, tempp,9);
        printf(symmie[z].label);
        for(c=0;c<7;++c) {
            address[c]=fgetc(symfp);
        }

        address[7]='\0';
        memcpy(symmie[z].address, address, 7);
        printf(symmie[z].address);

        while(getc(symfp)!='\n') {
            getc(symfp);
        }
        symTabSize++;
        ++z;
        g=0;
        c=0;
        printf("\n"); //TODO: Copy the sample.sym contents into the symtab struct
    }



    //int retr = strtol(symmie[4].address, &convert, 16);
    //printf("%s", symmie[4].label);
    //printf("%d",retr);

    /******************************************/
    /**THIS SECTION READS IN THE OPCODE AND FINDS THE CORRESPONDING STRING FROM THE OPCODETABLE**/
    /******************************************/
    char ch;
    char opCode[1];
    char *ptr;
    FILE *ifp;	//input file pointer
    ifp = fopen("sample.obj", "r");
    while (!(feof(ifp))) {
        ch = getc(ifp);


        /**This section reads in the Header Line**/
        char programName[20]; //TODO: Check if 20 is enough size to allocate
        if (ch == 'H') {
            int i = 0;
            ch = getc(ifp);
            while (ch >= 65 && ch <= 90) { //While ch is a capital letter
                programName[i] = ch;
                ch = getc(ifp);
                i++;
            }
            //printf("Program Name: %s\n", programName);


            while (ch == ' ') { //Skips through the spaces between the file name and starting address in the header line
                ch = getc(ifp);
            }

            char startingAddress[6];
            char endingAddress[6];
            int programLength;

            if (ch >= 48 && ch <= 57) { //If ch is an integer
                for (int i = 0; i < 6; i++) {   //Gets the starting address
                    startingAddress[i] = ch;
                    ch = getc(ifp);
                }

                startingAddress[6] = '\0';

                for (int i = 0; i < 6; i++) {
                    endingAddress[i] = ch;   //Gets the ending address
                    ch = getc(ifp);
                }

                endingAddress[6] = '\0';

            }

            int charStartingAddrToHex = strtol(startingAddress, &ptr, 16);
            int charEndingAddrToHex = strtol(endingAddress, &ptr, 16);
            int addressDifference = (charEndingAddrToHex - charEndingAddrToHex);    //TODO FIGURE OUT WHY THIS IS NOT SUBTRACTING PROPERLY
            //printf("Starting Address: %d\n", charStartingAddrToHex);
            //printf("Ending Address: %d\n", charEndingAddrToHex);
            //printf("Program Length: %d\n", addressDifference);
    }


        /**This section reads in the Text record**/
        if (ch == 'T') {
            for (int i = 0; i < 9; i++) {   //Moves the file pointer over the address value and length
                ch = getc(ifp);
            }

            //This section grabs the next two characters of the text records which are the opcode instructions
            opCode[0] = ch;
            ch = getc(ifp);
            opCode[1] = ch;
            opCode[2] = '\0';


            //This converts hex strings to hex values
            int opVal = strtol(opCode, &ptr, 16); //ret is the opcode value
            //printf("ret: %d\n", opVal);

            char toPrintInstruction[7];
            char niBit[1];
            int trueOpval;
            int trueFormat;

            //This section interates through the obtab and copies the instruction to print
            for (int j = 0; j < 59; j++) {  //59 is the amount of obtab instructions

                if ((opVal - 1) == opCodeTable[j].opCode) {
                    strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                    niBit[0] = '#';
                    locctr += opCodeTable[j].format;
                    trueFormat = opCodeTable[j].format;

                } else if ((opVal - 2) == opCodeTable[j].opCode) {
                    strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                    niBit[0] = '@';
                    locctr+=opCodeTable[j].format;
                    trueFormat = opCodeTable[j].format;

                } else if ((opVal - 3) == opCodeTable[j].opCode) {
                    strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                    niBit[0] = ' ';
                    locctr+=opCodeTable[j].format;
                    trueFormat = opCodeTable[j].format;
                }
                if (opVal == opCodeTable[j].opCode) {
                    strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);

                    if (opCodeTable[j].format == 1 || opCodeTable[j].format == 2){
                        locctr += opCodeTable[j].format;
                        trueFormat = opCodeTable[j].format;
                    } else {
                        locctr+=opCodeTable[j].format;
                        trueFormat = opCodeTable[j].format;
                    }
                }
            }


            printf("\n%07x\n", locctr); //Displays the location counter

            if (trueFormat == 3) {
                char contents[4];

                for (int i = 0; i < 4; i++) {
                    ch = getc(ifp);
                    contents[i] = ch;
                }
                contents[4] = '\0';










                //This converts the contents from char to int
                char* eBitPointer;
                char firstBit[1];
                firstBit[0] = contents[0];
                int eBit = strtol(firstBit, &eBitPointer, 16);
                if (eBit == 1 || eBit == 9) {
                    //TODO: Work on format 4
                    printf("format4\n");
                    format4();
                }

                format3(toPrintInstruction, niBit, contents);
            }
            }
        }
}


void format3(char toPrintInstruction[], char niBit[], char contents[]) {
    int tempcter;
    int a = locctr;
    char displacement[3];
    char* displacementPointer;
    char* symmiePointer;
    int displacementValue;
    int displacementValue2;


    int temp;

    for (int i = 0; i < 4; i++) {
        displacement[i] = contents[i+1];
    }



    //2, 4, 10, 12
    if (contents[0] == '2') { //PC Relative
        tempcter = locctr;
        displacementValue = strtol(displacement, &displacementPointer, 16);
        displacementValue2 = displacementValue + tempcter;
        printf(" ");


        for (int i = 0; i < symTabSize; i++) {
            temp = strtol(symmie[i].address, &symmiePointer, 16);
            if (displacementValue2 == temp) {
                printf(symmie[i].label);
                printf(toPrintInstruction);

            }
        }

    }

    if (contents[0] == 4) { //Base Relative

    }

    if (contents[0] == 10) { //PC Relative with index

    }

    if (contents[0] == 12) { //Base Relative with index

    }

}

void format4() {

}



