#include "associative_array.h"
#include <stdlib.h>
#include <string.h>

typedef struct pair
{
    const char *key;
    int value;
} pair_t;

struct assoc_array_type
{
    pair_t **data;
    size_t capacity;
    size_t len;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_array = malloc(sizeof(struct assoc_array_type));
    if (!assoc_array)
        return NULL;

    assoc_array->data = calloc(1, sizeof(pair_t *));

    if (!assoc_array->data)
    {
        free(assoc_array);
        return NULL;
    }
    assoc_array->len = 0;
    assoc_array->capacity = 1;
    return assoc_array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (assoc_array_clear(*arr) == ASSOC_ARRAY_OK)
    {
        free((*arr)->data);
        free(*arr);
    }

    (*arr) = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int *tmp_value;
    if (assoc_array_find(arr, key, &tmp_value) == ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_KEY_EXISTS;

    if (arr->len == arr->capacity)
    {
        pair_t **tmp = realloc(arr->data, arr->capacity * 2 * sizeof(pair_t *));
        if (!tmp)
            return ASSOC_ARRAY_MEM;
        arr->data = tmp;
        arr->capacity *= 2;
    }

    pair_t *item = malloc(sizeof(pair_t));
    if (!item)
        return ASSOC_ARRAY_MEM;
    item->key = key;
    item->value = num;

    arr->data[arr->len] = item;
    arr->len++;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || strlen(key) == 0 || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    (*num) = NULL;
    for (size_t i = 0; i < arr->len; i++)
        if (strcmp(key, arr->data[i]->key) == 0)
        {
            *num = &arr->data[i]->value;
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

    size_t index;
    for (size_t i = 0; i < arr->len; i++)
        if (strcmp(arr->data[i]->key, key) == 0)
            index = i;

    free(arr->data[index]);

    memmove(arr->data + index, arr->data + index + 1, (arr->len - index - 1) * sizeof(pair_t *));
    arr->len--;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        free(arr->data[i]);

    arr->len = 0;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        action(arr->data[i]->key, &arr->data[i]->value, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    const char *min = arr->data[0]->key;
    *num = &arr->data[0]->value;
    for (size_t i = 0; i < arr->len; i++)
        if (strcmp(arr->data[i]->key, min) < 0)
        {
            min = arr->data[i]->key;
            *num = &arr->data[i]->value;
        }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    const char *max = arr->data[0]->key;
    *num = &arr->data[0]->value;
    for (size_t i = 0; i < arr->len; i++)
        if (strcmp(arr->data[i]->key, max) > 0)
        {
            max = arr->data[i]->key;
            *num = &arr->data[i]->value;
        }

    return ASSOC_ARRAY_OK;
}
