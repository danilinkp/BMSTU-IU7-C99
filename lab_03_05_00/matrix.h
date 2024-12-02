#ifndef INPUT_MATRIX_H
#define INPUT_MATRIX_H

#include "array.h"

size_t input_matrix(matrix_t matrix, size_t row, size_t col);
void change_elems_matrix(matrix_t matrix, array_t arr, size_t row, size_t col);
void print_matrix(matrix_t matrix, size_t row, size_t col);

#endif