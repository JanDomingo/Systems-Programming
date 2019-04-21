#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

struct symTab {
    char label[17];
    char address[8];
}; typedef struct symTab symTable;

struct opTab {
    char instruction[7];
    int opCode;
    int format; //format 3 refers to format 3 or format 4
};
void format2();
void format3();
void format4();
int locctr = 0;
int pcctr;
int symTabSize;
int xRegister = 0;
int bRegister = 0;
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
    struct symTab *items = malloc(sizeof(struct symTab));
    FILE *symfp;

    symfp = fopen("sample.sym", "r");

    //TODO: CREATE THE TABLE FOR THE SYMTAB

    char tempp[9];
    int i = 0;
    int c = 0;
    char *convert;
    int g = 0;
    char buffer[80];
    char address[7];
    int z = 0;
    char buffer2[50];

    for (i = 0; i < 3; i++) {   //This skips three lines of the symbol table to skip the header labels and the name address and start directly at the body to copy symbols
        fgets(buffer, 80, symfp);
    }
    while (!(feof(symfp))) {

        for (g = 0; g < 8; ++g) {
            tempp[g] = fgetc(symfp);


        }
        if (tempp[0] == '\n') {
            break;
        }
        tempp[8] = '\0';

        memcpy(symmie[z].label, tempp, 9);
        printf(symmie[z].label);
        for (c = 0; c < 7; ++c) {
            address[c] = fgetc(symfp);
        }

        address[7] = '\0';
        memcpy(symmie[z].address, address, 7);
        printf(symmie[z].address);

        while (getc(symfp) != '\n') {
            getc(symfp);
        }
        symTabSize++;
        ++z;
        g = 0;
        c = 0;
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
            int addressDifference = (charEndingAddrToHex -charEndingAddrToHex);    //TODO FIGURE OUT WHY THIS IS NOT SUBTRACTING PROPERLY
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
            while ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90)) {
                opCode[0] = ch;
                ch = getc(ifp);

                opCode[1] = ch;
                opCode[2] = '\0';


                //This converts the object code hex strings to hex values
                int opVal = strtol(opCode, &ptr, 16);
                //printf("ret: %d\n", opVal);

                char toPrintInstruction[7];
                char niBit[2];
                int trueOpval;
                int trueFormat;

                //This section iterates through the optab and copies the instruction to print
                for (int j = 0; j < 59; j++) {  //59 is the amount of optab instructions

                    if ((opVal - 1) == opCodeTable[j].opCode) {
                        strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                        niBit[0] = '#';
                        niBit[1] = '\0';
                        //pcctr += opCodeTable[j].format;
                        trueFormat = opCodeTable[j].format;


                    } else if ((opVal - 2) == opCodeTable[j].opCode) {
                        strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                        niBit[0] = '@';
                        niBit[1] = '\0';
                        //pcctr+=opCodeTable[j].format;
                        trueFormat = opCodeTable[j].format;

                    } else if ((opVal - 3) == opCodeTable[j].opCode) {
                        strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                        niBit[0] = '\0';
                        //pcctr+=opCodeTable[j].format;
                        trueFormat = opCodeTable[j].format;
                    }
                    if (opVal == opCodeTable[j].opCode) {
                        strncpy(toPrintInstruction, opCodeTable[j].instruction, 7);
                        niBit[0] = '\0';
                        if (opCodeTable[j].format == 1 || opCodeTable[j].format == 2) {
                            //pcctr += opCodeTable[j].format;
                            trueFormat = opCodeTable[j].format;
                        } else {
                            //pcctr+=opCodeTable[j].format;
                            trueFormat = opCodeTable[j].format;
                        }
                    }
                }



                printf("\n%04X  ", locctr); //Displays the location counter

                if(trueFormat==1) {
                    pcctr += 1;
                    locctr = pcctr;
                    char *format1Pointer;
                    int opCodeF1=strtol(opCode, &format1Pointer, 16);
                    for(int z=0;z<59;++z) {
                        if(opCodeF1==opCodeTable[z].opCode) {
                            printf("%s",opCodeTable[z].instruction);
                        }
                    }

                }

                if(trueFormat==2) {//copy toPrint instruction
                    char format2Contents[3];
                    format2Contents[0]= getc(ifp);
                    format2Contents[1]=getc(ifp);
                    format2Contents[2]='\0';
                    format2(toPrintInstruction,format2Contents);
                }

                if (trueFormat == 3) {
                    char format3Contents[4];

                    for (int i = 0; i < 4; i++) { //Gets the xbpe bit and the displacement and saves it into contents
                        ch = getc(ifp);
                        format3Contents[i] = ch;
                    }
                    format3Contents[4] = '\0';

                    //This converts the contents from char to int
                    char *eBitPointer;
                    char firstBit[1];
                    firstBit[0] = format3Contents[0];
                    int eBit = strtol(firstBit, &eBitPointer, 16);

                    //This section goes into the format4 function
                    if (eBit == 1 || eBit == 9) {
                        char format4Contents[6];    //Puts the dispalcement field in address into an array
                        memcpy(format4Contents, format3Contents, 4);
                        for (int i = 0; i < 2; i++) {   //Skips over the opcode
                            ch = getc(ifp);
                            format4Contents[i+4] = ch;
                        }

                        format4Contents[6]='\0';
                        format4(toPrintInstruction, niBit, format4Contents);
                    } else {
                        format3(toPrintInstruction, niBit, format3Contents);
                    }

                }

                //if (locctr == symT)

                ch = getc(ifp);
            }
            printf("\n");

        }


    }




    /**THIS SECTION MANAGES THE RESB AND RESW PRINT STATEMENTS**/
    int idxCtr;
    char *nextLabel;
    int afterNextAddress;
    int symTabAddy;
    char* symmieAddy;
    int saveSymmieAddy;
    int nextAddress;
    char *symmiePointer2;
    int length;
    int thirds;

    for (int x = 1; x < symTabSize; x++) {
        symTabAddy = strtol(symmie[x].address, &symmieAddy, 16);
        if (locctr == symTabAddy) {

            idxCtr=x;
            saveSymmieAddy = symTabAddy;
        }
    }
    printf("%04s ",symmie[idxCtr].address);
    printf("%s RESW ",symmie[idxCtr].label);
    printf("\n");
    idxCtr=idxCtr+1;  //Index Counter

    nextAddress = strtol(symmie[idxCtr].address, &symmiePointer2, 16); //LENGTH ADDRESS (Original Address + 1)
    for(idxCtr; idxCtr<symTabSize - 1; idxCtr++) {
        afterNextAddress= strtol(symmie[idxCtr+1].address, &nextLabel, 16); //BUFFER ADDRESS (Original Address + 2)
        length = afterNextAddress - nextAddress;
        if(length%3==0) {
            thirds=length/3;
            printf("%s",symmie[idxCtr].address);
            printf(" %s RESW",symmie[idxCtr].label);
            printf(" %d",thirds);
            printf("\n");

        }
        else {

            printf("%s",symmie[idxCtr].address);
            printf(" %s RESB",symmie[idxCtr].label);
            printf(" %d",length);
            printf("\n");
        }
    }
}

/**THIS IS THE FUNCTION FOR FORMAT3**/
void format3(char toPrintInstruction[], char niBit[], char contents[]) {
    int tempctr;    //temporary pc counter
    int symTabLookup;
    char displacement[3];
    char* displacementPointer;
    char* displacementValue2Pointer;
    char* symmiePointer;
    char* xbpeBitPointer;
    int displacementValue;
    int displacementValue2;
    char displacementValue2Arr;
    int symTabAddressToInt; //Holds the int value of the sym tab address
    int targetAddress;
    bool immediateFlag = false;

    pcctr += 3;

    //Prints the non-instrudtional label
    for (int i = 1; i < symTabSize; i++) {
        symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
        if (locctr == symTabAddressToInt) {
            printf("%s", symmie[i].label);
        }
    }



    //Copies the displacement value and puts it into the displacement char array
    for (int i = 0; i < 4; i++) {
        displacement[i] = contents[i+1];
    }

    displacementValue = strtol(displacement, &displacementPointer, 16); //Converts the displacement value from char to int
    displacementValue2 = displacementValue + pcctr; //Displacement Value added with pcctr

    //This function loads the X register
    if(strcmp(toPrintInstruction, "LDX") == 0) {
        if (niBit[0] == '#') {
            xRegister = displacementValue;
        }
        //if (niBit[0] == '@') **OPTIONAL: ADD IN A CASE IF THERE IS AN IMMEDIATE LDX SYMBOL
        if (niBit[0] == '\0') {
            symTabLookup = displacementValue + pcctr;
            for (int i = 0; i < symTabSize; i++) {
                symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
                if (symTabLookup == symTabAddressToInt) {
                    printf(symmie[i].label);
                    xRegister = symTabAddressToInt;
                }
            }
        }
    }

    if(strcmp(toPrintInstruction, "LDB") == 0) {
        if (niBit[0] == '#') {
            bRegister = displacementValue2;
        }
        //if (niBit[0] == '@') **OPTIONAL: ADD IN A CASE IF THERE IS AN IMMEDIATE LDX SYMBOL
        //If simple addressing, get the target address as the base
        if (niBit[0] == '\0') {
            symTabLookup = displacementValue + pcctr;   //TODO: CHECK IF PCCTR IS OK HERE
            for (int i = 0; i < symTabSize; i++) {
                symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
                if (symTabLookup == symTabAddressToInt) {
                    printf(symmie[i].label);
                    bRegister = symTabAddressToInt;
                }
            }
        }
    }



    if (contents[0] == '0') { //COMP instruction
        printf(" ");    //TODO: Figure out what this empty space does
        printf("%-05s",toPrintInstruction);
        printf("%s", niBit);
        printf("%d", displacementValue);
    }

    if (contents[0] == '2' || contents[0] == 'A') { //PC Relative or PC relative with index
        printf(" ");
        targetAddress = pcctr + displacementValue;
        if (targetAddress > 4096) {
            targetAddress = targetAddress - 4096;
            for (int i = 1; i < symTabSize; i++) {
                symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
                if (targetAddress == symTabAddressToInt) {
                    printf("%-05s", toPrintInstruction);
                    printf("%s", symmie[i].label);
                    if (contents[0] == 'A') {
                        printf(",X");
                    }
                }
            }
        }

        //TODO: FIGURE OUT WHAT THIS DOES
        for (int i = 0; i < symTabSize; i++) {
            symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
            if (displacementValue2 == symTabAddressToInt) {
                printf("%-05s", toPrintInstruction);
                printf("%s", niBit);
                printf(symmie[i].label);
            }
        }

    }

    if (contents[0] == '4' || (contents[0] == 'C')) { //Base Relative or base relative with index
        targetAddress = bRegister + displacementValue;
        for (int i = 1; i < symTabSize; i++) {
            symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
            if (targetAddress == symTabAddressToInt) {
                printf("%-05s", toPrintInstruction);
                printf("%s", symmie[i].label);
                if (contents[0] == 'C') {
                    printf(",X");
                }
            }
        }
    }

    locctr = pcctr;

}

void format4(char toPrintInstruction[], char niBit[], char contents[]) {
    pcctr += 4;

    char addressField[5];
    int addressFieldInt;
    int symTabAddressToInt;
    char toPrintAddress[7];
    char *symmiePointer;


    char *addressFieldPointer;

    //Prints the non-instrudtional label
    for (int i = 1; i < symTabSize; i++) {
        symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
        if (locctr == symTabAddressToInt) {
            printf("%s", symmie[i].label);
        }
    }

    //This copies the contents array, exlcuding the first bit to make a new array of only the address field
    for (int i = 0; i < 5; i++) {
        addressField[i] = contents[i + 1];
    }

    addressFieldInt = strtol(addressField, &addressFieldPointer, 16);

    for (int i = 0; i < symTabSize; i++) {
        symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
        if (addressFieldInt == symTabAddressToInt) {
            printf("+%s ", toPrintInstruction);
            printf("%s", niBit);
            printf("%s", symmie[i].label);
        }
        locctr = pcctr;
    }
}
//TODO: ADD X REGISTER SCENARIO
void format2(char toPrintInstruction[], char format2Contents[]) {

//r1,r2 r2 stores the result
    pcctr += 2;
    locctr = pcctr;
    char register1;
    char register2;
    register1 = format2Contents[0];
    printf("%-05s", toPrintInstruction);
    char register1Integer = register1;
    if (register1Integer == '0') {
        printf("A,");
    }
    if (register1Integer == '1') {
        printf("X,");
    }
    if (register1Integer == '2') {
        printf("L,");
    }
    if (register1Integer == '3') {
        printf("B,");
    }
    if (register1Integer == '4') {
        printf("S,");
    }
    if (register1Integer == '5') {
        printf("T,");
    }
    if (register1Integer == '6') {
        printf("F,");
    }

    char register2Integer = format2Contents[1];
    if (register2Integer == '0') {
        printf("A");
    }
    if (register2Integer == '1') {
        printf("X");
    }
    if (register2Integer == '2') {
        printf("L");
    }
    if (register2Integer == '3') {
        printf("B");
    }
    if (register2Integer == '4') {
        printf("S");
    }
    if (register2Integer == '5') {
        printf("T");
    }
    if (register2Integer == '6') {
        printf("F");
    }
}
