#ifndef frequency_h
#define frequency_h

#include <stdio.h>
#include <stdlib.h>
#include "../util/util.h"
#include "../heap/heap.h"
#include "../huffman/huffman.h"

#define MAX_B_TREE 600
#define MAX_BYTE 256


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
ulli* make_new_freq_arr();
ulli* make_count_arr(char *file_name, ulli *original_size);

#endif