#ifndef frequency_h
#define frequency_h

#include <stdio.h>
#include <stdlib.h>
#include "../util/util.h"
#include "../heap/heap.h"
#include "../huffman/huffman.h"

#define MAX_B_TREE 600
#define MAX_BYTE 255

typedef struct _count_b count_b_t;

typedef struct _count_b_tree b_tree;

huff_node* pop_huff_heap(heap_t *heap);
void push_huff_heap(heap_t *heap, huff_node *h_node);
heap_t* make_huff_heap(char *file_name, long *original_size);
count_b_t* new_count_b(u_char byte, int freq);
b_tree* make_new_b_tree();
int* make_new_freq_arr();
int* make_count_arr(char *file_name, long *original_size);
count_b_t* count_byte(b_tree *tree, u_char byte, int index, int i);
FILE* open_file(char *file_name);

#endif