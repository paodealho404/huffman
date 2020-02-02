#include "codes.h"

struct _huffman_dict
{
	u_char codes[256][16];
	unsigned short path_bits[256];
	int length[256];
	ulli freq[256];
};

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
		dict->length[i] = 0;
		dict->path_bits[i] = 0;
	}
}

void print_huff_dict(huff_dict *dict)
{
    printf("byte | freq | code\n");
	for(int i = 0; i < 256; i++)
	{
		if(dict->length[i] > 0)
		{
			int j;
			printf("%d | %lld | ", i, dict->freq[i]);
			for(j = 0; j < dict->length[i]; j++)
				printf("%d", dict->codes[i][j]);
			printf("\n");
		}
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

int get_code_size(huff_dict *dict, u_char byte)
{
	return dict->length[byte];
}

//pega o array do novo codigo de um byte
u_char* get_code(huff_dict *dict, u_char byte)
{
	return dict->codes[byte];
}

short calc_trash_size(huff_dict *dict)
{
	int i;
	ulli bits_count = 0;

	for(i = 0; i < 256; i++)
	{
		if(dict->length[i] > 0)
		{
			bits_count += dict->freq[i] * dict->length[i];
		}
	}

	short rest = bits_count % 8;
	
	return (rest > 0) ? 8 - rest : 0;
}