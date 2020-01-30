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
	O array eh um array simples de inteiros iniciado com todas as
	posicoes iguais a 0. Ele funciona como uma hash, ou seja, no
	na posicao que eh igual ao valor de um byte, eh encontrada a
	frequencia desse byte. Pra cada byte encontrado ele incrementa
	um no indice do mesmo.
*/
ulli* make_count_arr(char *file_name, ulli *original_size)
{
	FILE* file_ptr = open_file(file_name);
	ulli *freq_arr = make_new_freq_arr();

	u_char byte;
	while(fscanf(file_ptr, "%c", &byte) != EOF)
	{
		freq_arr[byte]++;

		*original_size++;
	}

	fclose(file_ptr);
	return freq_arr;
}