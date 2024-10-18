#include "svmalloc.h"
#include <stdio.h>
int main() {
    char* a = svmalloc(10); 
    char* b=svmalloc(10);
    printf("%p\n", a);
    printf("%p\n", b);
    return 0;
}

