#pragma once
#include <stddef.h>
struct block* mem_init(struct block* last, size_t size);
void* svmalloc(size_t size);


struct block* find_free(struct block** last, int size);

void print_heap_layout();

struct block* get_ptr(void* ptr);

void free(void* ptr);
