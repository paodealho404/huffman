#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "heap.h"

struct _huffman_node
{
    u_char byte;
    int freq;
    huff_node *left;
    huff_node *right;
};

int set_bit(unsigned char x, int i)
{
    unsigned char mask = 1 << i;
    return mask | x;
}

int is_bit_i_set(unsigned char x, int i)
{
    unsigned mask = 1 << i;
    return mask & x;
}

int is_huff_empty(huff_node *huff_tree)
{
    return (huff_tree == NULL);
}

int is_huff_leaf(huff_node *node)
{
    return (is_huff_empty(node->left) && is_huff_empty(node->right));
}

huff_node* new_huff_node(u_char byte, int freq, 
						huff_node *left, huff_node *right)
{
	huff_node *new_node = (huff_node*)malloc(sizeof(huff_node));

	new_node->byte = byte;
	new_node->freq = freq;

	new_node->left = left;
	new_node->right = right;
	
	return new_node;
}

huff_node* build_huffman_tree(heap_t *heap)
{
	huff_node *root;

	if(get_size(heap) == 1)
	{
		huff_node *left = pop_huff_heap(heap);
		root = new_huff_node('*', left->freq, left, NULL);
		push_huff_heap(heap, root);
	}

	while(get_size(heap) != 1)
	{
		huff_node *left = pop_huff_heap(heap);
		huff_node *right = pop_huff_heap(heap);
		
		root = new_huff_node('*', left->freq + right->freq, left, right);
		
		push_huff_heap(heap, root);
	}

	root = pop_huff_heap(heap);

    return root;
}

void print_huff_pre_order(huff_node *root)
{
    if(!is_huff_empty(root))
	{
		printf("%5u | %5d \n", root->byte, root->freq);
		print_huff_pre_order(root->left);
		print_huff_pre_order(root->right);
	}
}

u_char get_byte(huff_node *node)
{
    return node->byte;
}

int get_frequency(huff_node *node)
{
    return node->freq;
}

huff_node* get_left_node(huff_node *node)
{
    return node->left;
}

huff_node* get_right_node(huff_node *node)
{
    return node->right;
}

void huffman_tree_size(huff_node *node, long long int *huff_tree_size)
{
	if(node)
	{
		*huff_tree_size += 1;

		if(is_huff_leaf(node) && (node->byte == '*' || node->byte == '\\'))
		{
			*huff_tree_size += 1;
		}

		huffman_tree_size(node->left, huff_tree_size);
		huffman_tree_size(node->right, huff_tree_size);
	}
}

// imprime a huff tree em pre-ordem no arquivo comprimido.
void save_huff_to_file(huff_node *node, char* filename)
{
	if(node)
	{
		FILE *fp = fopen(filename, "a");

		if((node->byte == '*' || node->byte == '\\') && is_huff_leaf(node))
		{
			fputc('\\', fp);
		}

		fputc(node->byte, fp);
		fclose(fp);

		save_huff_to_file(node->left, filename);
		save_huff_to_file(node->right, filename);
	}
}