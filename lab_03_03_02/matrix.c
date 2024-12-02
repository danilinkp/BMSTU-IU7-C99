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

void assign_array(int arr_1[], int arr_2[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        arr_1[i] = arr_2[i];
}

int product_of_elems(array_t arr, size_t len)
{
    int product = 1;
    for (size_t i = 0; i < len; i++)
        product *= arr[i];
    return product;
}

void sort_matrix(matrix_t matrix, size_t row, size_t col)
{
    for (size_t i = 0; i < row - 1; i++)
    {
        size_t jmax = i;
        for (size_t j = i + 1; j < row; j++)
            if (product_of_elems(matrix[j], col) < product_of_elems(matrix[jmax], col))
                jmax = j;
        array_t buf;
        assign_array(buf, matrix[jmax], col);
        for (size_t k = jmax; k > i; k--)
            assign_array(matrix[k], matrix[k - 1], col);
        assign_array(matrix[i], buf, col);
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
