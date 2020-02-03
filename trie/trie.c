#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#define CHAR_SIZE 26 //número de letras no alfabeto

struct trie
{
    int leaf;
    struct trie *character[CHAR_SIZE];
};

TRIE *create_new_trie_node()
{
    TRIE *node = (TRIE *)malloc(sizeof(TRIE));
    node->leaf = 0;

    int i;

    for (i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }

    return node;
}

void insert_word(TRIE *head, char *string)
{
    TRIE *current = head;

    while (*string)
    {
        if (current->character[*string - 'a'] == NULL) //a letra 'a' corresponde ao número 97 na tabela ascii
        {
            current->character[*string - 'a'] = create_new_trie_node();
        }

        current = current->character[*string - 'a'];

        string++;
    }

    current->leaf = 1;
}

int search_word(TRIE *head, char *string)
{
    if (head == NULL)
        return 0;

    TRIE *current = head;

    while (*string)
    {
        current = current->character[*string - 'a'];

        if (current == NULL)
            return 0;

        string++;
    }

    return current->leaf;
}

int has_children(TRIE *node)
{
    int i;

    for (i = 0; i < CHAR_SIZE; i++)
    {
        if (node->character[i])
            return 1;
    }

    return 0;
}

int remove_word(TRIE **node, char* string)
{
	if (*node == NULL)
		return 0;

	if (*string)
	{
		if (*node != NULL && (*node)->character[*string - 'a'] != NULL &&
			remove_word(&((*node)->character[*string - 'a']), string + 1) &&
			(*node)->leaf == 0)
		{
			if (!has_children(*node))
			{
				free(*node);
				(*node) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	if (*string == '\0' && (*node)->leaf)
	{
		if (!has_children(*node))
		{
			free(*node); 
			(*node) = NULL;
			return 1; 
		}
		else
		{
			(*node)->leaf = 0;
			return 0;
		}
	}

	return 0;
}

int empty_trie(TRIE *head)
{
    return head == NULL ? 1 : 0;
}