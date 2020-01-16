/** 
 * BINARY_TREE ADT
*/

//
// Structs
//

/**
 * @brief Estrutura de uma Árvore de Busca Binária.
 * 
 */
typedef struct binary_tree BINARY_TREE;


//
// Return - BINARY_TREE function()
//

/**
 * @brief Cria uma árvore binária vazia.
 * 
 * @return BINARY_TREE* 
 */
BINARY_TREE* create_empty_binary_tree();

/**
 * @brief Cria e inicializa os componentes (item) , (left) , (right) de um nó de uma árvore binária,
 * retornando o novo nó.
 * 
 * @param item 
 * @param left 
 * @param right 
 * @return BINARY_TREE* 
 */
BINARY_TREE* create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right);

/**
 * @brief Adiciona um dado elemento (item) em uma árvore binária informada (bt).
 * 
 * @param bt 
 * @param item 
 * @return BINARY_TREE* 
 */
BINARY_TREE* add_bt(BINARY_TREE *bt, int item);

BINARY_TREE* search_bt(BINARY_TREE *bt, int item, int *comp);


//
// Return - int function()
//

/**
 * @brief Verifica o estado de uma árvore binária informada (bt), retornando 1 se ela estiver vazia
 * ou 0 se ela não estiver vazia.
 *  
 * @param bt 
 * @return int 
 */
int is_bt_empty(BINARY_TREE *bt);


//
// Return - void function()
//

/**
 * @brief Imprime uma dada árvore binária (bt) em pré-ordem.
 * 
 * @param bt 
 */
void print_pre_order_bt(BINARY_TREE *bt);