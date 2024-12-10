#include "linked_list.h"

#define NODE_ALLOC_ERROR 1

void free_list(node_t *head)
{
    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

int node_alloc(node_t **node)
{
    *node = malloc(sizeof(node_t));
    if (!(*node))
        return NODE_ALLOC_ERROR;
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
