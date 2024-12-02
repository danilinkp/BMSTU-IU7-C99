#include "matrix.h"
#include <stdio.h>

#define ROW_ERR 3
#define COL_ERR 4
#define NOT_SQUARE_MATRIX 5

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

    if (col != row)
    {
        printf("Матрица не квадратная");
        return NOT_SQUARE_MATRIX;
    }

    printf("Введите матрицу:\n");
    if (input_matrix(matrix, row, col) == ELEM_ERROR)
    {
        printf("Ошибка ввода элементы матрицы");
        return ELEM_ERROR;
    }

    int max = max_under_side_diagonal(matrix, row, col);
    if (max == NO_ELEM_ENDS_WITH_5)
    {
        printf("Под побочной диагональю нет чисел заканчивающихся на пять.");
        return NO_ELEM_ENDS_WITH_5;
    }
    printf("Максимальное под побочной диагональю: %d", max);

    return EXIT_SUCCESS;
}
