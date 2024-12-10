#include <stdio.h>
#include <stdlib.h>
#include "my_list.h"

int main(void)
{
    int elem;
    node_t *list = NULL;
    int rc;
    printf("Введите элементы списка до 0: ");
    while (scanf("%d", &elem) == 1 && elem != 0)
    {
        node_t *new_node;
        rc = node_alloc(&new_node);
        if (rc != EXIT_SUCCESS)
        {
            free_list(list);
            return rc;
        }
        new_node->data = elem;
        list = push_back(list, new_node);
    }

    rc = insert(list);
    if (rc != EXIT_SUCCESS)
    {
        free_list(list);
        return rc;
    }

    node_t *result = NULL;
    rc = new_even_list(list, &result);
    if (rc != EXIT_SUCCESS)
    {
        if (result)
            free_list(result);
        free_list(list);
    }

    print_list(result);

    return EXIT_SUCCESS;
}