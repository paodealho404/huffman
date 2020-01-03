typedef struct binary_tree BINARY_TREE;

int is_bt_empty(BINARY_TREE *bt);

BINARY_TREE* create_empty_binary_tree();

BINARY_TREE* create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right);

BINARY_TREE* add(BINARY_TREE *bt, int item);

BINARY_TREE* search(BINARY_TREE *bt, int item);

void print_pre_order(BINARY_TREE *bt);