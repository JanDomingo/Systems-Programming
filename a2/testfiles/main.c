#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
    struct opTab {
        char instruction[7];
        int opCode;
        int format; //format 3 refers to format 3 or format 4
    };

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
    printf("%s\n",opCodeTable[1].instruction);
    printf("%d\n",opCodeTable[1].opCode);
    int test=opCodeTable[1].opCode-1;   //Subtracts 1 from the hex to check for n, i flags of the opcode
    printf("%d\n",test);

    /******************************************/
    /************THIS IS THE SYMTAB************/
    /******************************************/

    struct symTab {
        char label[15];
        int address;
    };

    struct symTab symTable [50];

    void symTabBuilder(char* filename) {
        FILE *symfp;
        symfp = fopen(filename, "r");
        //TODO: CREATE THE TABLE FOR THE SYMTAB



        int lineCtr;
        char linePtr;

        while (!(feof(symfp))) {
            linePtr = getc(symfp);
            //TODO: Search until the line character then do a new line
            char buffer[100];
            for (int i = 0; i < 2; i++) {   //This skips two line of the symbol table to skip the header labels and start directly at the body to copy symbols
                fgets(buffer, 100, symfp);
            }

            char editor2;
            char temp[20];  //TODO: FIX THIS ARRAY DECLARATION OF GARBAGE
            int i = 0;
            while(editor2 != ' '){
                editor2 = getc(symfp);
                temp[i] = editor2;
                i++;
            }

            char toDebug[20];
            memcpy(symTable[1].label, temp, 15); //TODO: FOR LOOP TO PLACE THE LABEL INTO SYMTABLE STRUCT
            printf(symTable[1].label);

            printf(" ");

            //TODO: Copy the sample.sym contents into the symtab struct
        }




    }
    void readTextRecord(char* filename) {
        char ch;
        char opCode[1];
        char *ptr;
        *ifp;	//input file pointer
        ifp = fopen(filename, "r");
        while (!(feof(ifp))) {
            ch = getc(ifp);
            //TODO: An if Statement that reads the header 'H'
            if (ch == 'T') {
                for (int i = 0; i < 9; i++) {
                    ch = getc(ifp);
                }
                opCode[0] = ch;
                ch = getc(ifp);
                opCode[1] = ch;
                opCode[2] = '\0';


                //This converts hex strings to hex values
                int ret = strtol(opCode, &ptr, 16);
                printf("ret: %d\n", ret);

                char toPrint[7];
                int opcod4 = opCodeTable[4].opCode;

                //This section interates through the obtab and copies the instruction to print
                for (int j = 0; j < 59; j++) {
                    if (ret == opCodeTable[j].opCode) {
                        strncpy(toPrint, opCodeTable[j].instruction, 7);
                        printf(toPrint);
                        break;
                    }
                }
            }
        }
    }
}



/******************************************/
/**THIS SECTION READS IN THE OPCODE AND FINDS THE CORRESPONDING STRING FROM THE OPCODETABLE**/
/******************************************/




