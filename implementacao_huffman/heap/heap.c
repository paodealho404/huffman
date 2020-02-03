#include "heap.h"
#include "../huffman/huffman.h"

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
    huff_node *aux = NULL;
    for(i = 1; i <= heap->size; i++)
    {
        aux = (huff_node *) heap->arr[i];
        printf(" %lld | %c", heap->arr[i]->prio, (int)aux->byte);
        
    }
    printf(" %lld\n", heap->arr[heap->size]->prio);
}

p_node_t* cp_node(p_node_t *node)
{
    p_node_t* cp_node = new_node(node->item, node->prio);
    return cp_node;
}

void push_heap(heap_t *heap, void *p, ulli prio)
{
    heap->size++; 

    p_node_t *node = new_node(p, prio);
    heap->arr[heap->size] = node;

    min_heapify(heap);
}

p_node_t* new_node(void *p, int prio)
{
    p_node_t *new_node = (p_node_t*)malloc(sizeof(p_node_t));
    new_node->item = p;
    new_node->prio = prio;

    return new_node;
}

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

void swap(p_node_t **p_1, p_node_t **p_2)
{
    p_node_t *temp = *p_1;
    *p_1 = *p_2;
    *p_2 = temp; 
}

int get_left_son(int i)
{
    return (i*2);
}

int get_right_son(int i)
{
    return (i*2) + 1;
}

int is_empty(heap_t *heap)
{
    return heap->size == 0 ? 1 : 0;
}

void* get_node_item(p_node_t* node)
{
    return node->item;
}

int get_size(heap_t *heap)
{
    return heap->size;
}