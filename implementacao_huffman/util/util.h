#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Tipo padrão para abreviar unsigned char
 * 
 */
typedef unsigned char u_char;

/**
 * @brief Tipo padrão para abreviar unsigned long long int
 * 
 */
typedef unsigned long long int ulli;

/**
 * @brief Verifica o estado do bit de posição 'i' de um dado Byte
 * 
 * @param x 
 * @param i 
 * @return int 
 */
int is_bit_i_set(unsigned char x, int i);

/**
 * @brief Altera o estado 1 bit de um determinado Byte em uma posição 'i'
 * 
 * @param x 
 * @param i 
 * @return int 
 */
int set_bit(unsigned char x, int i);

FILE* open_file(char *file_name);

void print_byte(u_char byte);

#endif