#include <stdio.h>
#include "compress/compress.h"

int main()
{
    char filename[400];

    printf("Insira o path/nome do arquivo:\n>");
    scanf("%[^\n]s", filename);

    compress(filename);

    return 0;
}