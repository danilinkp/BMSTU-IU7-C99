#ifndef INPUT_MATRIX_H
#define INPUT_MATRIX_H

#include <stdlib.h>

#define N_MAX 20
#define ELEM_ERROR 1

typedef int matrix_t[N_MAX][N_MAX];
typedef int array_t[N_MAX];

size_t input_matrix(matrix_t matrix, size_t row, size_t col);
size_t insert_line(matrix_t matrix, array_t line, size_t row, size_t col);
void print_matrix(matrix_t matrix, size_t row, size_t col);

#endif