#ifndef LAB10_MATRIX_H
#define LAB10_MATRIX_H

#include "linked_list.h"

typedef struct
{
    node_t *head;
    size_t rows;
    size_t cols;
} matrix_t;

enum matrix_errors
{
    MATRIX_SIZE_READ_ERROR = 2,
    ELEM_READ_ERROR,
    MATRIX_EMPTY_ERROR
};

void free_matrix(matrix_t *matrix);

int matrix_elem_add(matrix_t *matrix, int elem, size_t i, size_t j);

int read_matrix(matrix_t *matrix);

int matrix_add(matrix_t *matrix_1, matrix_t *matrix_2, matrix_t *result);

int matrix_mul(matrix_t *matrix_1, matrix_t *matrix_2, matrix_t *result);

int matrix_lin(matrix_t *matrix);

void print_matrix(matrix_t *matrix);

#endif //LAB10_MATRIX_H
