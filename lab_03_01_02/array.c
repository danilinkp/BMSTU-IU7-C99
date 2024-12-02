#include "array.h"
#include "matrix.h"
#include <stdio.h>


void print_array(array_t arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
}


size_t make_array(matrix_t matrix, array_t arr, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t k = 0; k < col; k++)
            arr[k] = is_alternating_pos_neg(matrix, row, k);
    return col;
}
