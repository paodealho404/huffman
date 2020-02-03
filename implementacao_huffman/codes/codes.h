#ifndef codes_h
#define codes_h

#include <stdlib.h>
#include <stdio.h>
#include "../huffman/huffman.h"

//
// Structs
//

/**
 * @brief Tipo padrão para o dicionário dos bytes da Árvore de Huffman.
 * 
 */
typedef struct _huffman_dict huff_dict;


//
// Return - huff_dict* function()
//

/**
 * @brief Cria um dicionário para os bytes da Árvore de Huffman.
 * 
 * @return huff_dict* 
 */
huff_dict* make_huff_dict();


//
// Return - void function()
//

/**
 * @brief Inicializa um dicionário informado para os bytes da Árvore de Huffman.
 * 
 * @param dict 
 */
void init_huff_dict(huff_dict *dict);

/**
 * @brief Imprime um dicionário informado de bytes da Árvore de Huffman.
 * 
 * @param dict 
 */
void print_huff_dict(huff_dict *dict);

/**
 * @brief Gera os códigos de bytes em um dicionário (dict) a partir de uma Árvore de Huffman informada (node) iniciando
 * em determinado nível (pos), por padrão: 0. 
 * 
 * @param node 
 * @param dict 
 * @param pos 
 */
void generate_codes(huff_node *node, huff_dict *dict, int pos);


//
// Return - int function()
//

/**
 * @brief Informa o respectivo tamanho do código de um dado byte (byte) em
 * determinado dicionário de bytes (dict) da Árvore de Huffman.
 * 
 * @param dict 
 * @param byte 
 * @return int 
 */
int get_code_size(huff_dict *dict, u_char byte);


//
// Return - u_char* function()
//

/**
 * @brief Informa o código de determinado byte (byte) em um dicionário de bytes (dict) da 
 * Árvore de Huffman.
 * 
 * @param dict 
 * @param byte 
 * @return u_char* 
 */
u_char* get_code(huff_dict *dict, u_char byte);


//
// Return - short function()
//

/**
 * @brief Calcula o tamanho do lixo gerado pela Árvore de Huffman a partir de um
 * dicionário de bytes (dict).
 * 
 * @param dict 
 * @return short 
 */
short calc_trash_size(huff_dict *dict);

#endif