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

struct textRecord {
    char address[6];
    int length;
}; typedef struct textRecord textRecField;

void format2();
void format3();
void format4();
void mainFileParser();
void storageDeclaration();

int locctr = 0;
int pcctr;
int symTabSize;
int textRecordSize = 0;
int xRegister = 0;
int bRegister = 0;
symTable symmie[60];
textRecField textRecordFields [50];
bool makeStorageDeclaration;
int textRecordLengthInt;
int textRecordFieldsBuilderCounter=0;
FILE *symfp;
FILE *ifp;  //input file pointer
FILE *ofp;
FILE *sfp;
char fileName[50];
char sic[5];
char lis [5];
char fileNameSIC[50];
char fileNameLIS[50];
int width = 7;

/******************************************/
/************THIS IS THE OPTAB*************/
/******************************************/

const struct opTab opCodeTable[] = {
        {"ADD",    0x18, 3},
        {"ADDF",   0x58, 3},
        {"ADDR",   0x90, 2},
        {"AND",    0x40, 3},
        {"CLEAR",  0xB4, 2},
        {"COMP",   0x28, 3},
        {"COMPF",  0x88, 3},
        {"COMPR",  0xA0, 2},
        {"DIV",    0x24, 3},
        {"DIVF",   0x64, 3},
        {"DIVR",   0x9C, 2},
        {"FIX",    0xC4, 1},
        {"FLOAT",  0xC0, 1},
        {"HIO",    0xF4, 1},
        {"J",      0x3C, 3},
        {"JEQ",    0x30, 3},
        {"JGT",    0x34, 3},
        {"JLT",    0x38, 3},
        {"JSUB",   0x48, 3},
        {"LDA",    0x00, 3},
        {"LDB",    0x68, 3},
        {"LDCH",   0x50, 3},
        {"LDF",    0x70, 3},
        {"LDL",    0x08, 3},
        {"LDS",    0x6C, 3},
        {"LDT",    0x74, 3},
        {"LDX",    0x04, 3},
        {"LPS",    0xD0, 3},
        {"MUL",    0x20, 3},
        {"MULF",   0x60, 3},
        {"MULR",   0x98, 2},
        {"NORM",   0xC8, 1},
        {"OR",     0x44, 3},
        {"RD",     0xD8, 3},
        {"RMO",    0xAC, 2},
        {"RSUB",   0x4C, 3},
        {"SHIFTL", 0xA4, 2},
        {"SHIFTR", 0xA8, 2},
        {"SIO",    0xF0, 1},
        {"SSK",    0xEC, 3},
        {"STA",    0x0C, 3},
        {"STB",    0x78, 3},
        {"STCH",   0x54, 3},
        {"STF",    0x80, 3},
        {"STI",    0xD4, 3},
        {"STL",    0x14, 3},
        {"STS",    0x7C, 3},
        {"STSW",   0xE8, 3},
        {"STT",    0x84, 3},
        {"STX",    0x10, 3},
        {"SUB",    0x1C, 3},
        {"SUBF",   0x5C, 3},
        {"SUBR",   0x94, 2},
        {"SVC",    0xB0, 2},
        {"TD",     0xE0, 3},
        {"TIO",    0xF8, 1},
        {"TIX",    0x2C, 3},
        {"TIXR",   0xB8, 2},
        {"WD",     0xDC, 3}
};

//fprintf(ofp, "%s\n",opCodeTable[1].instruction);
//fprintf(ofp, "%d\n",opCodeTable[1].opCode);
//int test=opCodeTable[1].opCode-1;   //Subtracts 1 from the hex to check for n, i flags of the opcode
//fprintf(ofp, "%d\n",test);




int main(int argc, char * argv[]) {

    char fileNames[50][50];

    if (argc < 3) {
        printf("Error, check arguments");
    }

    if (argc == 3) {
        ifp = fopen(argv[1], "r");
        symfp = fopen(argv[2], "r");

        strncpy(fileNames[0], argv[1], 50);
        strncpy(fileNames[1], argv[2], 50);

        for (int i = 0; i < 50; i++) {
            if (fileNames[0][i] != '.') {
                fileName[i] = fileNames[0][i];
                fileNameLIS[i] = fileNames[0][i];
                fileNameSIC[i] = fileNames[0][i];
            }
        }

        lis[0] = '.';
        lis[1] = 'l';
        lis[2] = 'i';
        lis[3] = 's';
        lis[4] = '\0';

        sic[0] = '.';
        sic[1] = 's';
        sic[2] = 'i';
        sic[3] = 'c';
        sic[4] = '\0';

        strcat(fileNameLIS, lis);
        strcat(fileNameSIC, sic);


        ofp=fopen(fileNameLIS,"w");
        sfp=fopen(fileNameSIC,"w");
    }

    mainFileParser();
}

    /******************************************/
    /************THIS IS THE SYMTAB************/
    /******************************************/
    void mainFileParser() {
    struct symTab *items = malloc(sizeof(struct symTab));

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
        //fprintf(ofp, symmie[z].label);
        for (c = 0; c < 7; ++c) {
            address[c] = fgetc(symfp);
        }

        address[7] = '\0';
        memcpy(symmie[z].address, address, 7);
        //fprintf(ofp, symmie[z].address);

        while (getc(symfp) != '\n') {
            getc(symfp);
        }
        symTabSize++;
        ++z;
        g = 0;
        c = 0;
        //fprintf(ofp, "\n"); //TODO: Copy the sample.sym contents into the symtab struct
        //fprintf(sfp, "\n.sic", fileName);
    }

    int v=z;
    char litValue [7];
    int s=0;
    char litAddress[9];
    char sh;
    char * cnv;
    while (!(feof(symfp))) {
        for (i = 0; i <2; i++) {   //This skips three lines of the symbol table to skip the header labels and the name address and start directly at the body to copy symbols
            fgets(buffer, 80, symfp);
        }
        for(int f=0;f<8;++f) {
            fgetc(symfp);
        }
        while(sh!=' ') {
            sh= getc(symfp);
            litValue[s]=sh;
            ++s;
        }


        memcpy(symmie[v].label, litValue, 7);



        for(int r=0;r<10;++r) {
            getc(symfp);
        }


        for(int o=0;o<8;++o) {
            litAddress[o]= getc(symfp);
        }
        memcpy(symmie[v].address, litAddress, 8);

        ++v;
        ++symTabSize;
    }
    //fprintf(ofp, "%s",symmie[v-1].label);
    int retr = strtol(symmie[v-1].address, &cnv, 16);

    //fprintf(ofp, "%d",retr);


    //int retr = strtol(symmie[4].address, &convert, 16);
    //fprintf(ofp, "%s", symmie[4].label);
    //fprintf(ofp, "%d",retr);


    /******************************************/
    /**THIS SECTION READS IN THE OPCODE AND FINDS THE CORRESPONDING STRING FROM THE OPCODETABLE**/
    /******************************************/
    char ch;
    char opCode[3];
    char *ptr;
    char start[5];
    ifp = fopen("sample.obj", "r");
    while (!(feof(ifp))) {
        ch = getc(ifp);


        /**This section reads in the Header Line**/
        char programName[20]; //TODO: Check if 20 is enough size to allocate
        int symmieAddressToInt;
        char * symmieAddressToIntPtr;
        if (ch == 'H') {
            int i = 0;
            ch = getc(ifp);
            while (ch >= 65 && ch <= 90) { //While ch is a capital letter
                programName[i] = ch;
                ch = getc(ifp);
                i++;
            }
            //fprintf(ofp, "Program Name: %s\n", programName);


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


            start[0] = 'S'; start[1] = 'T'; start[2] = 'A'; start[3] = 'R'; start[4] = 'T';
            /*This is the print statements for the first line*/
            fprintf(ofp, "%04x", locctr);
            symmieAddressToInt = strtol(symmie[0].address, &symmieAddressToIntPtr, 16);
            if (locctr == symmieAddressToInt) {
                fprintf(ofp, "%*s", width, programName);
            }
            fprintf(ofp, "%*s", width, start);
            fprintf(ofp, "%*x", width, locctr);



            fprintf(sfp, "%*04x", width, locctr);
            if (locctr == symmieAddressToInt) {
                fprintf(sfp, symmie[0].label);
            }
            fprintf(sfp, "%*s", width, programName);
            fprintf(sfp, "%*x", width, locctr);

            int charStartingAddrToHex = strtol(startingAddress, &ptr, 16);
            int charEndingAddrToHex = strtol(endingAddress, &ptr, 16);
            int addressDifference = (charEndingAddrToHex - charEndingAddrToHex);    //TODO FIGURE OUT WHY THIS IS NOT SUBTRACTING PROPERLY
            //fprintf(ofp, "Starting Address: %d\n", charStartingAddrToHex);
            //fprintf(ofp, "Ending Address: %d\n", charEndingAddrToHex);
            //fprintf(ofp, "Program Length: %d\n", addressDifference);
        }

        /*****************************************/
        /**This section reads in the Text record**/
        /*****************************************/
        char textRecordLength[2];
        char textRecordAddress[6];
        char *textRecordLengthPointer;
        char addressAndLength[8];


        if (ch == 'T') {
            for (int i = 0; i < 9; i++) {   //Moves the file pointer over the address value and length
                ch = getc(ifp);
                addressAndLength[i] = ch;
            }

            for (int i = 0; i < 6; i++) {
                textRecordAddress[i] = addressAndLength[i];
            }

            textRecordLength[0] = addressAndLength[6];
            textRecordLength[1] = addressAndLength[7];
            textRecordLengthInt = strtol(textRecordLength, &textRecordLengthPointer, 16);

            memcpy(textRecordFields[textRecordFieldsBuilderCounter].address, textRecordAddress, 6);
            textRecordFields[textRecordFieldsBuilderCounter].length = textRecordLengthInt;

            textRecordFieldsBuilderCounter++;
            textRecordSize++;


            //This section grabs the next two characters of the text records which are the opcode instructions
            while ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90)) {
                opCode[0] = ch;
                ch = getc(ifp);

                opCode[1] = ch;
                opCode[2] = '\0';


                //This converts the object code hex strings to hex values
                int opVal = strtol(opCode, &ptr, 16);
                //fprintf(ofp, "ret: %d\n", opVal);

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


                fprintf(ofp, "\n%04X  ", locctr); //Displays the location counter
                fprintf(sfp, "\n%04X ", locctr);

                if (trueFormat == 1) {
                    pcctr += 1;
                    locctr = pcctr;
                    char *format1Pointer;
                    int opCodeF1 = strtol(opCode, &format1Pointer, 16);
                    for (int z = 0; z < 59; ++z) {
                        if (opCodeF1 == opCodeTable[z].opCode) {
                            fprintf(ofp, "%*s", width, opCodeTable[z].instruction);
                        }
                    }

                }

                if (trueFormat == 2) {//copy toPrint instruction
                    char format2Contents[3];
                    format2Contents[0] = getc(ifp);
                    format2Contents[1] = getc(ifp);
                    format2Contents[2] = '\0';
                    format2(toPrintInstruction, format2Contents, opCode);
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
                            format4Contents[i + 4] = ch;
                        }

                        format4Contents[6] = '\0';
                        format4(toPrintInstruction, niBit, format4Contents, opCode);
                    } else {
                        format3(toPrintInstruction, niBit, format3Contents, opCode);
                    }

                }



                ch = getc(ifp);
            }
            //fprintf(ofp, "\n"); //This prints a new line when there is a new text record

        }
    }
    }








    //TODO: SAVE THE TEXT RECORD ADDRESS
    //TODO: SAVE THE TEXT RECORD LENGTH
    //TODO: SAVE THE NEXT TEXT RECORD ADDRESS
    //TODO: SAVE THE NEXT TEXT RECORD LENGTH
    //TODO: SAVE THE DIFFERENCE BETWEEN THE (TEXT RECORD ADDRESS) AND (NEXT TEXT RECORD ADDRESS)
    //TODO: IF THEY MATCH, NO STORAGE DECLARATION. IF NO MATCH THEN STORAGE DECLARATION CREATED
    /*
    int idxCtr;
    char *nextLabel;
    int afterNextAddress;
    int symTabAddy;
    char *symmieAddy;
    int saveSymmieAddy;
    int nextAddress;
    char *symmiePointer2;
    int length;
    int thirds;


    for (int x = 1; x < symTabSize; x++) {
        symTabAddy = strtol(symmie[x].address, &symmieAddy, 16);
        if (locctr == symTabAddy) {

            idxCtr = x;
            saveSymmieAddy = symTabAddy;
        }
    }
    fprintf(ofp, "%04s ", symmie[idxCtr].address);
    fprintf(ofp, "%s RESW ", symmie[idxCtr].label);
    fprintf(ofp, "\n");
    idxCtr += 1;

    for (idxCtr; idxCtr < symTabSize - 1; idxCtr++) {
        nextAddress = strtol(symmie[idxCtr].address, &symmiePointer2, 16); //LENGTH ADDRESS (Original Address + 1)
        afterNextAddress = strtol(symmie[idxCtr + 1].address, &nextLabel, 16); //BUFFER ADDRESS (Original Address + 2)
        length = afterNextAddress - nextAddress;
        if (length % 3 == 0) {
            thirds = length / 3;
            fprintf(ofp, "%s", symmie[idxCtr].address);
            fprintf(ofp, " %s RESW", symmie[idxCtr].label);
            fprintf(ofp, " %d", thirds);
            fprintf(ofp, "\n");

        } else {

            fprintf(ofp, "%s", symmie[idxCtr].address);
            fprintf(ofp, " %s RESB", symmie[idxCtr].label);
            fprintf(ofp, " %d", length);
            fprintf(ofp, "\n");
        }
    }
}*/





/**THIS IS THE FUNCTION FOR FORMAT3**/
void format3(char toPrintInstruction[], char niBit[], char contents[], char opCode[]) {
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

    //Prints the non-instructional label
    for (int i = 0; i < symTabSize; i++) {
        symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
        if (locctr == symTabAddressToInt) {
            fprintf(ofp, "%*s", width, symmie[i].label);
            fprintf(sfp, "%*s", width, symmie[i].label);

            //fprintf(ofp, "%s", contents);
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
                    fprintf(ofp, "%*s", width, symmie[i].label);
                    fprintf(sfp, "%*s", width, symmie[i].label);
                    fprintf(ofp, "%*s", width, opCode);
                    fprintf(ofp, "%*s", width, contents);

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
                    fprintf(ofp, "%*s", width, symmie[i].label);
                    fprintf(sfp, "%*s", width, symmie[i].label);
                    fprintf(ofp, "%*s", width, opCode);
                    fprintf(ofp, "%s", contents);

                    bRegister = symTabAddressToInt;
                }
            }
        }
    }



    if (contents[0] == '0') { //COMP instruction

        fprintf(ofp, "%*s", width, toPrintInstruction);
        fprintf(ofp, "%*s", width,niBit);
        fprintf(ofp, "%d", displacementValue);  //TODO: FIX PADDING
        fprintf(ofp, "%*s", width, opCode);
        fprintf(ofp, "%s", contents);


        fprintf(sfp, "%s", toPrintInstruction);
        fprintf(sfp, "%s", niBit);
        fprintf(sfp, "%d", displacementValue);

    }

    if (contents[0] == '2' || contents[0] == 'A') { //PC Relative or PC relative with index
        targetAddress = pcctr + displacementValue;
        if (targetAddress > 4096) {
            targetAddress = targetAddress - 4096;
            for (int i = 1; i < symTabSize; i++) {
                symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
                if (targetAddress == symTabAddressToInt) {
                    fprintf(ofp, "%*s", width, toPrintInstruction);
                    fprintf(ofp, "%s", symmie[i].label);
                    fprintf(sfp, "%*s", width, toPrintInstruction);
                    fprintf(sfp, "%*s", width, symmie[i].label);
                    if (contents[0] == 'A') {
                        fprintf(ofp, ",X");
                        fprintf(ofp, "%*s", width, opCode);
                        fprintf(ofp, contents);

                    }
                }
            }
        }

        //If not PC relative go here
        //TODO: FIGURE OUT WHAT THIS DOES
        for (int i = 0; i < symTabSize; i++) {
            symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
            if (displacementValue2 == symTabAddressToInt) {
                fprintf(ofp, "%s",  toPrintInstruction);
                fprintf(ofp, "%s", niBit);
                fprintf(ofp, symmie[i].label);
                fprintf(ofp, "%*s" ,width, opCode);
                fprintf(ofp, contents);

                fprintf(sfp, "%*s",width,  toPrintInstruction);
                fprintf(sfp, "%*s", width, niBit);
                fprintf(sfp, symmie[i].label);

            }
        }

    }

    if (contents[0] == '4' || (contents[0] == 'C')) { //Base Relative or base relative with index
        targetAddress = bRegister + displacementValue;
        for (int i = 1; i < symTabSize; i++) {
            symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
            if (targetAddress == symTabAddressToInt) {
                fprintf(ofp, "%*s", width, toPrintInstruction);
                fprintf(ofp, "%*s", width, symmie[i].label);

                fprintf(sfp, "%*s", width, toPrintInstruction);
                fprintf(sfp, "%*s", width, symmie[i].label);

                if (contents[0] == 'C') {
                    fprintf(ofp, ",X");
                    fprintf(sfp, ",X");
                    fprintf(ofp, "%*s", width, opCode);
                    fprintf(ofp, "%*s", contents);
                }
            }
        }
    }

    locctr = pcctr;

}

void format4(char toPrintInstruction[], char niBit[], char contents[], char opCode[]) {
    pcctr += 4;

    char addressField[5];
    int addressFieldInt;
    int symTabAddressToInt;
    char toPrintAddress[7];
    char *symmiePointer;
    char *addressFieldIntPointer;


    char *addressFieldPointer;

    //Prints the non-instrudtional label
    for (int i = 1; i < symTabSize; i++) {
        symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
        if (locctr == symTabAddressToInt) {
            fprintf(ofp, "%*s", width,  symmie[i].label);    //PRINTS CLOOP
            fprintf(sfp, "%*s", width,  symmie[i].label);

        }
    }



    //This copies the contents array, exlcuding the first bit to make a new array of only the address field
    for (int i = 0; i < 5; i++) {
        addressField[i] = contents[i + 1];
    }
    //addressField[5] = '\0';

    addressFieldInt = strtol(addressField, &addressFieldIntPointer, 16);

    if (contents[0] == '1' && niBit[0] == '#') { //COMP instruction
        fprintf(ofp, " ");    //TODO: Figure out what this empty space does
        fprintf(ofp, "+%s", toPrintInstruction);
        fprintf(ofp, "%*s", width,  niBit);
        fprintf(ofp, "%*d", width, addressFieldInt);  //TODO: FIX PADDING
        fprintf(ofp, "%*s", width, opCode);
        fprintf(ofp, "%s", contents);

        fprintf(sfp, " ");    //TODO: Figure out what this empty space does
        fprintf(sfp, "%*s", width, toPrintInstruction);
        fprintf(sfp, "%*s", width, niBit);
        fprintf(sfp, "%d", addressFieldInt);

    } else {
        for (int i = 0; i < symTabSize; i++) {
            symTabAddressToInt = strtol(symmie[i].address, &symmiePointer, 16);
            if (addressFieldInt == symTabAddressToInt) {
                fprintf(ofp, "+%s ",  toPrintInstruction);
                fprintf(ofp, "%*s", width, niBit);
                fprintf(ofp, "%s", symmie[i].label);
                fprintf(ofp, "%*s", width, opCode);
                fprintf(ofp, contents);

                fprintf(sfp, "+%s ", toPrintInstruction);
                fprintf(sfp, "%*s", width, niBit);
                fprintf(sfp, symmie[i].label);

            }
            locctr = pcctr;
        }
    }
}
//TODO: ADD X REGISTER SCENARIO
void format2(char toPrintInstruction[], char contents[], char opCode[]) {

//r1,r2 r2 stores the result
    pcctr += 2;
    locctr = pcctr;
    char register1;
    char register2;
    register1 = contents[0];
    fprintf(ofp, "%-05s", toPrintInstruction);
    fprintf(sfp, "+%s ", toPrintInstruction);
    char register1Integer = register1;
    if (register1Integer == '0') {
        fprintf(ofp, "A,");
        fprintf(sfp, "A,");

        fprintf(ofp, opCode);
        fprintf(ofp, contents);

    }
    if (register1Integer == '1') {
        fprintf(ofp, "X,");
        fprintf(sfp, "X,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register1Integer == '2') {
        fprintf(ofp, "L,");
        fprintf(sfp, "L,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register1Integer == '3') {
        fprintf(ofp, "B,");
        fprintf(sfp, "B,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register1Integer == '4') {
        fprintf(ofp, "S,");
        fprintf(sfp, "S,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register1Integer == '5') {
        fprintf(ofp, "T,");
        fprintf(sfp, "T,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register1Integer == '6') {
        fprintf(ofp, "F,");
        fprintf(sfp, "F,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }

    char register2Integer = contents[1];
    if (register2Integer == '0') {
        fprintf(ofp, "A");
        fprintf(sfp, "A,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register2Integer == '1') {
        fprintf(ofp, "X");
        fprintf(sfp, "X,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register2Integer == '2') {
        fprintf(ofp, "L");
        fprintf(sfp, "L,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register2Integer == '3') {
        fprintf(ofp, "B");
        fprintf(sfp, "B,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register2Integer == '4') {
        fprintf(ofp, "S");
        fprintf(sfp, "S,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register2Integer == '5') {
        fprintf(ofp, "T");
        fprintf(sfp, "T,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
    if (register2Integer == '6') {
        fprintf(ofp, "F");
        fprintf(sfp, "F,");
        fprintf(ofp, opCode);
        fprintf(ofp, contents);
    }
}
