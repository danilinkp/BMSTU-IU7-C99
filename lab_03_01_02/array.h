#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#define N_MAX 10
#define ELEM_ERROR 1

typedef int matrix_t[N_MAX][N_MAX];
typedef int array_t[N_MAX];

size_t make_array(matrix_t matrix, array_t arr, size_t row, size_t col);
void print_array(array_t arr, size_t len);

#endif