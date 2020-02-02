#ifndef decompress_h
#define decompress_h

#include <stdio.h>
#include <stdlib.h>
#include "../huffman/huffman.h"
#include "../util/util.h"

//
// Return - void function()
//

/**
 * @brief Descomprime um arquivo informado (filename) em codificação de Huffman.
 * 
 * @param filename 
 */
void decompress(char *filename);

/**
 * @brief Lê e altera o tamanho da Árvore de Huffman (huff_tree_size), o tamanho do lixo da codifição de Huffman
 * no cabeçalho (header) de um determinado arquivo (fp).
 * 
 * @param fp 
 * @param header 
 * @param trash_size 
 * @param huff_tree_size 
 */
void read_header(FILE *fp, u_char *header, short *trash_size, short *huff_tree_size);

/**
 * @brief Escreve os bytes descomprimidos a partir de uma dada Árvore de Huffman (huff_tree)
 * e um tamanho do lixo da codificação de Huffman informada (trash_size) de um dado
 * arquivo comprimido de origem(compressed) em determinado arquivo a ser descomprimido
 * (decompressed) de saída.
 * 
 * @param compressed 
 * @param huff_tree 
 * @param trash_size 
 * @param decompressed 
 */
void write_decompressed_bytes(FILE *compressed, huff_node *huff_tree, short trash_size, FILE *decompressed);

#endif