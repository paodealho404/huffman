/** 
 * AVL ADT
*/

//
// Structs
//

/**
 * @brief Estrutura de uma árvore AVL.
 * 
 */
typedef struct avl AVL;


//
// Return - AVL function()
//

/**
 * @brief Inicializa uma nova AVL.
 * 
 * @return AVL* 
 */
AVL* create_empty_avl();

/**
 * @brief Cria e inicializa os elementos de um novo nó (item, left, right) de uma AVL.
 * 
 * @param item 
 * @param left 
 * @param right 
 * @return AVL* 
 */
AVL* create_avl(int item, AVL *left, AVL *right);

/**
 * @brief Rotaciona uma árvore desbalanceada (avl) para a esquerda.
 * 
 * @param avl 
 * @return AVL* 
 */
AVL* rotate_left(AVL *avl);

/**
 * @brief Rotaciona uma árvore desbalanceada (avl) para a direita.
 * 
 * @param avl 
 * @return AVL* 
 */
AVL* rotate_right(AVL *avl);

/**
 * @brief Adiciona um novo elemento (item) em uma AVL informada (avl), mantendo sua raíz preservada (root).
 * 
 * @param root 
 * @param avl 
 * @param item 
 * @return AVL* 
 */
AVL* add_avl(AVL **root, AVL *avl, int item);

/**
 * @brief Busca um elemento informado (item) em uma AVL dada (avl), aumentando as comparações em cada iteração (comp).
 * 
 * @param avl 
 * @param item 
 * @param comp 
 * @return AVL* 
 */
AVL* search_avl(AVL *avl, int item, int *comp);


//
// Return - int function()
//

/**
 * @brief Retorna a altura de um dado nó (avl) de uma árvore ou subárvore AVL.
 *  
 * @param avl 
 * @return int 
 */
int h(AVL *avl);

/**
 * @brief Retorna o fator de balanceamento de uma árvore ou subárvore AVL informada (avl).
 * 
 * @param avl 
 * @return int 
 */
int balance_factor(AVL *avl);

/**
 * @brief Retorna o estado de uma AVL informada (avl), 
 * retornando 1 caso esteja vazia, e 0 caso contrário. 
 * 
 * @param avl 
 * @return int 
 */
int is_avl_empty(AVL *avl);

/**
 * @brief Retorna o máximo entre dois numéros informados (a) (b).
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(int a, int b);


//
// Return void - function()
//

/**
 * @brief Imprime uma árvore AVL informada (avl) em pré-ordem.
 * 
 * @param avl
 */
void print_pre_order_avl(AVL *avl);

/**
 * @brief Imprime o nó raíz de uma árvore AVL informada.
 * 
 * @param avl 
 */
void print_avl_root(AVL *avl);