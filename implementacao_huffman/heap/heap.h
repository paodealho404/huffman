/** 
 * HEAP ADT 
 */ 

#ifndef heap_h 
#define heap_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../util/util.h"

#define HEAP_MAX 257

//
//Structs
//

/**
 * @brief Nó padrão para a heap.
 * 
 */
typedef struct _p_node p_node_t;
struct _p_node
{
    void *item;
    ulli prio;
};

/**
 * @brief Estrutura da heap.
 * 
 */
typedef struct _heap heap_t;
struct _heap
{
    p_node_t* arr[HEAP_MAX];
    int size;
    int max_buffer_size;
};


// 
// Return - void function()
//

/**
 * @brief Insere um elemento novo (p) com prioridade
 *  definida (prio) em uma Heap informada (heap)
 * 
 * @param heap 
 * @param p 
 * @param prio 
 */
void push_heap(heap_t *heap, void *p, ulli prio);

/**
 * @brief Altera a posição de dois nós informados ( (p_1) e (p_2) ).
 * 
 * @param p_1 
 * @param p_2 
 */
void swap(p_node_t **p_1, p_node_t **p_2);

/**
 * @brief Constrói uma Heap mínima a partir de uma Heap informada (heap).
 * 
 * @param heap 
 */
void min_heapify(heap_t *heap);

/**
 * @brief Busca e Reposiciona os nós de uma Heap infomada (heap) 
 * de modo a construir uma nova heap a partir de um de seus índices (parent).
 * 
 * @param heap 
 * @param parent 
 */
void heapify(heap_t *heap, int parent);

/**
 * @brief Imprime uma Heap informada (heap).
 * 
 * @param heap 
 */
void print_heap(heap_t *heap);

/**
 * @brief Imprime um array infomado (arr[]) de (n) indíces.
 * 
 * @param arr 
 * @param n 
 */
void print_arr(int arr[], int n);


//
// Return - int function()
//

/**
 * @brief Retorna o estado de uma Heap informada (heap), retornando
 *  0 se estiver vazia ou 1 se não estiver vazia.
 * 
 * @param heap 
 * @return int 
 */
int is_empty(heap_t *heap);

/**
 * @brief Retorna o indice do elemento filho da direita de um dado indice (i).
 * 
 * @param i 
 * @return int 
 */
int get_right_son(int i);

/**
 * @brief Retorna o indice do elemento filho da esquerda de um dado indice (i).
 * 
 * @param i 
 * @return int 
 */
int get_left_son(int i);


//
// Return - p_node_t function()
//

/**
 * @brief Cria e retorna um novo nó podendo conter qualquer elemento informadado (p)
 *  com uma dada prioridade (prio).
 * 
 * @param p 
 * @param prio 
 * @return p_node_t* 
 */
p_node_t* new_node(void *p, int prio);

/**
 * @brief Copia e retorna um novo nó com base em um nó informado (node).
 * 
 * @param node 
 * @return p_node_t* 
 */
p_node_t* cp_node(p_node_t *node);

/**
 * @brief Remove e retorna o nó de maior prioridade de uma Heap informada (heap).
 * 
 * @param heap 
 * @return p_node_t* 
 */
p_node_t* pop_heap(heap_t *heap);


//
// Heap
//
/**
 * @brief Cria e inicializa uma Heap nova.
 * 
 * @return heap_t* 
 */
heap_t* make_heap();

/**
 * @brief Retorna o item de um nó da Heap.
 * 
 * @param node 
 * @return void* 
 */
void* get_node_item(p_node_t *node);

/**
 * @brief retorna o tamanho (size) de uma heap
 * 
 * @param heap 
 * @return int 
 */
int get_size(heap_t *heap);

#endif