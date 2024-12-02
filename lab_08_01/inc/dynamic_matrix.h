#ifndef LAB8_DYNAMIC_MATRIX_H
#define LAB8_DYNAMIC_MATRIX_H

#include <stdlib.h>

typedef struct
{
    size_t rows;
    size_t cols;
    int **data;
} matrix_t;

typedef enum
{
    DATA_ALLOC_ERROR = 1,
    DATA_REALLOC_ERR0R,
    SIZE_READ_ERROR,
    READ_ELEM_ERROR,
} matrix_errors_t;

void matrix_free(matrix_t *matrix);

int matrix_alloc(matrix_t *matrix);

int read_matrix(matrix_t *matrix);

int make_matrix_square(matrix_t *matrix);

int extend_matrix(matrix_t *matrix_a, matrix_t *matrix_b);

int matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result);

int pow_matrix(const matrix_t *matrix, matrix_t *result, size_t pow);

void print_matrix(matrix_t matrix);

#endif //LAB8_DYNAMIC_MATRIX_H
