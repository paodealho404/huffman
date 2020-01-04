typedef struct binary_tree BINARY_TREE;

int is_bt_empty(BINARY_TREE *bt);

BINARY_TREE* create_empty_binary_tree();

BINARY_TREE* create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right);

BINARY_TREE* add_bt(BINARY_TREE *bt, int item);

BINARY_TREE* search_bt(BINARY_TREE *bt, int item, int *comp);

void print_pre_order_bt(BINARY_TREE *bt);