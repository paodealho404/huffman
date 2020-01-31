#ifndef compress_h
#define compress_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../heap/heap.h"
#include "../codes/codes.h"
#include "../frequency/frequency.h"
#include "../huffman/huffman.h"

//
// Return - void function()
//

/**
 * @brief Comprime um determinado arquivo (filename) na codificação de Huffman.
 * 
 * @param filename 
 */
void compress(char* filename);

/**
 * @brief Escreve o cabeçalho com tamanho do lixo (trash_size) e tamanho 
 * da Árvore de Huffman (huff_tree_size) em determinado arquivo (filename).
 * 
 * @param trash_size 
 * @param huff_tree_size 
 * @param filename 
 */
void write_header(short trash_size, short huff_tree_size, char* filename);

/**
 * @brief Escreve os bytes já codificados em determinado arquivo (filename_dest) a partir de
 * um dado dicionário de bytes (dict) e um arquivo de origem (filename_src).
 * 
 * @param filename_src 
 * @param dict 
 * @param filename_dest 
 */
void write_encoded_bytes(char* filename_src, huff_dict *dict, char* filename_dest);

#endif