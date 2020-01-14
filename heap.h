#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HEAP_MAX 1000

/*
    Nó de prioridade, possui um ponteiro pra void e um inteiro
    referente a prioridade do nó.
*/
struct _p_node
{
    void *item;
    int prio;
};

typedef struct _p_node p_node_t; 
 /*
    Estrutura de Heap; Possui um Array de p_node_t e um inteiro
    referente ao seu tamanho;
*/
struct _heap
{
    p_node_t* arr[HEAP_MAX];
    int size;
    int max_buffer_size;
};

typedef struct _heap heap_t;

void push_heap(heap_t *heap, void *p, int prio);

p_node_t* new_node(void *p, int prio);
heap_t* make_heap();

void max_heapify(heap_t *heap);
void heapify(heap_t *heap, int parent);

int get_right_son(int i);
int get_left_son(int i);

void swap(p_node_t **p_1, p_node_t **p_2);

p_node_t* pop_heap(heap_t *heap);
void print_heap(heap_t *heap);

p_node_t* cp_node(p_node_t *node);

void print_arr(int arr[], int n);

