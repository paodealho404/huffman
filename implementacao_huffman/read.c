#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "heap.h"

#define MAX_B_TREE 600
#define DEBUG if(0)
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
	int freq[256];
};

// tipo para os codigos de huffman
typedef struct _huffman_dict huff_dict;

u_char* read_bytes(u_char *file_name, long *original_size);
void print_bytes(u_char *byte_str, long size);

int bb_search(u_char *byte_str, u_char byte);
int search_byte(u_char *byte_str, u_char byte);

int count_byte_freq(u_char *byte_str, u_char byte);
void print_huff_heap(heap_t *heap);

huff_node* pop_huff_heap(heap_t *heap);
void push_huff_heap(heap_t *heap, huff_node *h_node);
heap_t* make_huff_heap(u_char *byte_str, long *original_size);

void init_huff_dict(huff_dict *dict);
huff_dict* make_huff_dict();
void generate_codes(huff_node *node, huff_dict *dict, int pos);

b_tree* make_new_b_tree();
int* make_new_freq_arr();

count_b_t* new_count_b(u_char byte, int freq);
int* make_count_arr(u_char *byte_str, long *original_size);
count_b_t* count_byte(b_tree *tree, u_char byte, int index, int i);

void write_encoded_bytes(u_char *byte_str, u_char *buffer, huff_dict *dict, long buffer_size);
u_char* get_code(huff_dict *dict, u_char byte);
long get_bytes_size(huff_dict *dict);
int get_code_size(huff_dict *dict, u_char byte);

int calc_trash_size(huff_dict *dict);

int main()
{
	int i;
	long original_size = 0;
	u_char *bytes_arr;
	bytes_arr = read_bytes("teste.txt", &original_size);

	//printf("%li\n", strlen(bytes_arr));

	heap_t *heap = make_huff_heap(bytes_arr, &original_size);

	//printf("works\n");
	
	huff_dict *dict = make_huff_dict();

	huff_node* huff_tree = build_huffman_tree(heap);

	//printf(" byte |  freq \n");
	//print_huff_pre_order(huff_tree);

	//printf("\n\n byte | code \n");

	generate_codes(huff_tree, dict, 0);

	long size = get_bytes_size(dict) / 8;
	
	int trash_size = calc_trash_size(dict);
	printf("\ntrash size = %d\n", trash_size);
	
	if(size > 0)
	{
		if(trash_size > 0) size += 1;
	}
	else
	{
		size = 1;
	}
	
	u_char *bytes_buffer = (u_char*)malloc(size);

	write_encoded_bytes(bytes_arr, bytes_buffer, dict, size);
	print_bytes(bytes_buffer, size);
		
	for(i = 0; i < 256; i++)
	{
		if(dict->length[i] > 0)
		{
			int j;
			printf("%5d | ", i);
			for(j = 0; j < dict->length[i]; j++)
				printf("%d", dict->codes[i][j]);
			printf("\n");
		}
	}
	
	long long int huff_tree_size = 0;
	huffman_tree_size(huff_tree, &huff_tree_size);
	printf("\nhuff tree size = %lli\n", huff_tree_size);
	/*
	print_huff_heap(heap);
	printf("\n");
	*/	

    return 0;
}

void print_bytes(u_char *byte_str, long size)
{
	for (int i = 0; i < size; i++)
	{
		u_char byte = byte_str[i];
		for (int j = 0; j < 8; j++)
		{
			if(is_bit_i_set(byte, j)) printf("1");
			else printf("0");
		}
		printf(" ");
		
	}
	printf("\n");
}

/*
	Essa funcao basicamente sao as variaveis: 

		str_i: controla o index da byte_str;
		code_i: vai controlar o index dos novos codigos dentro do dict;
		bit: controla em qual bit estamos do novo byte sendo sobescrito;
		b_index: controla o index do novo buffer criado, e q eh um argumento;
		code: eh o nova compressao do byte gerado pelo huffman, esta dentro de
		um array de u_char;

	E dois loops:
	
		O for de dentro percorre o byte sendo criado, ou seja, vai de 0 a 7. A cada nova
		iteracao ele checa se o valor de code[code_i] eh 1, se sim ele escreve no byte, se 
		nao, ele nao faz nada. Code_i eh incrementado. Tem uma checagem para ver se code_i
		ultrapassou o valor do novo codigo dentro do dict. Se sim, ele atualiza os valores
		de code e code_size. Code_i eh zerado. 

		No outro for, declaramos um byte vazio que sera escrito, e apos o for de dentro
		acabar, colocamos o novo byte escrito dentro do buffer. O loop para quando b_index
		ultrapassar o valor do buffer.

		Algumas observacoes: 

		code_i eh declarado antes pois mesmo se o loop de for acabar, pode ser que 
		ainda precisemos escrever o resto do codigo no proximo byte. 

*/
void write_encoded_bytes(u_char *byte_str, u_char *buffer, huff_dict *dict, long buffer_size)
{
	int code_size = get_code_size(dict, byte_str[0]);
	u_char *code = get_code(dict, byte_str[0]);

	int code_i = 0;
	int str_i = 0;

	for(int b_index = 0; b_index < buffer_size; b_index++)
	{
		u_char emp_byte = 0;

		for (int bit = 0; bit < 8; bit++)
		{
			if(code[code_i])	
			{
				emp_byte = set_bit(emp_byte, bit);
			}
			code_i++;

			if(code_i == code_size)
			{
				str_i++;

				code_size = get_code_size(dict, byte_str[str_i]);
				code = get_code(dict, byte_str[str_i]);
				code_i = 0;
			}
		}

		buffer[b_index] = emp_byte;
	}
}
//pega o tamanho que os novos codigos vao ocupar em bits
long get_bytes_size(huff_dict *dict)
{
	long size = 0;
	for (int i = 0; i < 256; i++)
	{
		if(dict->length[i] != -1)
		{
		long temp = dict->freq[i] * dict->length[i];
		size += temp;
		}
	}
	return size;
}

//pega o tamanho do novo codigo de um byte
int get_code_size(huff_dict *dict, u_char byte)
{
	return dict->length[byte];
}

//pega o array do novo codigo de um byte
u_char* get_code(huff_dict *dict, u_char byte)
{
	return dict->codes[byte];
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
u_char* read_bytes(u_char *file_name, long *original_size)
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
	printf("tam = %li\n", file_length);
	fseek(file_ptr, 0, SEEK_SET);

	buffer = (u_char *) malloc((file_length + 1) * sizeof(u_char));
	fread(buffer, file_length, 1, file_ptr);
	fclose(file_ptr);

	*original_size = file_length;

	return buffer;
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

heap_t* make_huff_heap(u_char *byte_str, long *original_size)
{
	heap_t *heap = make_heap();
	int *freq_arr = make_count_arr(byte_str, original_size);

	for(int i = 0; i < MAX_BYTE; i++)
	{
		if(freq_arr[i])
		{
			huff_node *node = new_huff_node((u_char) i, freq_arr[i], NULL, NULL);
			push_huff_heap(heap, node);
		}
	}
	return heap;
}

//retorna um novo count_b_t
count_b_t* new_count_b(u_char byte, int freq)
{
	count_b_t *new = (count_b_t*) malloc(sizeof(count_b_t));

	new->byte = byte;
	new->freq = freq;
	return new;
}

//cria e inicializa um tipo b_tree
b_tree* make_new_b_tree()
{
	b_tree* tree = (b_tree*)malloc(sizeof(b_tree));
	for(int i = 0; i < MAX_B_TREE; i++)
	{
		tree->arr[i] = NULL;
	}
	return tree;
}

//cria e inicia um array com todos os indices 0
int* make_new_freq_arr()
{
	int *freq_arr = (int*)malloc(sizeof(int) * MAX_BYTE);

	for (int i = 0; i < MAX_BYTE; i++)
	{
		freq_arr[i] = 0;
	}

	return freq_arr;
}

/*
	Cria um array e uma arvore vazias, e itera pelo byte_str.
	Para cada byte, se faz a checagem na arvore, a frequencia
	eh atualizada no array de frequencias. 

	O array eh um array simples de inteiros iniciado com todas as
	posicoes iguais a 0. Ele funciona como uma hash, ou seja, no
	na posicao que eh igual ao valor de um byte, eh encontrada a
	frequencia desse byte.
*/
int* make_count_arr(u_char *byte_str, long *original_size)
{
	b_tree* tree = make_new_b_tree();
	int *freq_arr = make_new_freq_arr();

	long i;
	for (i = 0; i < (*original_size); i++)
	{
		count_b_t *temp = count_byte(tree, byte_str[i], 1, 0);
		freq_arr[temp->byte] = temp->freq;
	}
	return freq_arr;
}

/*
	Essa funcao conta os bytes usando uma arvores binaria completa
	de altura 8. A arvore esta implementada em Heap.

	Funcao recursiva, se o i-esimo bit de um byte for 1, ele vai pro
	node da direita, se for 0 para o da esquerda. Ate que i = 8, oq quer
	dizer que chegamos em uma folha. Ha entao uma checagem se a folha ja
	foi visitada, se sim, entao apenas se incrementa a frequencia do node 
	do tipo count_b_t, e o node eh retornado. Se nao um novo node eh criado
	com frequencia 1, adicionado a arvore, e ai retornado. 

	A funcao funciona por que numa arvore binaria, o caminho da raiz para
	uma folha eh unico, e num arvore de altura 8, temos 255 folhas, ou seja
	uma para cada possivel byte. Dessa forma temos uma checagem constante 
	em O(8)
*/
count_b_t* count_byte(b_tree *tree, u_char byte, int index, int i)
{
	if(i > 7)
	{
		if(tree->arr[index])
		{
			tree->arr[index]->freq++;
			return tree->arr[index];
		}

		count_b_t* new = new_count_b(byte, 1);
		tree->arr[index] = new;
		return new;
	}

	if(is_bit_i_set(byte, i))
	{
		return count_byte(tree, byte, get_right_son(index), i+1);
	}

	return count_byte(tree, byte, get_left_son(index), i+1);
}

huff_dict* make_huff_dict()
{
	huff_dict *new = (huff_dict*)malloc(sizeof(huff_dict));
	init_huff_dict(new);
	return new;
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
    if(is_huff_leaf(node))
    {
        int i;
        for(i = 0; i < level; i++)
        {
            dict->codes[get_byte(node)][i] = dict->path_bits[i];
        }
		dict->length[get_byte(node)] = level;
		dict->freq[get_byte(node)] = get_frequency(node);
    }
}

int calc_trash_size(huff_dict *dict)
{
	int i, bits_count = 0;

	for(i = 0; i < 256; i++)
	{
		if(dict->length[i] > 0)
		{
			bits_count += dict->freq[i] * dict->length[i];
		}
	}

	int rest = bits_count % 8;
	
	return (rest > 0) ? 8 - rest : 0;
}
