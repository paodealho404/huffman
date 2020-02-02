#include <stdio.h>
#include "compress/compress.h"
#include "decompress/decompress.h"

int main()
{
    char filename[400];
    int op = 0;

    printf(" _    _  _    _  ______  ______  __  __            _   _ \n");
    printf("| |  | || |  | ||  ____||  ____||  \\/  |    /\\    | \\ | |\n");
    printf("| |__| || |  | || |__   | |__   | \\  / |   /  \\   |  \\| |\n");
    printf("|  __  || |  | ||  __|  |  __|  | |\\/| |  / /\\ \\  | . ` |\n");
    printf("| |  | || |__| || |     | |     | |  | | / ____ \\ | |\\  |\n");
    printf("|_|  |_| \\____/ |_|     |_|     |_|  |_|/_/    \\_\\|_| \\_|\n\n\n");

    while(op != 3) {

        printf("1. Compress\n2. Decompress\n3. Exit\n>");
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
            case 3:
                printf("\nBye\n");
                break;
            default:
                printf("Invalid input.\n");
                break;
        }
    }

    return 0;
}