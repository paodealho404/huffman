typedef struct trie TRIE;

TRIE* create_new_trie_node();

void insert_word(TRIE *head, char *string);

int search_word(TRIE *head, char *string);

int has_children(TRIE *node);

int remove_word(TRIE **node, char *string);

int empty_trie(TRIE *head);