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

int max_under_side_diagonal(matrix_t matrix, size_t row, size_t col)
{
    int max;
    int is_elem_end_with_5_in_matrix = 0;
    for (size_t i = 0; i < row; i++)
        for (size_t j = row - i; j < col; j++)
        {
            if (abs(matrix[i][j]) % 10 == 5)
            {
                if (!is_elem_end_with_5_in_matrix)
                {   
                    max = matrix[i][j];
                    is_elem_end_with_5_in_matrix = 1;
                }
                else
                {
                    if (matrix[i][j] > max)
                        max = matrix[i][j];
                }
            }
        }
    if (is_elem_end_with_5_in_matrix)
        return max;
    else
        return NO_ELEM_ENDS_WITH_5;
}
