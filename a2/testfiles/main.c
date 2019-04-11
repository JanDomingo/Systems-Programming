#include <stdio.h>
#include <stdlib.h>

int main() {
    char editor;
    char opCode[1];
    char *ptr;

    FILE *ifp;
    ifp = fopen("sample.obj", "r");
    while (!(feof(ifp))) {
        editor = getc(ifp);
        //TODO: An if Statement that reads the header 'H'
        if (editor == 'T') {
            for (int i = 0; i < 9; i++) {
                editor = getc(ifp);
            }
            opCode[0] = editor;
            editor = getc(ifp);
            opCode[1] = editor;


            //This converts hex strings to hex values 
            int ret = strtol(opCode, &ptr, 16);
            printf("%d", ret);

        }
    }
}
