#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "heap.h"

#define MAX_B_TREE 600
#define MAX_BYTE 255

// tipo pra contar os bytes da arvore
struct _count_b
{
	u_char byte;
	int freq;
};

typedef struct _count_b count_b_t;

// arvore pra contar os bytes

struct _count_b_tree
{
	count_b_t* arr[MAX_B_TREE];
};

typedef struct _count_b_tree b_tree;

struct _huffman_dict
{
	u_char codes[256][256];
	unsigned short path_bits[256];
	int length[256];
};

// tipo para os codigos de huffman
typedef struct _huffman_dict huff_dict;

u_char* read_bytes(u_char *file_name);

int bb_search(u_char *byte_str, u_char byte);
int search_byte(u_char *byte_str, u_char byte);

int count_byte_freq(u_char *byte_str, u_char byte);
void print_huff_heap(heap_t *heap);

huff_node* pop_huff_heap(heap_t *heap);
void push_huff_heap(heap_t *heap, huff_node *h_node);
heap_t* make_huff_heap(u_char *byte_str);

void sort_byte_str(u_char *byte_str);
int cmp_char(const void *a, const void *b);

void init_huff_dict(huff_dict *dict);
void generate_codes(huff_node *node, huff_dict *dict, int pos);

count_b_t* new_count_b(u_char byte, int freq);
count_b_t** make_count_arr(u_char *byte_str);
count_b_t* count_byte(b_tree *tree, u_char byte, int index, int i);
int main()
{
	int i;
	u_char *bytes_arr;
	bytes_arr = read_bytes("teste.txt");
	heap_t *heap = make_huff_heap(bytes_arr);
					printf("works\n");
	
	huff_dict dict;
	init_huff_dict(&dict);

	huff_node* huff_tree = build_huffman_tree(heap);
	printf(" byte |  freq \n");
	print_huff_pre_order(huff_tree);

	printf("\n\n byte | code \n");
	generate_codes(huff_tree, &dict, 0);
	for(i = 0; i < 256; i++)
	{
		if(dict.length[i] > 0)
		{
			int j;
			printf("%5d | ", i);
			for(j = 0; j < dict.length[i]; j++)
				printf("%d", dict.codes[i][j]);
			printf("\n");
		}
	}

	print_huff_heap(heap);
	printf("\n");
	
    return 0;
}



void print_huff_heap(heap_t *heap)
{
	huff_node *node = pop_huff_heap(heap);
	while(node)
	{
		printf("%u %d\n", get_byte(node), get_frequency(node));
		node = pop_huff_heap(heap);
	}
}

/*
	Abre um arquivo, procura o fim do arquivo usando fseek.
	O fim fica guardado no ponteiro file_ptr, usa ftell pra saber
	o tamanho do arquivo em bytes, rewind pra o ponteiro voltar pro
	inicio do arquivo. Cria um buffer com o tamanho do arquivo
	em bytes + 1, pra guardar o '\0'. E ai fread joga todos os
	bytes do arquivo dentro de um array de char. Char tem 1 byte.
*/
u_char* read_bytes(u_char *file_name)
{
	FILE *file_ptr;
	file_ptr = fopen(file_name, "rb");

	if(file_ptr == NULL)
	{
		printf("shit\n");
		return NULL;
	}

	u_char *buffer;
	long file_length;

	fseek(file_ptr, 0, SEEK_END);
	file_length = ftell(file_ptr);
	rewind(file_ptr);

	buffer = (u_char *) malloc((file_length + 1) * sizeof(u_char));
	fread(buffer, file_length, 1, file_ptr);

	return buffer;
}

/*
	Usa uma funcao da stdlib pra ordenar um array de char.
	A funcao qsort, ela precisa de uma funcao a parte pra 
	comparar o tipo que voce quer ordenar, q no caso eh a cmp_char.

	se a < b ela retorna "alguma coisa" < 0;
	se a == b retorna 0;
	se a > b retorna "alguma coisa" > 0;
*/
void sort_byte_str(u_char *byte_str)
{
	qsort(byte_str, strlen(byte_str), sizeof(u_char), cmp_char);
}

int cmp_char(const void *a, const void *b)
{
	return (*(u_char*)a - *(u_char*)b);
}

/*
	Abstracao do pop_heap q retorna o tipo huff_node
*/
huff_node* pop_huff_heap(heap_t *heap)
{
	p_node_t* node = pop_heap(heap);

	if(!node) return NULL;

	huff_node *huff = (huff_node*) get_node_item(node);

	return huff;
}

/*
	Abstracao de push_heap que ja faz o push de um huff_node
*/
void push_huff_heap(heap_t *heap, huff_node *h_node)
{
	push_heap(heap, h_node, get_frequency(h_node));
}

/*
	Funcao q cria a heap de huff_node a partir do array de char.
	Ela primeiro ordena o array. E entra num loop, ele vai contando
	os bytes iguais, ate algum ser diferente, oq significa q todos 
	os bytes desse tipo foram contados. Faz o push com a frequencia e
	o byte, e ai zera o contador.

	Retorna a heap ja pronta. Talvez precise ficar mais abstrato.
*/

heap_t* make_huff_heap(u_char *byte_str)
{
	heap_t *heap = make_heap();
	count_b_t **byte_arr = make_count_arr(byte_str);

	for(int i = 0; i < MAX_BYTE; i++)
	{
		if(byte_arr[i] != NULL)
		{
			huff_node *node = new_huff_node(byte_arr[i]->byte, byte_arr[i]->freq, NULL, NULL);
			push_huff_heap(heap, node);
		}
	}
	return heap;
}

count_b_t* new_count_b(u_char byte, int freq)
{
	count_b_t *new = (count_b_t*) malloc(sizeof(count_b_t));

	new->byte = byte;
	new->freq = freq;
	return new;
}

count_b_t** make_count_arr(u_char *byte_str)
{
	count_b_t **byte_arr = (count_b_t**) malloc(sizeof(count_b_t*) * MAX_BYTE);

	for(int i = 0; i < MAX_BYTE; i++)
		byte_arr[i] = NULL;

	b_tree* tree = (b_tree*)malloc(sizeof(b_tree));
	for(int i = 0; i < MAX_B_TREE; i++)
	{
		tree->arr[i] = NULL;
	}

	int j = 0;
	for (int i = 0; i < strlen(byte_str); i++)
	{
		count_b_t *temp = count_byte(tree, byte_str[i], 1, 0);
		if(temp)
		{
			byte_arr[j] = temp;
			j++;
		}
	}
	return byte_arr;
}

count_b_t* count_byte(b_tree *tree, u_char byte, int index, int i)
{
	if(i > 7)
	{
			if(tree->arr[index] == NULL)
			{
				count_b_t* new = new_count_b(byte, 1);
				tree->arr[index] = new;
				return new;
			}
			else
			{
				tree->arr[index]->freq++;
				return NULL;
			}
	}

	if(is_bit_i_set(byte, i))
	{
		return count_byte(tree, byte, get_right_son(index), i+1);
	}
	else
	{
		return count_byte(tree, byte, get_left_son(index), i+1);
	}
}

/*
	busca bb q talvez alguem use
*/
int bb_search(u_char *byte_str, u_char byte)
{
	int begin = 0;
	int end = strlen(byte_str) - 1;
	int middle;

	while (begin <= end) 
	{
		middle = (begin + end) / 2;

		if (byte_str[middle] < byte) begin = middle + 1;

		else if (byte_str[middle] > byte) end = middle - 1;

		else return middle;
	}
	return -1;
}

void init_huff_dict(huff_dict *dict)
{
	int i;
	for(i = 0; i < 256; i++)
	{
		dict->length[i] = -1;
		dict->path_bits[i] = 0;
	}
}

void generate_codes(huff_node *node, huff_dict *dict, int level)
{
    if(!is_huff_empty(get_left_node(node)))
    {
        dict->path_bits[level] = 0;
        generate_codes(get_left_node(node), dict, level + 1);
    }
    if(!is_huff_empty(get_right_node(node)))
    {
        dict->path_bits[level] = 1;
        generate_codes(get_right_node(node), dict, level + 1);
    }
    if(is_huff_empty(get_right_node(node)) && is_huff_empty(get_left_node(node)))
    {
        int i;
        for(i = 0; i < level; i++)
        {
            dict->codes[get_byte(node)][i] = dict->path_bits[i];
        }
		dict->length[get_byte(node)] = level;
    }
}