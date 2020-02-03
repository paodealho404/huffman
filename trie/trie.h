/** 
 * Trie ADT 
*/

//
// Structs
//

/**
 * @brief Estrutura da árvore Trie.
 * 
 */
typedef struct trie TRIE;


//
// Return - TRIE function()
//

/**
 * @brief Cria e Retorna um novo nó da árvore Trie.
 * 
 * @return TRIE* 
 */
TRIE* create_new_trie_node();

//
// Return - void function()
//

/**
 * @brief Insere uma palavra nova informada (string) para uma dada árvore de prefixos (head).
 * 
 * @param head 
 * @param string 
 */
void insert_word(TRIE *head, char *string);


//
// Return - int function()
//

/**
 * @brief Busca uma permutação de alguma palavra (string) previamente inserida na Trie (head).
 * 
 * @param head 
 * @param string 
 * @return int 
 */
int search_word(TRIE *head, char *string);

/**
 * @brief Verifica se a árvore de prefixos informada (node) possui ramificações / permutações de palavras,
 * ou seja, se possui subcadeias de caracteres.
 * 
 * @param node 
 * @return int 
 */
int has_children(TRIE *node);

/**
 * @brief Remove recursivamente uma cadeia de caracteres específica informada (string) da árvore Trie (node).
 * 
 * @param node 
 * @param string 
 * @return int 
 */
int remove_word(TRIE **node, char *string);

/**
 * @brief Verifica o estado de uma Trie informada (head), 
 * retornando 1, caso esteja vazia, ou 0, caso contrário.
 * 
 * @param head 
 * @return int 
 */
int empty_trie(TRIE *head);