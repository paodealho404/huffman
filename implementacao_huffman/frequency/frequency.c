#include "frequency.h"

// tipo pra contar os bytes da arvore
struct _count_b
{
	u_char byte;
	ulli freq;
};

// arvore pra contar os bytes
struct _count_b_tree
{
	count_b_t* arr[MAX_B_TREE];
};

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

heap_t* make_huff_heap(char *file_name, ulli *original_size)
{
	heap_t *heap = make_heap();
	ulli *freq_arr = make_count_arr(file_name, original_size);

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
count_b_t* new_count_b(u_char byte, ulli freq)
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
ulli* make_new_freq_arr()
{
	ulli *freq_arr = (ulli*)malloc(sizeof(ulli) * MAX_BYTE);

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
ulli* make_count_arr(char *file_name, ulli *original_size)
{
	FILE* file_ptr = open_file(file_name);
	b_tree* tree = make_new_b_tree();
	ulli *freq_arr = make_new_freq_arr();

	u_char byte;
	while(fscanf(file_ptr, "%c", &byte) != EOF)
	{
		count_b_t *temp = count_byte(tree, byte, 1, 0);
		freq_arr[temp->byte] = temp->freq;

		*original_size++;
	}

	fclose(file_ptr);
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
