#ifndef decompress_h
#define decompress_h

#include <stdio.h>
#include <stdlib.h>
#include "../huffman/huffman.h"
#include "../util/util.h"

void decompress(char *filename);

void read_header(FILE *fp, u_char *header, short *trash_size, short *huff_tree_size);

void write_decompressed_bytes(FILE *compressed, huff_node *huff_tree, short trash_size, FILE *decompressed);

#endif