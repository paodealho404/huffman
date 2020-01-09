#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main()
{
    TRIE *head = create_new_trie_node();

    insert_word(head, "rodrigo");

    if (search_word(head, "rodrigo"))
    {
        printf("O nome rodrigo esta na trie\n");
    }
    else
    {
        printf("O nome rodrigo nao estao na trie\n");
    }

    insert_word(head, "pedro");

    if (search_word(head, "pedro"))
    {
        printf("O nome pedro esta na trie\n");
    }
    else
    {
        printf("O nome pedro nao estao na trie\n");
    }

    insert_word(head, "clemens");

    if (search_word(head, "clemens"))
    {
        printf("O nome clemens esta na trie\n");
    }
    else
    {
        printf("O nome clemens nao estao na trie\n");
    }

    insert_word(head, "joao");

    if (search_word(head, "joao"))
    {
        printf("O nome joao esta na trie\n");
    }
    else
    {
        printf("O nome joao nao estao na trie\n");
    }

    insert_word(head, "hello");

    insert_word(head, "helloworld");

    insert_word(head, "h");

    insert_word(head, "hell");

    remove_word(&head, "hello");

    if (!search_word(head, "hello"))
    {
        printf("O nome hello nao esta na trie\n");
    }
    else
    {
        printf("O nome hello ainda esta na trie\n");
    }

    if (empty_trie(head))
    {
        printf("A trie esta vazia\n");
    }
    else
    {
        printf("A trie nao estao vazia\n");
    }
    return 0;
}