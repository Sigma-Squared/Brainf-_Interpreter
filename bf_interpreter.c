#define S_MEM 65536

#define uint unsigned int

#include <stdio.h>
#include <stdlib.h>

void run(char* prog, long len) {
    uint* br_stack = calloc(len / 2, sizeof(uint));
    int br_stackp = -1;
    uint* brackets = calloc(len, sizeof(uint));
    for (uint i=0; i<len; i++) {
        if (prog[i] == '[')
            br_stack[++br_stackp] = i;
        else if (prog[i] == ']') {
            if (br_stackp < 0) {
                printf("Malformed brackets");
                return;
            }
            uint op_brack = br_stack[br_stackp--];
            brackets[op_brack] = i;
            brackets[i] = op_brack;
        }
    }
    free(br_stack);

    char progmem[S_MEM] = {0};
    char* ptr = progmem;
    uint pc = 0;
    while (1) {
        char c = prog[pc];
        switch(c) {
            case '>': ++ptr; break;
            case '<': --ptr; break;
            case '+': ++*ptr; break;
            case '-': --*ptr; break;
            case '.': putchar(*ptr); break;
            case ',': *ptr = getchar(); break;
            case '[':
                if (*ptr == 0)
                    pc = brackets[pc];
                break;
            case ']':
                if (*ptr != 0)
                    pc = brackets[pc];
                break;
        }
        pc++;
        if (pc >= len)
            break;
    }
    free(brackets);
}

int main(int argc, char** argv) {
    if (argc != 2)
        return 1;
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL)
        return 1;
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* fcontents = malloc(fsize);
    fread(fcontents, 1, fsize, fp);
    fclose(fp);

    run(fcontents, fsize);
    free(fcontents);
}