#include "matrix.h"
#include <stdio.h>


void make_matrix(matrix_t matrix, int row, int col)
{
    int c_first = 1;
    for (int i = col - 1; i >= 0; i -= 2)
    {
        for (int j = row - 1; j >= 0; j--)
        {
            matrix[j][i] = c_first;
            c_first++;
        }
        c_first += row;
    }
    int c_second = row + 1;
    for (int i = col - 2; i >= 0; i -= 2)
    {
        for (int j = 0; j < row; j++)
        {
            matrix[j][i] = c_second;
            c_second++;
        }
        c_second += row;
    }
}

void print_matrix(matrix_t matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (j == col - 1)
                printf("%d\n", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
}