#include "../inc/set.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_ALLOC_ERROR 1
#define ELEM_READ_ERROR 2
#define DATA_REALLOC_ERROR 3


void set_free(set_t *set)
{
    free(set->data);
}

int set_alloc(set_t *set)
{
    set->data = calloc(set->len, sizeof(int));
    if (!set->data)
        return DATA_ALLOC_ERROR;

    return EXIT_SUCCESS;
}

static int realloc_set(set_t *set)
{
    int *tmp = realloc(set->data, set->len);
    if (!tmp)
        return DATA_REALLOC_ERROR;

    set->data = tmp;
    free(tmp);
    return EXIT_SUCCESS;
}

int input_set(set_t *set, size_t nmax)
{
    int *tmp = malloc(nmax * sizeof(int));
    if (!tmp)
    {
        printf("Ошибка выделения памяти.");
        return DATA_ALLOC_ERROR;
    }
    printf("Введите натуральные элементы множества (не верный ввод для завершения):\n");
    size_t cur_ind = 0;
    int tmp_elem;

    while ((scanf("%d", &tmp_elem) == 1 & tmp_elem > 0) || cur_ind < nmax)
    {
        tmp[cur_ind] = tmp_elem;
        cur_ind++;
    }
    set->data = tmp;
    set->len = cur_ind;

    int rc = realloc_set(set);
    if (rc != EXIT_SUCCESS)
        return rc;
    free(tmp);
    return EXIT_SUCCESS;
}

int is_duplicate_elem_in_set(set_t *set)
{
    int is_duplicate_elem_in_set = 0;
    for (size_t i = 0; i < set->len - 1; i++)
        for (size_t j = i + 1; j < set->len; j++)
            if (set->data[i] == set->data[j])
                is_duplicate_elem_in_set = 1;
    return is_duplicate_elem_in_set;
}


int del_duplicates(set_t *set)
{
    int *tmp = malloc(set->len * sizeof(int));
    size_t new_len = 0;
    for (size_t i = 0; i < set->len; i++)
    {
        int is_found = 0;
        for (size_t j = 0; j < new_len; j++)
        {
            if (set->data[i] == tmp[j])
                is_found = 1;
        }
        if (!is_found)
            tmp[new_len++] = set->data[i];
    }

    for (size_t i = 0; i < new_len; i++)
        set->data[i] = tmp[i];

    set->len = new_len;

    int rc = realloc_set(set);
    if (rc != EXIT_SUCCESS)
        return rc;
    free(tmp);
    return EXIT_SUCCESS;
}

//{1, 3, 5, 6}
//{2, 3, 4, 5}
// {3, 5}

int set_intersection(set_t *a, set_t *b, set_t *result)
{
    if (a->len > b->len)
        result->len = a->len;
    else
        result->len = b->len;

    if (set_alloc(result) != 1)
        return DATA_ALLOC_ERROR;

    size_t res_len = 0;
    for (size_t i = 0; i < a->len; i++)
        for (size_t j = 0; j < b->len; j++)
            if (a->data[i] == b->data[j])
                result->data[res_len++] = a->data[i];
    result->len = res_len;
    int rc = realloc_set(result);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}

void print_set(set_t set)
{
    printf("Множество: ");
    for (size_t i = 0; i < set.len; i++)
        printf("%d ", set.data[i]);
}