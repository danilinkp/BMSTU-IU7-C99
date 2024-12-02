#include "matrix.h"
#include <stdio.h>

#define ROW_ERR 2
#define COL_ERR 3

int main(void)
{
    matrix_t matrix;
    
    size_t row, col;
    printf("Введите кол-во строк матрицы: ");
    if (scanf("%zu", &row) != 1 || row > 10 || row == 0)
    {
        printf("Ошибка ввода кол-ва строк\n");
        return ROW_ERR;
    }
    printf("Введите кол-во столбцов матрицы: ");
    if (scanf("%zu", &col) != 1 || col > 10 || col == 0)
    {
        printf("Ошибка ввода кол-ва столбцов\n");
        return COL_ERR;
    }

    printf("Введите матрицу:\n");
    if (input_matrix(matrix, row, col) == ELEM_ERROR)
    {
        printf("Ошибка ввода элементы матрицы");
        return ELEM_ERROR;
    }

    array_t line;

    for (size_t i = 0; i < col; i++)
        line[i] = -1;

    size_t new_rows = insert_line(matrix, line, row, col);
    printf("New matrix:\n");
    print_matrix(matrix, new_rows, col);

    return EXIT_SUCCESS;
}