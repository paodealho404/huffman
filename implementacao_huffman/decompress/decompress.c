#include "decompress.h"

void decompress(char *filename)
{    
    int trash_size = 0, huff_tree_size = 0;
    u_char header[2];

    FILE *fp = fopen(filename, "rb");
    read_header(fp, header, &trash_size, &huff_tree_size);

    huff_node *huff_tree = NULL;
    huff_tree = build_huff_tree_from_file(fp, huff_tree, &huff_tree_size);

    //print_huff_pre_order(huff_tree);

    char dec_name[strlen(filename)];
    strcpy(dec_name, filename);
    dec_name[strlen(dec_name) - 5] = '\0';
    //puts(dec_name);

    write_decompressed_bytes(fp, huff_tree, trash_size, fopen(dec_name, "wb"));

    fclose(fp);
}

void read_header(FILE *fp, u_char *header, int *trash_size, int *huff_tree_size)
{
    header[1] = fgetc(fp);
	header[0] = fgetc(fp);

    u_char tr = header[1] >> 5;
    memcpy(trash_size, &tr, 1);
    printf("\n%d\n", (*trash_size));

	header[1] = header[1] << 3;
	header[1] = header[1] >> 3;

	memcpy(huff_tree_size, header, 2);
	printf("\n%d\n", (*huff_tree_size));
}

void write_decompressed_bytes(FILE *compressed, huff_node *huff_tree, int trash_size, FILE *decompressed)
{
    huff_node *curr_node = huff_tree;
    u_char byte, next;
    int bit_count = 7;

    byte = fgetc(compressed);
    while(!feof(compressed))
    {
        next = fgetc(compressed);
        printf("b - "); print_byte(byte);
        printf("n - "); print_byte(next);

        if(!feof(compressed))
        {
            printf("if\n");
            while(bit_count >= 0)
            {
                if(is_huff_leaf(curr_node))
                {
                    fputc(get_byte(curr_node), decompressed);
                    curr_node = huff_tree;
                }

                if(is_bit_i_set(byte, bit_count))
                {
                    curr_node = get_right_node(curr_node);
                }
                else
                {
                    curr_node = get_left_node(curr_node);
                }
                bit_count -= 1;
            }
        }
        else
        {
            printf("else\n");
            while(bit_count >= (trash_size - 1))
            {
                if(is_huff_leaf(curr_node))
                {
                    fputc(get_byte(curr_node), decompressed);
                    curr_node = huff_tree;
                }

                if(is_bit_i_set(byte, bit_count))
                {
                    curr_node = get_right_node(curr_node);
                }
                else
                {
                    curr_node = get_left_node(curr_node);
                }
                bit_count -= 1;                
            }
        }

        bit_count = 7;
        byte = next;
    }
    fclose(decompressed);
}