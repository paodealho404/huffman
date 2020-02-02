#include "../heap/heap.h"
#include "../huffman/huffman.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/MyMem.h>

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
void test_search_huff_tree()
{
    printf("teste1");
}
void test_create_huffman_tree()
{
    printf("teste3");
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

    printf("\n");
    CU_basic_run_tests();
    return CU_get_error();
}



void initialize_test()
{
    printf("Testando estruturas....");
}
