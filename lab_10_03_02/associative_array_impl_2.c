#include "associative_array.h"
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    const char *key;
    int value;
    struct node *next;
} node_t;

struct assoc_array_type
{
    node_t *head;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_array = malloc(sizeof(struct assoc_array_type));
    if (!assoc_array)
        return NULL;

    assoc_array->head = NULL;

    return assoc_array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (assoc_array_clear(*arr) == ASSOC_ARRAY_OK)
        free(*arr);

    (*arr) = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int *tmp_value;
    if (assoc_array_find(arr, key, &tmp_value) == ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_KEY_EXISTS;

    node_t *new_elem = malloc(sizeof(node_t));
    if (!new_elem)
        return ASSOC_ARRAY_MEM;
    new_elem->key = key;
    new_elem->value = num;
    new_elem->next = NULL;

    if (!arr->head)
        arr->head = new_elem;
    else
    {
        node_t *curr = arr->head;
        for (; curr->next; curr = curr->next);

        curr->next = new_elem;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || strlen(key) == 0 || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    (*num) = NULL;

    node_t *curr = arr->head;
    for (; curr; curr = curr->next)
        if (strcmp(curr->key, key) == 0)
        {
            *num = &curr->value;
            return ASSOC_ARRAY_OK;
        }

    if (!(*num))
        return ASSOC_ARRAY_NOT_FOUND;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int *tmp_value;
    if (assoc_array_find(arr, key, &tmp_value) != ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *curr = arr->head;
    node_t *prev = NULL;
    while (curr)
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (prev)
                prev->next = curr->next;
            else
                arr->head = curr->next;
            free(curr);
            return ASSOC_ARRAY_OK;
        }
        prev = curr;
        curr = curr->next;
    }
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *next;
    for (; arr->head; arr->head = next)
    {
        next = arr->head->next;
        free(arr->head);
    }
    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *curr = arr->head;
    for (; curr; curr = curr->next)
        action(curr->key, &curr->value, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->head)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *curr = arr->head;
    const char *min = curr->key;
    *num = &curr->value;
    for (; curr; curr = curr->next)
        if (strcmp(curr->key, min) < 0)
        {
            min = curr->key;
            *num = &curr->value;
        }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->head)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *curr = arr->head;
    const char *max = curr->key;
    *num = &curr->value;
    for (; curr; curr = curr->next)
        if (strcmp(curr->key, max) > 0)
        {
            max = curr->key;
            *num = &curr->value;
        }

    return ASSOC_ARRAY_OK;
}