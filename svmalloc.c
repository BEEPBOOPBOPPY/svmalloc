#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "svmalloc.h"
#include <unistd.h>


struct block {
    
    int free; //1 is free, 0 is not
    int size;
    struct block* next;
};

#define BLOCK_SIZE sizeof(struct block)


void* global_head = NULL;


 

struct block* find_free(struct block** last, int size) {
    struct block *current = global_head;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

struct block* mem_init(struct block* last, size_t size) {
    struct block* new;
    //void* new_addr = mmap(NULL, size+BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    void* new_addr = sbrk(0);
    void *request = sbrk(size + BLOCK_SIZE);
    (void)request;
    new=new_addr;
    if(last) {
       last->next = new; 
    }
    new->size = size;
    new->free=0;
    new->next=NULL;
    return new;
}


void* svmalloc(size_t size) {
    struct block* block;
    if(!global_head) {
        block = mem_init(NULL, size);
        global_head=block;
    } else {
        struct block* last = global_head;
        block = find_free(&last, size);
        if(!block) {
            block = mem_init(last, size);

        } else {
            block->next = NULL;
            block->free = 0;
        }
    }
    return (block+1);
}
//print free and allocated blocks
void print_heap_layout() {
    struct block* current = global_head;
    while(current) {
        printf("Block: %p, size: %d, free: %d\n", current, current->size, current->free);
        current = current->next;
    }
}

struct block* get_ptr(void* ptr) {
    return (struct block*)ptr-1;
}



void svfree(struct block* ptr) {
    if(!ptr){
        return;
    }
    struct block* blkptr=get_ptr(ptr);
    blkptr->free=1;
}
