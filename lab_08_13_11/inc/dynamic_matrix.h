#ifndef _DYNAMIC_MATRIX_H_
#define _DYNAMIC_MATRIX_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    size_t rows;
    size_t cols;
    double **data;
} matrix_t;

typedef enum
{
    DATA_ALLOC_ERROR = 1,
    DATA_REALLOC_ERR0R,
    SIZE_READ_ERROR,
    READ_ELEM_ERROR,
    MATRIX_MUL_ERROR,
    MATRIX_ADD_ERROR,
    DETERMINANT_CALC_ERROR
} matrix_errors_t;


void matrix_free(matrix_t *matrix);

int matrix_alloc(matrix_t *matrix);

int read_matrix(FILE *file, matrix_t *matrix);

int matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result);

int matrix_add(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result);

int matrix_determinant(matrix_t *matrix, size_t n, double *result);

void print_matrix_to_file(FILE *file, matrix_t matrix);


#endif //_DYNAMIC_MATRIX_H_
