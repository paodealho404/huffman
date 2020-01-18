/** 
 * HUFFMAN_TREE ADT
 */
 

//
// Structs
//

/**
 * @brief Tipo padrão para o nó de uma Árvore de Huffman.
 * 
 */
typedef struct _huffman_node huff_node;

/**
 * @brief Tipo padrão para nó de uma Heap.
 * 
 */
typedef struct _p_node p_node_t;

/**
 * @brief Tipo padrão para uma Heap.
 * 
 */
typedef struct _heap heap_t;

//
// Auxiliary typedefs
//

/**
 * @brief Tipo padrão para abreviar unsigned char
 * 
 */
typedef unsigned char u_char;


//
// Return - int function()
//

/**
 * @brief Retorna a frequência do Byte de um dado nó de uma Árvore de Huffman informada (node).
 * 
 * @param node 
 * @return int 
 */
int get_frequency(huff_node *node);

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
// Return - huff_node function()
//

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
huff_node* new_huff_node(u_char byte, int freq, huff_node *left, huff_node *right);

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
 * @brief Retorna um nó de uma Árvore de Huffman a partir de uma Heap informada (heap).
 * 
 * @param heap 
 * @return huff_node* 
 */
huff_node* pop_huff_heap(heap_t *heap);


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
 * @brief Insere um nó informado de uma Árvore de Huffman (h_node) em uma Heap informada (heap).
 * 
 * @param heap 
 * @param h_node 
 */
void push_huff_heap(heap_t *heap, huff_node *h_node);

/**
 * @brief Analiza o tamanho de uma Árvore de Huffman informada (node).
 * 
 * @param node 
 * @param huff_tree_size 
 */
void huffman_tree_size(huff_node *node, long long int *huff_tree_size);

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






