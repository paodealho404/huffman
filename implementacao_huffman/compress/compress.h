#ifndef compress_h
#define compress_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../heap/heap.h"
#include "../codes/codes.h"
#include "../frequency/frequency.h"
#include "../huffman/huffman.h"

void compress(char* filename);

void write_header(short trash_size, short huff_tree_size, char* filename);

void write_encoded_bytes(char* filename_src, huff_dict *dict, char* filename_dest);

#endif