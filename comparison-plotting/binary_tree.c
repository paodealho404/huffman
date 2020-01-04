#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

struct binary_tree
{
    int item;
    BINARY_TREE *left;
    BINARY_TREE *right;
};

int is_bt_empty(BINARY_TREE *bt)
{
    return (bt == NULL);
}

BINARY_TREE* create_empty_binary_tree()
{
    return NULL;
}

BINARY_TREE* create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right)
{
    BINARY_TREE *new_binary_tree = (BINARY_TREE*) malloc(sizeof(BINARY_TREE));
    
    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;

    return new_binary_tree;
}

BINARY_TREE* add_bt(BINARY_TREE *bt, int item)
{
    if(is_bt_empty(bt))
    {
        bt = create_binary_tree(item, NULL, NULL);
    }
    else if(bt->item > item)
    {
        bt->left = add_bt(bt->left, item);
    }
    else
    {
        bt->right = add_bt(bt->right, item);
    }

    return bt;
}

BINARY_TREE* search_bt(BINARY_TREE *bt, int item, int *comp)
{
    *comp += 1;

    if(is_bt_empty(bt) || (bt->item == item))
    {
        return bt;
    }
    else if(bt->item > item)
    {
        return search_bt(bt->left, item, comp);
    }
    else
    {
        return search_bt(bt->right, item, comp);
    }
}

void print_pre_order_bt(BINARY_TREE *bt)
{
    if(!is_bt_empty(bt))
    {
        printf(" %d ", bt->item);
        print_pre_order_bt(bt->left);
        print_pre_order_bt(bt->right);
    }
}