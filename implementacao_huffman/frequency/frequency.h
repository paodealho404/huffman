#ifndef frequency_h
#define frequency_h

#include <stdio.h>
#include <stdlib.h>
#include "../util/util.h"
#include "../heap/heap.h"
#include "../huffman/huffman.h"

#define MAX_B_TREE 600
#define MAX_BYTE 256

typedef struct _count_b count_b_t;

typedef struct _count_b_tree b_tree;


/**
 * @brief Retorna um nó de uma Árvore de Huffman a partir de uma Heap informada (heap).
 * 
 * @param heap 
 * @return huff_node* 
 */
huff_node* pop_huff_heap(heap_t *heap);

/**
 * @brief Insere um nó informado de uma Árvore de Huffman (h_node) em uma Heap informada (heap).
 * 
 * @param heap 
 * @param h_node 
 */
void push_huff_heap(heap_t *heap, huff_node *h_node);

heap_t* make_huff_heap(char *file_name, ulli *original_size);
count_b_t* new_count_b(u_char byte, ulli freq);
b_tree* make_new_b_tree();
ulli* make_new_freq_arr();
ulli* make_count_arr(char *file_name, ulli *original_size);
count_b_t* count_byte(b_tree *tree, u_char byte, int index, int i);

#endif