#include <stdio.h>
#include <sys/mman.h>
#include "svmalloc.h"

void* mem_init() {
    return mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

typedef struct block {
    size_t size;
    int free; // 1 if free, 0 if not
    struct block* next;
} block_t;



block_t* global_head = NULL;


void insert_block(block_t* head, block_t* new_block, int index) {
    block_t* current = head;
    for(int i=0; i<index-1; i++) {
        current = current->next;
    }
    new_block->next = current->next;
    current->next = new_block;
}

block_t* find_free(block_t** last, int size){
    block_t* current = global_head;
    while (current && !(current->free==1 && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

void* svmalloc(size_t size) {
    block_t* new_block;
    if(global_head == NULL) {
        new_block = mem_init();
        new_block->size = 4096 - sizeof(block_t);
        new_block->free = 0;
        new_block->next = NULL;
        global_head = new_block;
    } else {
        block_t* last = global_head;
        new_block = find_free(&last, size);
        if(new_block == NULL) {
            new_block = mem_init();
            new_block->size = 4096 - sizeof(block_t);
            new_block->free = 0;
            new_block->next = NULL;
            insert_block(global_head, new_block, 1);
        }
        new_block->free = 0;

    }
    return (void*)(new_block + 1);
}




