/** 
 * HUFFMAN_TREE ADT
 */
 

//
// Structs
//

// tipo padrão para o nó da huffman tree
typedef struct _huffman_node huff_node;

// tipo para abreviar unsigned char
typedef unsigned char u_char;

// heap utils
typedef struct _p_node p_node_t;
typedef struct _heap heap_t;

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

int is_huff_empty(huff_node *huff_tree);

int is_huff_leaf(huff_node *node);

huff_node* new_huff_node(u_char byte, int freq,
						huff_node *left, huff_node *right);

huff_node* build_huffman_tree(heap_t *heap);

void print_huff_pre_order(huff_node *root);

u_char get_byte(huff_node *node);

int get_frequency(huff_node *node);

huff_node* get_left_node(huff_node *node);

huff_node* get_right_node(huff_node *node);

huff_node* pop_huff_heap(heap_t *heap);

void push_huff_heap(heap_t *heap, huff_node *h_node);

void huffman_tree_size(huff_node *node, long long int *huff_tree_size);
