#include "util.h"	

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

FILE* open_file(char *file_name)
{
	FILE *file_ptr;
	file_ptr = fopen(file_name, "rb");

	if(file_ptr == NULL)
	{
		printf("Error reading file\n");
		return NULL;
	}

	return file_ptr;
}

void print_byte(u_char byte)
{
	for(int j = 7; j >= 0; j--)
	{
		printf("%d", is_bit_i_set(byte, j) ? 1 : 0);
	}
	printf("\n");
}