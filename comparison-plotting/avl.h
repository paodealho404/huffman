typedef struct avl AVL;

int is_avl_empty(AVL *avl);

int max(int a, int b);

AVL* create_empty_avl();

AVL* create_avl(int item, AVL *left, AVL *right);

int h(AVL *avl);

int balance_factor(AVL *avl);

AVL* rotate_left(AVL *avl);

AVL* rotate_right(AVL *avl);

AVL* add(AVL **root, AVL *avl, int item);

AVL* search(AVL *avl, int item, int *comp);

void print_pre_order(AVL *avl);