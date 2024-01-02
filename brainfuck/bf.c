#include <stdio.h>

int program[1024];
__u_char buffer[256];

// argc[1] is filename
int main(int argv, char **argc) {
    // read program from args
    char *filename = argc[1];
    FILE *file = fopen(filename, "r");
    for (int i = 0; (program[i] = fgetc(file)) != EOF; ++i)
        ;
    //
    int bp = 0;  // buffer pointer
    int pp = 0;  // program pointer
    while (program[pp] != EOF) {
        switch (program[pp]) {
            case '>': {
                bp++;
                pp++;
                break;
            }
            case '<': {
                bp--;
                pp++;
                break;
            }
            case '+': {
                buffer[bp]++;
                pp++;
                break;
            }
            case '-': {
                buffer[bp]--;
                pp++;
                break;
            }
            case '.': {
                putc(buffer[bp], stdout);
                // printf("num=[%d]\n", buffer[bp]);
                pp++;
                break;
            }
            case ',': {
                buffer[bp] = getc(stdin);
                pp++;
                break;
            }
            case '[': {  // if buffer[bp]==0, jump to pairing bracket
                if (buffer[bp] == 0) {
                    int count = 1;
                    while (count != 0) {
                        pp++;
                        if (program[pp] == '[') count++;
                        if (program[pp] == ']') count--;
                    }
                }
                pp++;
                break;
            }
            case ']': {  // jump to pairing bracket
                int count = -1;
                while (count != 0) {
                    pp--;
                    if (program[pp] == '[') count++;
                    if (program[pp] == ']') count--;
                }
                break;
            }
            default:
                break;
        }
    }

    return 0;
}