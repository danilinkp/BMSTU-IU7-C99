#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_ERR 1
#define COL_ERR 2

int main(void)
{
    matrix_t matrix;
    
    int row, col;
    printf("Введите кол-во строк матрицы: ");
    if (scanf("%d", &row) != 1 || row > 10 || row <= 0)
    {
        printf("Ошибка ввода кол-ва строк\n");
        return ROW_ERR;
    }
    printf("Введите кол-во столбцов матрицы: ");
    if (scanf("%d", &col) != 1 || col > 10 || col <= 0)
    {
        printf("Ошибка ввода кол-ва столбцов\n");
        return COL_ERR;
    }

    make_matrix(matrix, row, col);
    print_matrix(matrix, row, col);

    return EXIT_SUCCESS;
}
