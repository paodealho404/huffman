typedef struct _p_node p_node_t; 
 
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

int is_empty(heap_t *heap);