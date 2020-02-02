#include "../heap/heap.h"
#include "../huffman/huffman.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/MyMem.h>
#include <stdio.h>
#include <stdlib.h>

heap_t *NEW_HEAP = NULL;
huff_node *NEW_HUFF_ROOT = NULL;

int init_suite(void) {
    return 0;
}
void test_create_heap()
{
    NEW_HEAP = make_heap();
    CU_ASSERT_PTR_NULL(NEW_HEAP->arr[1]);
    CU_ASSERT_FALSE(NEW_HEAP->size);
}
void test_push_heap() {
    long long int frequency = 15;

    huff_node *AUX_NODE = new_huff_node('A', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);

    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP);
    push_heap(NEW_HEAP, AUX_NODE, frequency);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[1]);
    CU_ASSERT_EQUAL(NEW_HEAP->arr[1]->prio, AUX_NODE->freq);
    CU_ASSERT_EQUAL(NEW_HEAP->size, 1);


    frequency=10;
    CU_FREE(AUX_NODE);

    AUX_NODE = new_huff_node('B', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);

    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP);
    push_heap(NEW_HEAP, AUX_NODE, frequency);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[1]);
    CU_ASSERT_EQUAL(NEW_HEAP->arr[1]->prio, AUX_NODE->freq);
    CU_ASSERT_EQUAL(NEW_HEAP->size, 2);

    frequency=9;
    CU_FREE(AUX_NODE);

    AUX_NODE = new_huff_node('C', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);

    push_heap(NEW_HEAP, AUX_NODE, frequency);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[3]);
    CU_ASSERT_EQUAL(NEW_HEAP->arr[1]->prio, AUX_NODE->freq);
    CU_ASSERT_EQUAL(NEW_HEAP->size, 3);

}
int clean_suite(void) { 
    return 0; 
}
void test_pop_heap()
{
   CU_ASSERT_PTR_NOT_NULL(NEW_HEAP);
   huff_node *AUX_NODE = (huff_node *)pop_heap(NEW_HEAP);
   CU_ASSERT_PTR_NOT_NULL(NEW_HEAP);
   CU_ASSERT_EQUAL(AUX_NODE->freq, 9);

   AUX_NODE = (huff_node *)pop_heap(NEW_HEAP);
   CU_ASSERT_PTR_NOT_NULL(NEW_HEAP);
   CU_ASSERT_EQUAL(AUX_NODE->freq, 10);

   AUX_NODE = (huff_node *)pop_heap(NEW_HEAP);
   CU_ASSERT_PTR_NOT_NULL(NEW_HEAP);
   CU_ASSERT_EQUAL(AUX_NODE->freq, 15);

   AUX_NODE = (huff_node *)pop_heap(NEW_HEAP);
   CU_ASSERT_PTR_NULL(AUX_NODE);
}
void test_create_huffman_tree()
{
    NEW_HUFF_ROOT = create_empty_huff_node();
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
}
void test_generate_huffman_tree()
{
    long long int frequency = 10000;
    push_heap(NEW_HEAP, new_huff_node('A', frequency, NULL, NULL), frequency);
    frequency = 9000;
    push_heap(NEW_HEAP, new_huff_node('B', frequency, NULL, NULL), frequency);
    frequency = 8000;
    push_heap(NEW_HEAP, new_huff_node('C', frequency, NULL, NULL), frequency);
    frequency = 10000;
    push_heap(NEW_HEAP, new_huff_node('D', frequency, NULL, NULL), frequency);
    frequency = 5000;
    push_heap(NEW_HEAP, new_huff_node('E', frequency, NULL, NULL), frequency);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[1]);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[2]);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[3]);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[4]);
    CU_ASSERT_PTR_NOT_NULL(NEW_HEAP->arr[5]);

    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
    NEW_HUFF_ROOT = build_huffman_tree(NEW_HEAP); 
    print_huff_pre_order(NEW_HUFF_ROOT);
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT);  
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT->left);
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT->right);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->left->left->left);

    // **BA*D*EC
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->byte);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->left->byte);
    CU_ASSERT_EQUAL('B', NEW_HUFF_ROOT->left->left->byte);
    CU_ASSERT_EQUAL('A', NEW_HUFF_ROOT->left->right->byte);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->right->byte);
    CU_ASSERT_EQUAL('D', NEW_HUFF_ROOT->right->left->byte);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->right->right->byte);
    CU_ASSERT_EQUAL('E', NEW_HUFF_ROOT->right->right->left->byte);
    CU_ASSERT_EQUAL('C', NEW_HUFF_ROOT->right->right->right->byte);
}
void test_generate_huffman_tree_from_file()
{
    free_huff_tree(NEW_HUFF_ROOT);
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT);

    NEW_HUFF_ROOT = NULL;
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);

    FILE *fp = fopen("tests/tree.txt", "rb");
    short tree_size = 9;
    NEW_HUFF_ROOT = build_huff_tree_from_file(fp, NEW_HUFF_ROOT, &tree_size);
    fclose(fp);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->byte);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->left->byte);
    CU_ASSERT_EQUAL('B', NEW_HUFF_ROOT->left->left->byte);
    CU_ASSERT_EQUAL('A', NEW_HUFF_ROOT->left->right->byte);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->right->byte);
    CU_ASSERT_EQUAL('D', NEW_HUFF_ROOT->right->left->byte);
    CU_ASSERT_EQUAL('*', NEW_HUFF_ROOT->right->right->byte);
    CU_ASSERT_EQUAL('E', NEW_HUFF_ROOT->right->right->left->byte);
    CU_ASSERT_EQUAL('C', NEW_HUFF_ROOT->right->right->right->byte);
}

int main()
{
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Testes básicos", init_suite, clean_suite); 
    
    //Searching for errors

    if (pSuite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    //Structures unit test

    if (CU_add_test(pSuite, "\n\nTestando a criação da Heap\n.", test_create_heap)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "\n\nTestando o enfileiramento na Heap\n", test_push_heap)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "\n\nTestando o desenfileiramento na Heap\n", test_pop_heap)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "\n\nTestando a criação da Árvore de Huffman\n", test_create_huffman_tree)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "\n\nTestando a inserção na Árvore de Huffman\n", test_generate_huffman_tree)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "\n\nTestando a criação da Árvore de Huffman pelo arquivo\n", test_generate_huffman_tree_from_file)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    return CU_get_error();

}



void initialize_test()
{
    printf("Testando estruturas....");
}
