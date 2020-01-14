#include <stdio.h>
#include <stdlib.h>

#include "heap.h" 

struct _huffman_node
{
    char byte;
    int freq;
    struct _huffman_node *left;
    struct _huffman_node *right;
};

typedef struct _huffman_node huff_node;

huff_node* new_huff_node(char byte, int freq,
						huff_node *left, huff_node *right);

char* read_bytes(char *file_name);

int bb_search(char *byte_str, char byte);
int search_byte(char *byte_str, char byte);

int count_byte_freq(char *byte_str, char byte);
void print_huff(heap_t *heap);

huff_node* pop_huff_heap(heap_t *heap);
void push_huff_heap(heap_t *heap, char byte, int freq,
						huff_node *left, huff_node *right);

heap_t* make_huff_heap(char *byte_str);

void sort_byte_str(char *byte_str);
int cmp_char(const void *a, const void *b);

int main()
{
	char *bytes_arr;
	bytes_arr = read_bytes("teste.txt");

	heap_t *heap = make_huff_heap(bytes_arr);
	print_huff(heap);
	
    return 0;
}

void print_huff(heap_t *heap)
{
	huff_node *node = pop_huff_heap(heap);
	while(node)
	{
		printf("%c %d\n",node->byte, node->freq);
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
char* read_bytes(char *file_name)
{
	FILE *file_ptr;
	file_ptr = fopen(file_name, "rb");

	if(file_ptr == NULL)
	{
		printf("shit\n");
		return NULL;
	}

	char *buffer;
	long file_length;

	fseek(file_ptr, 0, SEEK_END);
	file_length = ftell(file_ptr);
	rewind(file_ptr);

	buffer = (char *) malloc((file_length + 1) * sizeof(char));
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
void sort_byte_str(char *byte_str)
{
	qsort(byte_str, strlen(byte_str), sizeof(char), cmp_char);
}

int cmp_char(const void *a, const void *b)
{
	return (*(char*)a - *(char*)b);
}

/*
	Abstracao do pop_heap q retorna o tipo huff_node
*/
huff_node* pop_huff_heap(heap_t *heap)
{
	p_node_t* node = pop_heap(heap);

	if(!node) return NULL;

	huff_node *huff = (huff_node*) node->item;

	return huff;
}

/*
	Abstracao de push_heap que ja faz o push de um huff_node
*/
void push_huff_heap(heap_t *heap, char byte, int freq,
					 huff_node *left, huff_node *right)
{
	huff_node* node = new_huff_node(byte, freq, left, right);
	push_heap(heap, node, freq);
}

/*
	Funcao q cria a heap de huff_node a partir do array de char.
	Ela primeiro ordena o array. E entra num loop, ele vai contando
	os bytes iguais, ate algum ser diferente, oq significa q todos 
	os bytes desse tipo foram contados. Faz o push com a frequencia e
	o byte, e ai zera o contador.

	Retorna a heap ja pronta. Talvez precise ficar mais abstrato.
*/
heap_t* make_huff_heap(char *byte_str)
{
	heap_t *heap = make_heap();
	sort_byte_str(byte_str);

	int freq = 0;
	char byte = byte_str[0];

	for(int i = 0; i <= strlen(byte_str); i++)
	{
		if(byte_str[i] != byte)
		{
			push_huff_heap(heap, byte_str[i], freq, NULL, NULL);
			byte = byte_str[i];
			freq = 0;
		}
		freq++;
	}
	return heap;
}

/*
	Retorna um novo huff_node
*/
huff_node* new_huff_node(char byte, int freq, 
						huff_node *left, huff_node *right)
{
	huff_node *new_node = (huff_node*)malloc(sizeof(huff_node));

	new_node->byte = byte;
	new_node->freq = freq;

	new_node->left = left;
	new_node->right = right;
	
	return new_node;
}

/*
	busca bb q talvez alguem use
*/
int bb_search(char *byte_str, char byte)
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