#ifndef INPUT_MATRIX_H
#define INPUT_MATRIX_H

#include <stdlib.h>

#define N_MAX 10
#define ELEM_ERROR 1
#define NO_ELEM_ENDS_WITH_5 2

typedef int matrix_t[N_MAX][N_MAX];
typedef int array_t[N_MAX];

size_t input_matrix(matrix_t matrix, size_t row, size_t col);
int max_under_side_diagonal(matrix_t matrix, size_t row, size_t col);

#endif