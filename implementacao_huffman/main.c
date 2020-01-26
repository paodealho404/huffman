#include <stdio.h>
#include "compress/compress.h"
#include "decompress/decompress.h"

int main()
{
    char filename[400];
    int op;

    printf("1. Compress\n2. Decompress\n>");
    scanf("%d", &op);
    getchar();

    switch(op)    
    {
        case 1:
            printf("File path/name:\n>");
            scanf("%[^\n]s", filename);
            compress(filename);
            break;
        case 2:
            printf("File path/name:\n>");
            scanf("%[^\n]s", filename);
            decompress(filename);
            break;
        default:
            printf("Err\n");
            break;
    }

    return 0;
}