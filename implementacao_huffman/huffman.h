/** 
 * HUFFMAN_TREE ADT
 */
 

//
// Structs
//


// Return - int function()
/**
 * @brief Verifica o estado do bit de posição 'i' de um dado Byte
 * 
 * @param x 
 * @param i 
 * @return int 
 */
int is_bit_i_set(unsigned char x, int i);

/**
 * @brief Altera o estado 1 bit de um determinado Byte em uma posição 'i'
 * 
 * @param x 
 * @param i 
 * @return int 
 */
int set_bit(unsigned char x, int i);


/** 
 * HEAP ADT 
 */ 


//
//Structs
//

/**
 * @brief Nó padrão para a heap.
 * 
 */
typedef struct _p_node p_node_t;

/**
 * @brief Estrutura da heap.
 * 
 */
typedef struct _heap heap_t;


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
void push_heap(heap_t *heap, void *p, int prio);

/**
 * @brief Altera a posição de dois nós informados ( (p_1) e (p_2) ).
 * 
 * @param p_1 
 * @param p_2 
 */
void swap(p_node_t **p_1, p_node_t **p_2);

/**
 * @brief Constrói uma Heap máxima a partir de uma Heap informada (heap).
 * 
 * @param heap 
 */
void max_heapify(heap_t *heap);

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










