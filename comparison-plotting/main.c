#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "avl.h"

int main()
{
    int i = 0, n;
    int comp_bt_lin = 0, comp_bt_random = 0, comp_avl_lin = 0, comp_avl_random = 0;

    BINARY_TREE *bt_linear = create_empty_binary_tree();
    BINARY_TREE *bt_random = create_empty_binary_tree();

    AVL *avl_linear = create_empty_avl();
    AVL *avl_random = create_empty_avl();

    FILE *file = fopen("number_list.txt", "r");

    printf("Aguarde a leitura dos 50000 numeros :)\n");
    fscanf(file, "%d", &n);
    while(!feof(file))
    {
        i++;

        bt_linear = add_bt(bt_linear, i);
        bt_random = add_bt(bt_random, n);

        avl_linear = add_avl(&(avl_linear), avl_linear, i);
        avl_random = add_avl(&(avl_random), avl_random, n);

        fscanf(file, "%d", &n);
        printf("%d de 50000... \r", i);
    }
    fclose(file);

    printf("\n");
    print_avl_root(avl_linear);
    print_avl_root(avl_random);

    printf("\nentre o numero a ser procurado (1 - 50000): \n> ");
    while(1)
    {
        scanf("%d", &n);

        BINARY_TREE *n1 = search_bt(bt_linear, n, &comp_bt_lin);
        BINARY_TREE *n2 = search_bt(bt_random, n, &comp_bt_random);
        AVL *n3 = search_avl(avl_linear, n, &comp_avl_lin);
        AVL *n4 = search_avl(avl_random, n, &comp_avl_random);

        if(!is_bt_empty(n1) && !is_bt_empty(n2) && !is_avl_empty(n3) && !is_avl_empty(n4))
            printf("%d encontrado!\n", n);
        else
            printf("%d nao encontrado :(\n", n);
        
        printf("ABB (linear): %d comparacoes\n", comp_bt_lin);
        printf("ABB (random): %d comparacoes\n", comp_bt_random);
        printf("AVL (linear): %d comparacoes\n", comp_avl_lin);
        printf("AVL (random): %d comparacoes\n", comp_avl_random);

        FILE *file = fopen("out.txt", "a");
        fprintf(file, "%d %d %d %d %d\n", n, comp_bt_lin, comp_bt_random, comp_avl_lin, comp_avl_random);
        fclose(file);

        comp_bt_lin = 0;
        comp_bt_random = 0;
        comp_avl_lin = 0;
        comp_avl_random = 0;
    }

    return 0;
}