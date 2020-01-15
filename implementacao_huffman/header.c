#include <stdio.h>
#include <stdlib.h>

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