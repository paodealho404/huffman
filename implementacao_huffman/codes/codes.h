#ifndef codes_h
#define codes_h

#include <stdlib.h>
#include <stdio.h>
#include "../huffman/huffman.h"

// tipo para os codigos de huffman
typedef struct _huffman_dict huff_dict;

huff_dict* make_huff_dict();

void init_huff_dict(huff_dict *dict);

void print_huff_dict(huff_dict *dict);

void generate_codes(huff_node *node, huff_dict *dict, int pos);

int get_code_size(huff_dict *dict, u_char byte);

u_char* get_code(huff_dict *dict, u_char byte);

short calc_trash_size(huff_dict *dict);

#endif