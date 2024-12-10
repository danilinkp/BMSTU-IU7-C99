#ifndef LAB10_LINKED_LIST_H
#define LAB10_LINKED_LIST_H

#include <stdlib.h>

typedef struct node
{
    size_t row;
    size_t col;
    int data;
    struct node *next;
} node_t;

void free_list(node_t *head);

int node_alloc(node_t **node);

node_t *push_back(node_t *head, node_t *node);

#endif //LAB10_LINKED_LIST_H
