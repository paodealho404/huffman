#include "heap.h"

/*
    Nó de prioridade, possui um ponteiro pra void e um inteiro
    referente a prioridade do nó.
*/
struct _p_node
{
    void *item;
    ulli prio;
};

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


/*
    Implementacao de um pop pra heap. Se a Heap nao estiver vazia,
    ela vai copiar o primeiro node e guardar ele numa var. Se estiver
    vazia ele retorna NULL. 

    Faz um swap do primeiro elemento com o ultimo, diz que o ultimo 
    elemento eh igual a NULL, e diminui o tamanho da Heap. Faz um max
    heapify.
*/
p_node_t* pop_heap(heap_t *heap)
{
    if(heap->size)
    {
        p_node_t* n_node = cp_node(heap->arr[1]);

        if(heap->size > 1) 
            swap(&heap->arr[1], &heap->arr[heap->size]);

        heap->arr[heap->size] = NULL;
        heap->size--;

        min_heapify(heap);

        return n_node;
    }
    return NULL;
}

void print_heap(heap_t *heap)
{
    int i;
    for(i = 1; i < heap->size; i++)
    {
        printf(" %lld |", heap->arr[i]->prio);
        
    }
    printf(" %lld\n", heap->arr[heap->size]->prio);
}

/*
    Copia os elementos de um node pra outro, ou seja,
    copia o node, mas muda o endereco de memoria.
*/
p_node_t* cp_node(p_node_t *node)
{
    p_node_t* cp_node = new_node(node->item, node->prio);
    return cp_node;
}

/*
    Push de heap. Aumenta o tamanho da heap, cria um novo
    node com os elementos que estao no argumento, e diz que
    o ultimo elemento da heap e igual a ele. Faz um min_heapify.
*/
void push_heap(heap_t *heap, void *p, ulli prio)
{
    heap->size++; 

    p_node_t *node = new_node(p, prio);
    heap->arr[heap->size] = node;

    if(heap->size > heap->max_buffer_size)
    {
        //realloc_heap(heap);
    }

    min_heapify(heap);
}
/*
    Retorna um novo p_node_t.
*/
p_node_t* new_node(void *p, int prio)
{
    p_node_t *new_node = (p_node_t*)malloc(sizeof(p_node_t));
    new_node->item = p;
    new_node->prio = prio;

    return new_node;
}

/*
    Inicializa a estrutura de heap.
*/
heap_t* make_heap()
{
    heap_t *heap = (heap_t*)malloc(sizeof(heap_t));

    heap->size = 0;
    heap->max_buffer_size = HEAP_MAX;

    int i;
    for (i = 0; i < HEAP_MAX; i++)
    {
        heap->arr[i] = NULL;
    }
    
    return heap;
}

/*
    Max_heapify, e heapify usando a estrutura de heap
    implementada.
*/
void min_heapify(heap_t *heap)
{
    int i; 
    for(i = heap->size/2; i > 0 ; i--)
    {
        heapify(heap, i);
    }
}
void heapify(heap_t *heap, int parent)
{
    int left = get_left_son(parent);
    int right = get_right_son(parent);

    int smallest = parent;

    if(left <= heap->size)
    {
        if(heap->arr[left]->prio < heap->arr[smallest]->prio)
        {
            smallest = left;
        }
    }

    if(right <= heap->size)
    {
        if(heap->arr[right]->prio < heap->arr[smallest]->prio)
        {
            smallest = right;
        }
    }

    if(smallest != parent)
    {
        swap(&heap->arr[smallest], &heap->arr[parent]);
        heapify(heap, smallest);
    }
}

/*
    troca os valores entre as posições de memória informadas
*/
void swap(p_node_t **p_1, p_node_t **p_2)
{
    p_node_t *temp = *p_1;
    *p_1 = *p_2;
    *p_2 = temp; 
}

/*
    Retorna o filho a esquerda de i, que é o nó pai.
*/
int get_left_son(int i)
{
    return (i*2);
}

/*
    Retorna o filho a direita de i, que é o nó pai.
*/
int get_right_son(int i)
{
    return (i*2) + 1;
}

// Verifica se a heap está vazia ou não
int is_empty(heap_t *heap)
{
    return heap->size == 0 ? 1 : 0;
}

/**
 * @brief Get the node item object
 * 
 * @param node
 * @return void*
 */
void* get_node_item(p_node_t* node)
{
    return node->item;
}

int get_size(heap_t *heap)
{
    return heap->size;
}