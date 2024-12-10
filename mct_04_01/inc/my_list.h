#ifndef LAB10_MY_LIST_H
#define LAB10_MY_LIST_H

typedef struct node node_t;

struct node
{
    int data;
    node_t *next;
};

void free_list(node_t *node);

int node_alloc(node_t **node);

node_t *push_back(node_t *head, node_t *node);

int insert(node_t *head);

node_t *reverse(node_t *head);

int new_even_list(node_t *head, node_t **result);

void print_list(node_t *head);

#endif //LAB10_MY_LIST_H
