#include "linked_list.h"
#include <stdlib.h>

#define NODE_ALLOC_ERR 1

void free_list(node_t *head, void (*free_data)(void *))
{
    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        if (head->data != NULL)
            free_data(head->data);
        free(head);
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

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    for (; head; head = head->next)
        if (comparator(data, head->data) == 0)
            return head;
    return NULL;
}

void *pop_back(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    node_t *curr = *head;
    node_t *prev = NULL;
    for (; curr->next; curr = curr->next)
        prev = curr;

    if (prev)
    {
        void *data = curr->data;
        free(curr);
        prev->next = NULL;
        return data;
    }
    else
    {
        void *data = (*head)->data;
        free(*head);
        *head = NULL;
        return data;
    }
}

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    node_t *curr_head = *head;
    void *data = (*head)->data;
    *head = curr_head->next;
    free(curr_head);

    return data;
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

void front_back_split(node_t *head, node_t **back)
{
    if (!head || !head->next)
        return;

    node_t *slow = head;
    node_t *fast = head->next;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *back = slow->next;
    slow->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t *tail;

    if (*head_a == NULL)
    {
        tail = *head_b;
        *head_b = NULL;
        return tail;
    }

    if (*head_b == NULL)
    {
        tail = *head_a;
        *head_a = NULL;
        return tail;
    }

    node_t *left_elem = *head_a;
    node_t *right_elem = *head_b;

    if (comparator(left_elem->data, right_elem->data) < 0)
    {
        tail = left_elem;
        left_elem = left_elem->next;
    }
    else
    {
        tail = right_elem;
        right_elem = right_elem->next;
    }

    node_t *result = tail;

    while (left_elem && right_elem)
    {
        if (comparator(left_elem->data, right_elem->data) < 0)
        {
            tail->next = left_elem;
            left_elem = left_elem->next;
        }
        else
        {
            tail->next = right_elem;
            right_elem = right_elem->next;
        }
        tail = tail->next;
    }

    if (left_elem)
        tail->next = left_elem;
    else
        tail->next = right_elem;

    *head_a = NULL;
    *head_b = NULL;

    return result;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (!head || !head->next)
        return head;

    node_t *left = head;
    node_t *right = NULL;
    front_back_split(left, &right);
    left = sort(left, comparator);
    right = sort(right, comparator);

    return sorted_merge(&left, &right, comparator);
}
