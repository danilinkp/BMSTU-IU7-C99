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

int is_alternating_pos_neg(matrix_t matrix, size_t row, size_t col)
{
    int is_alternating = 1;
    if (row == 1)
        is_alternating = 0;
    else
        for (size_t i = 1; i < row; i++)
            if (!((matrix[i - 1][col] > 0 && matrix[i][col] < 0) || (matrix[i - 1][col] < 0 && matrix[i][col] > 0)))
                is_alternating = 0;
    return is_alternating;
}
