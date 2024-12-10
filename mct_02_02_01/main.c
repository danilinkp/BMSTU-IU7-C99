#include "matrix.h"
#include <stdio.h>

#define ROW_ERR 2
#define COL_ERR 3
#define NOT_SQUARE 4


int main(void)
{
    matrix_t matrix;
    
    size_t row, col;
    printf("Введите кол-во строк матрицы: ");
    if (scanf("%zu", &row) != 1 || row > 10 || row < 3)
    {
        printf("Ошибка ввода кол-ва строк\n");
        return ROW_ERR;
    }
    printf("Введите кол-во столбцов матрицы: ");
    if (scanf("%zu", &col) != 1 || col > 10 || col < 3)
    {
        printf("Ошибка ввода кол-ва столбцов\n");
        return COL_ERR;
    }
    
    if (row != col)
    {
        printf("Matrix not square\n");
        return NOT_SQUARE;
    }

    printf("Введите матрицу:\n");
    if (input_matrix(matrix, row, col) == ELEM_ERROR)
    {
        printf("Ошибка ввода элементы матрицы");
        return ELEM_ERROR;
    }

    size_t len = remove_col(matrix, row, col);
    print_matrix(matrix, row, col);

    return 0;
}