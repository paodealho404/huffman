/** 
 * HUFFMAN_TREE ADT
 */

#ifndef huffman_h 
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include "../heap/heap.h"
#include "../util/util.h"

//
// Structs
//

/**
 * @brief Tipo padrão para o nó de uma Árvore de Huffman.
 * 
 */
typedef struct _huffman_node huff_node;
struct _huffman_node
{
    u_char byte;
    ulli freq;
    huff_node *left;
    huff_node *right;
};


//
// Return - int function()
//

/**
 * @brief Verifica se a árvore de Huffman informada (huff_tree) está vazia.
 * 
 * @param huff_tree 
 * @return int 
 */
int is_huff_empty(huff_node *huff_tree);

/**
 * @brief Verifica se o nó informado (node) de uma Árvore de Huffman é um nó folha.
 * 
 * @param node 
 * @return int 
 */
int is_huff_leaf(huff_node *node);


//
// Return - huff_node* function()
//

/**
 * @brief Create a empty huff node object
 * 
 * @return huff_node* 
 */
huff_node* create_empty_huff_node();

/**
 * @brief Cria, inicializa e retorna um novo nó da Árvore de Huffman com
 * um byte informado (byte), uma dada frequência e os nós da esquerda e direita
 * ,respectivamente. 
 * 
 * @param byte 
 * @param freq 
 * @param left 
 * @param right 
 * @return huff_node* 
 */
huff_node* new_huff_node(u_char byte, ulli freq, huff_node *left, huff_node *right);

/**
 * @brief Constrói uma Árvore de Huffman a partir de uma Heap informada (heap) e retorna
 * a raíz da mesma.
 * 
 * @param heap 
 * @return huff_node* 
 */
huff_node* build_huffman_tree(heap_t *heap);

/**
 * @brief Retorna o nó da esquerda de uma Árvore de Huffman informada (node).
 * 
 * @param node 
 * @return huff_node* 
 */
huff_node* get_left_node(huff_node *node);

/**
 * @brief Retorna o nó da direita de uma Árvore de Huffman informada (node).
 * 
 * @param node 
 * @return huff_node* 
 */
huff_node* get_right_node(huff_node *node);

/**
 * @brief Constrói uma Árvore de Huffman a partir de um dado aquivo (fp) e um tamanho
 * de lixo informado (huff_tree_size), em uma determinada Árvore de Huffman vazia (huff_tree).
 * 
 * @param fp 
 * @param huff_tree 
 * @param huff_tree_size 
 * @return huff_node* 
 */
huff_node* build_huff_tree_from_file(FILE *fp, huff_node *huff_tree, short *huff_tree_size);


//
// Return - void function()
//

/**
 * @brief Imprime uma Árvore de Huffman (root) em pré-ordem.
 * 
 * @param root 
 */
void print_huff_pre_order(huff_node *root);

/**
 * @brief Analiza o tamanho de uma Árvore de Huffman informada (node).
 * 
 * @param node 
 * @param huff_tree_size 
 */
void huffman_tree_size(huff_node *node, short *huff_tree_size);

/**
 * @brief Libera o espaço alocado pelas variáveis que armazenam os nós da Árvore de Huffman.
 * 
 * @param root 
 */
void free_huff_tree(huff_node *root);

/**
 * @brief Salva a Huffman Tree (node) em pré-ordem em um determinado arquivo indicado (filename).
 * 
 * @param node 
 * @param filename 
 */
void save_huff_to_file(huff_node *node, char* filename);


//
// Return - u_char function()
//

/**
 * @brief Retorna o byte correspondente a um nó de uma árvore de Huffman (node).
 * 
 * @param node 
 * @return u_char 
 */
u_char get_byte(huff_node *node);


//
// Return ulli - function()
//
/**
 * @brief Retorna a frequência do Byte de um dado nó de uma Árvore de Huffman informada (node).
 * 
 * @param node 
 * @return unsigned long long int
 */
ulli get_frequency(huff_node *node);

#endif