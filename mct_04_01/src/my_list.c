#include "my_list.h"
#include <stdio.h>
#include <stdlib.h>

#define NODE_ALLOC_ERR 1

void free_list(node_t *node)
{
    node_t *next;
    for (; node; node = next)
    {
        next = node->next;
        free(node);
    }
}

int node_alloc(node_t **node)
{
    *node = malloc(sizeof(node_t));
    if (!(*node))
        return NODE_ALLOC_ERR;
    return EXIT_SUCCESS;
}

node_t *push_back(node_t *head, node_t *node)
{
    if (!head)
        return node;

    node_t *curr = head;
    for (; curr->next; curr = curr->next);
    curr->next = node;

    return head;
}


int insert(node_t *head)
{
    node_t *curr = head;
    int rc;
    while (curr)
    {
        if (curr->data % 2 == 0)
        {
            node_t *new_node;
            rc = node_alloc(&new_node);
            if (rc != EXIT_SUCCESS)
                return rc;
            new_node->data = 100;
            new_node->next = curr->next;
            curr->next = new_node;
            curr = new_node->next;
        }
        else
            curr = curr->next;
    }
    return EXIT_SUCCESS;
}

node_t *reverse(node_t *head)
{
    node_t *prev = NULL;
    node_t *curr = head;
    node_t *next;
    for (; curr; curr = next)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }
    return prev;
}

int new_even_list(node_t *head, node_t **result)
{
    node_t *reversed_list = reverse(head);
    int odd_node_found = 0;
    node_t *curr = reversed_list;
    for (; curr && !odd_node_found; curr = curr->next)
    {
        if (curr->data % 2 == 0)
        {
            node_t *new_node;
            int rc = node_alloc(&new_node);
            if (rc != EXIT_SUCCESS)
                return rc;
            new_node->data = curr->data;
            new_node->next = NULL;

            *result = push_back(*result, new_node);
        }
        else
            odd_node_found = 1;
    }
    return EXIT_SUCCESS;
}

void print_list(node_t *head)
{
    node_t *curr = head;
    for (; curr; curr = curr->next)
        printf("%d ", curr->data);
}
