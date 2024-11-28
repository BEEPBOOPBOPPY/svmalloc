#include "svmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void copyChar(char *s, char c, int len)
{
    for( int i=0; i<len; i++)
        s[i] = c;
}

int main() {
    srand(time(NULL));
    struct block* blocks[41] = {NULL};
    for(int i=0; i<40; i++) {
        int size = rand() % (4096/2 + 1);
        blocks[i] = svmalloc(size);
        copyChar(blocks[i], 'A'+i, size);
    }
    //free 20 blocks randomly
    for(int i=0; i<20; i++) {
        int index = rand() % 40;
        if(blocks[index]) {
            svfree(blocks[index]);
            blocks[index] = NULL;
        }
    }
    //allocate 10 more blocks and put them in the null slots in the array
    for(int i=0; i<10; i++) {
        int size = rand() % (4096/2 + 1);
        for(int j=0; j<40; j++) {
            if(!blocks[j]) {
                blocks[j] = svmalloc(size);
                copyChar(blocks[j], 'A'+j, size);
                break;
            }
        }
    }

    


    print_heap_layout();
    return 0;
}

