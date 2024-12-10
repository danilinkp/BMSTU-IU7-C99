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


int second_max(matrix_t matrix, size_t row, size_t col)
{
    int max = matrix[1][0];
    int second_max = matrix[1][0];
    size_t index;
    for (size_t i = 0; i < col; i++)
        for (size_t j = 0; j < row; j++)
        {
            if (matrix[j][i] > max)
            {
                second_max = max;
                max = matrix[j][i];
                index = i;
            }
            else if (second_max < matrix[j][i] < max)
                second_max = matrix[i][j];
                index = i;
        }
}

void set_col(matrix_t matrix, size_t row, size_t col_1, size_t col_2)
{
    for (size_t i = 0; i < row; i++)
        matrix[i][col_1] = matrix[i][col_2];
}

size_t remove_col(matrix_t matrix, size_t row, size_t col)
{
    size_t index_col = second_max(matrix, row, col);
    size_t c = 0;
    for (size_t i = 0; i < col; i++)
        if (i == index_col)
            c++;
        else
            set_col(matrix, row, i - c, i);

    return row - c;
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