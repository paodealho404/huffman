#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct avl
{
    int item;
    int h;
    AVL* left;
    AVL* right;
};

int is_avl_empty(AVL *avl)
{
    return (avl == NULL);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

AVL* create_empty_avl()
{
    return NULL;
}

AVL* create_avl(int item, AVL *left, AVL *right)
{
    AVL *new_avl = (AVL*) malloc(sizeof(AVL));
    
    new_avl->item = item;
    new_avl->left = left;
    new_avl->right = right;

    return new_avl;
}

int h(AVL *avl)
{
    if (is_avl_empty(avl))
    {
        return -1;
    }
    else
    {
        return 1 + max(h(avl->left), h(avl->right));
    }
}

int balance_factor(AVL *avl)
{
    if(is_avl_empty(avl))
    {
        return 0;
    }
    else if(!is_avl_empty(avl->left) && !is_avl_empty(avl->right))
    {
        return (avl->left->h - avl->right->h);
    }
    else if(!is_avl_empty(avl->left) && is_avl_empty(avl->right))
    {
        return (1 + avl->left->h);
    }
    else
    {
        return (-avl->right->h - 1);
    }
}

AVL* rotate_left(AVL *avl)
{
    AVL *subtree_root = create_empty_avl();

    if(!is_avl_empty(avl) && !is_avl_empty(avl->right))
    {
        subtree_root = avl->right;
        avl->right = subtree_root->left;
        subtree_root->left = avl;
    }

    subtree_root->h = h(subtree_root);
    avl->h = h(avl);

    return subtree_root;
}

AVL* rotate_right(AVL *avl)
{
    AVL *subtree_root = NULL;

    if(!is_avl_empty(avl) && !is_avl_empty(avl->left))
    {
        subtree_root = avl->left;
        avl->left = subtree_root->right;
        subtree_root->right = avl;
    }

    subtree_root->h = h(subtree_root);
    avl->h = h(avl);

    return subtree_root;
}

AVL* add(AVL **root, AVL *avl, int item)
{
    if(is_avl_empty(avl))
    {
        return create_avl(item, NULL, NULL);
    }
    else if(avl->item > item)
    {
        avl->left = add(root, avl->left, item);
    }
    else
    {
        avl->right = add(root, avl->right, item);
    }

    avl->h = h(avl);
    AVL *child;

    if(balance_factor(avl) == 2 || balance_factor(avl) == -2)
    {
        if(balance_factor(avl) == 2)
        {
            child = avl->left;
            if (balance_factor(child) == -1)
            {
                avl->left = rotate_left(child);
            }
            avl = rotate_right(avl);
        }
        else if (balance_factor(avl) == -2)
        {
            child = avl->right;
            if(balance_factor(child) == 1)
            {
                avl->right = rotate_right(child);
            }
            avl = rotate_left(avl);
        }
    }
    
    return avl;
}

AVL* search(AVL *avl, int item, int *comp)
{
    *comp += 1;

    if(is_avl_empty(avl) || (avl->item == item))
    {
        return avl;
    }
    else if(avl->item > item)
    {
        return search(avl->left, item, comp);
    }
    else
    {
        return search(avl->right, item, comp);
    }
}

void print_pre_order(AVL *avl)
{
    if(!is_avl_empty(avl))
    {
        printf(" %d ", avl->item);
        print_pre_order(avl->left);
        print_pre_order(avl->right);
    }
}