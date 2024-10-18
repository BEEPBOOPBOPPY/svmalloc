#pragma once
#include <stddef.h>
void* mem_init();
void* svmalloc(size_t size);

typedef struct block block_t;
block_t* find_free(block_t** last, int size);
void insert_block(block_t* head, block_t* new_block, int index);
