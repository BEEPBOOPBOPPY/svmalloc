#include "svmalloc.h"
#include <stdio.h>

void copyChar(char *s, char c, int len)
{
    for( int i=0; i<len; i++)
        s[i] = c;
}

int main() {
    char* a = svmalloc(10); 
    printf("a = %p \n", a);
    char* b=svmalloc(20);
    printf("b = %p \n", b);
    char* c=svmalloc(30);
    printf("c = %p \n", c);
    char* d=svmalloc(40);
    printf("d = %p \n", d);

    printf("b-a = %ld \n", (b-a));
    printf("c-b = %ld \n", (c-b));
    printf("d-c = %ld \n", (d-c));

    copyChar(a, 'a', 10);
    copyChar(b, 'b', 20);
    copyChar(c, 'c', 30);
    copyChar(d, 'd', 40);


    print_heap_layout();
    return 0;
}

