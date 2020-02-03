#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h"
#include "avl.h"
#define N 25000

int main()
{
    int i = 0, n, min = -1001, max = 1;
    int comp_bt_r = 0, comp_bt_l = 0, comp_avl_r = 0, comp_avl_l = 0;
    
    srand((unsigned) time(NULL));

    BINARY_TREE *bt_r = create_empty_binary_tree();
    BINARY_TREE *bt_l = create_empty_binary_tree();
    AVL *avl_r = create_empty_avl();
    AVL *avl_l = create_empty_avl();

    FILE *input = fopen("number_list.txt", "r");

    printf("Aguarde a leitura dos numeros :)\n");
    fscanf(input, "%d", &n);
    while(!feof(input))
    {
        i++;

        bt_r = add_bt(bt_r, n);
        bt_l = add_bt(bt_l, i);

        avl_r = add_avl(&(avl_r), avl_r, n);
        avl_l = add_avl(&(avl_l), avl_l, i);

        fscanf(input, "%d", &n);
        printf("%d de %d... \r", i, N);
    }
    fclose(input);
    
    printf("\nLeitura finalizada, iniciando sorteios\n");

    FILE *output = fopen("out.txt", "a");
    for(i = 0; i < 100; i++)
    {
        if(i % 4 == 0)
        {
            min += 1000;
            max += 1000;
        }

        n = rand() % (max + 1 - min) + min;
        printf("Numero sorteado: %d\n", n);

        BINARY_TREE *n1 = search_bt(bt_r, n, &comp_bt_r);
        BINARY_TREE *n2 = search_bt(bt_l, n, &comp_bt_l);

        AVL *n3 = search_avl(avl_r, n, &comp_avl_r);
        AVL *n4 = search_avl(avl_l, n, &comp_avl_l);

        fprintf(output, "%d %d %d %d %d\n", n, comp_bt_r, comp_bt_l, comp_avl_r, comp_avl_l);

        comp_bt_r = 0;
        comp_bt_l = 0;
        comp_avl_r = 0;
        comp_avl_l = 0;
    }
    fclose(output);

    return 0;
}