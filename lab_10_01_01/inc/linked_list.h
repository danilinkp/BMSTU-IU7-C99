#ifndef LAB10_LINKED_LIST_H
#define LAB10_LINKED_LIST_H

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};

void free_list(node_t *head, void (*free_data)(void *));

int node_alloc(node_t **node);

node_t *push_back(node_t *head, node_t *node);

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));

void *pop_back(node_t **head);

void *pop_front(node_t **head);

node_t *reverse(node_t *head);

void front_back_split(node_t *head, node_t **back);

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif //LAB10_LINKED_LIST_H
