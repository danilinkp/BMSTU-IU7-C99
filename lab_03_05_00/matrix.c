#include "matrix.h"
#include <stdio.h>


size_t input_matrix(matrix_t matrix, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
            {
                return ELEM_ERROR;
            }
    return EXIT_SUCCESS;
}

void change_elems_matrix(matrix_t matrix, array_t arr, size_t row, size_t col)
{   
    int c = 0;
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
        {
            if (is_prime(matrix[i][j]))
            {
                matrix[i][j] = arr[c];
                c++;
            }
        }
}

void print_matrix(matrix_t matrix, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            if (j == col - 1)
                printf("%d\n", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
}
