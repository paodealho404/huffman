#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "avl.h"

int main()
{
    int i = 0, n;
    int comp_bt = 0, comp_avl = 0;

    BINARY_TREE *bt = create_empty_binary_tree();
    AVL *avl = create_empty_avl();

    FILE *file = fopen("number_list.txt", "r");

    printf("Aguarde a leitura dos 50000 numeros :)\n");
    fscanf(file, "%d", &n);
    while(!feof(file))
    {
        i++;

        bt = add_bt(bt, n);

        avl = add_avl(&(avl), avl, n);

        fscanf(file, "%d", &n);
        printf("%d de 50000... \r", i);
    }
    fclose(file);

    printf("\n");

    printf("\nentre o numero a ser procurado (1 - 50000): \n> ");
    while(1)
    {
        scanf("%d", &n);
        
        BINARY_TREE *n1 = search_bt(bt, n, &comp_bt);
        AVL *n2 = search_avl(avl, n, &comp_avl);

        if(!is_bt_empty(n1) && !is_avl_empty(n2))
            printf("%d encontrado!\n", n);
        else
            printf("%d nao encontrado :(\n", n);
        
        printf("ABB: %d comparacoes\n", comp_bt);
        printf("AVL: %d comparacoes\n", comp_avl);

        FILE *file = fopen("out.txt", "a");
        fprintf(file, "%d %d %d\n", n, comp_bt, comp_avl);
        fclose(file);

        comp_bt = 0;
        comp_avl = 0;
    }

    return 0;
}