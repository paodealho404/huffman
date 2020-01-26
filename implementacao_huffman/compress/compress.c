#include "compress.h"

void compress(char* filename)
{
    int i;
	long original_size = 0;

	heap_t *heap = make_huff_heap(filename, &original_size);
	huff_node* huff_tree = build_huffman_tree(heap);

    huff_dict *dict = make_huff_dict();
	generate_codes(huff_tree, dict, 0);
	
	int trash_size = calc_trash_size(dict);
	printf("\ntrash size = %d\n", trash_size);
	
	print_huff_dict(dict);
	
	int huff_tree_size = 0;
	huffman_tree_size(huff_tree, &huff_tree_size);
	printf("\nhuff tree size = %d\n", huff_tree_size);
	
	char compressed[406];
	char ext[6] = ".huff";

	strcpy(compressed, filename);
	strcat(compressed, ext);

	write_header(trash_size, huff_tree_size, compressed);
	save_huff_to_file(huff_tree, compressed);
	write_encoded_bytes(filename, dict, compressed);
}


/*
	função pra escrever o cabeçalho do arquivo comprimido;
	o cabeçalho consiste de 2 bytes, sendo 3 bits para o trash size e
	os 13 restantes para o tamanho da arvore.

	como inteiros possuem 4 bytes e chars apenas 1 byte, ao atribuirmos um valor
	do tipo int para uma variavel u_char apenas o primeiro byte (dir. para esq.) é copiado.
	exempĺo:
	int n = 263; // bits de n: 00000000 00000000 00000001 00000111
	char c = n; // bits de c: 00000111

	por isso, eh preciso fazer shift bit de 8 bits para a direita no valor tree size,
	e atribui-los ao primeiro byte do header. para o segundo byte do header eh so atribuir
	normalmente que teremos os bits desejados.

	para o lixo, temos que fazer shift bit para esquerda de 5 bits, para assim os 3 bits de
	importancia ficarem no inicio do byte. ex: 
	int trash_size = 5; // 00000101
	trash_size << 5; // 10100000
	
	para escrever os bits do lixo junto dos bits da tree size de uma vez só no header, fazemos
	a operação bit-wise OR. ex:
	00000111 // bits do tree size
	10100000 // bits do trash size
	10100111 // resultado do OR

 */
void write_header(int trash_size, int huff_tree_size, char* filename)
{
	u_char byte1, byte2;
	FILE *fp = fopen(filename, "wb");

	byte1 = trash_size << 5 | huff_tree_size >> 8;
	byte2 = huff_tree_size;

	fputc(byte1, fp);
	fputc(byte2, fp);

	fclose(fp);
}

/*
	vai lendo byte por byte até o final do arquivo original (src).
	pra cada byte lido do original, pega o huff code dele e começa a
	preencher um novo byte. quando um byte novo eh completado, ele eh adicionado
	ao arquivo comprimido (dest). ao termino do loop de leitura do src, caso ainda
	exista um novo byte nao completo, ele eh adicionado ao dest.

	ps: dessa vez o contador de bits precisou ir de 7 a 0 para contar da esquerda
	pra direita.
*/
void write_encoded_bytes(char* filename_src, huff_dict *dict, char* filename_dest)
{
	FILE *fp_src = fopen(filename_src, "r+");
	FILE *fp_dest = fopen(filename_dest, "a");
	
	u_char read_byte, new_byte = 0;
	int code_size = 0, bit_count = 7, code_i = 0;
	u_char *code;

	while(fscanf(fp_src, "%c", &read_byte) != EOF)
	{
		code_size = get_code_size(dict, read_byte);
		code = get_code(dict, read_byte);

		for(code_i = 0; code_i < code_size; code_i++)
		{
			if(code[code_i])	
			{
				new_byte = set_bit(new_byte, bit_count);
			}
			bit_count--;

			if(bit_count < 0)
			{
				fputc(new_byte, fp_dest);
				new_byte = 0;
				bit_count = 7;
			}
		}
	}

	if(bit_count < 7)
	{
		fputc(new_byte, fp_dest);
	}

	fclose(fp_dest);
	fclose(fp_src);
}