#include "compress.h"

void compress(char* filename)
{
    int i;
	ulli original_size = get_file_size(filename);
	
	printf("\nFile status: Reading file...\n");

	heap_t *heap = make_huff_heap(filename);
	huff_node* huff_tree = build_huffman_tree(heap);
	
    huff_dict *dict = make_huff_dict();
	generate_codes(huff_tree, dict, 0);
	
	short trash_size = calc_trash_size(dict);
	
	short huff_tree_size = 0;
	huffman_tree_size(huff_tree, &huff_tree_size);
	
	char compressed[406];
	char ext[6] = ".huff";

	strcpy(compressed, filename);
	strcat(compressed, ext);
	printf("\nFile status: Processing...\n");
	write_header(trash_size, huff_tree_size, compressed);
	save_huff_to_file(huff_tree, compressed);
	write_encoded_bytes(filename, dict, compressed);
	printf("\nFile status: Compressed!!\n");
	printf("Compressed file: %s\n\n", compressed);

	ulli compressed_size = get_file_size(compressed);
	printf("Original size: %lli\n", original_size);
	printf("Compressed size: %lli\n", compressed_size);
	printf("Reduction of: %lf%%\n\n\n", 100 - (((double) compressed_size / original_size) * 100));
	free_huff_tree(huff_tree);
	free(dict);
}

ulli get_file_size(char *filename)
{
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0L, SEEK_END);
	ulli size = ftell(fp);
	fclose(fp);
	return size;
}

void write_header(short trash_size, short huff_tree_size, char* filename)
{
	u_char byte1, byte2;
	FILE *fp = fopen(filename, "wb");

	byte1 = trash_size << 5 | huff_tree_size >> 8;
	byte2 = huff_tree_size;

	fputc(byte1, fp);
	fputc(byte2, fp);

	fclose(fp);
}

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