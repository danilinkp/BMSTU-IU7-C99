#ifndef LAB8_SET_H
#define LAB8_SET_H

#include <stdlib.h>

#define NMAX 1024*1024

typedef struct
{
    int *data;
    size_t len;
} set_t;

int set_alloc(set_t *set);

void set_free(set_t *set);

int input_set(set_t *set, size_t nmax);

int is_duplicate_elem_in_set(set_t *set);

int del_duplicates(set_t *set);

int set_intersection(set_t *a, set_t *b, set_t *result);

void print_set(set_t set);

#endif //LAB8_SET_H
