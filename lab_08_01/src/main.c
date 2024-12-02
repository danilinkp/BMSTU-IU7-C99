#include "dynamic_matrix.h"
#include <stdio.h>

int main(void)
{
    matrix_t matrix_a;
    matrix_t matrix_b;
    printf("Введите количество строк матрицы A: ");
    if (scanf("%zu", &matrix_a.rows) != 1 || matrix_a.rows <= 0)
    {
        printf("Ошибка ввода строк");
        return SIZE_READ_ERROR;
    }

    printf("Введите количество столбцов матрицы A: ");
    if (scanf("%zu", &matrix_a.cols) != 1 || matrix_a.cols <= 0)
    {
        printf("Ошибка ввода столбцов");
        return SIZE_READ_ERROR;
    }

    if (matrix_alloc(&matrix_a) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;

    printf("Введите матрицу А:\n");
    int rc = read_matrix(&matrix_a);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_a);
        return rc;
    }

    printf("Введите количество строк матрицы B: ");
    if (scanf("%zu", &matrix_b.rows) != 1 || matrix_b.rows <= 0)
    {
        matrix_free(&matrix_a);
        printf("Ошибка ввода строк");
        return SIZE_READ_ERROR;
    }

    printf("Введите количество столбцов матрицы B: ");
    if (scanf("%zu", &matrix_b.cols) != 1 || matrix_b.cols <= 0)
    {
        matrix_free(&matrix_a);
        printf("Ошибка ввода столбцов");
        return SIZE_READ_ERROR;
    }

    if (matrix_alloc(&matrix_b) != EXIT_SUCCESS)
    {
        matrix_free(&matrix_a);
        return DATA_ALLOC_ERROR;
    }

    printf("Введите матрицу B:\n");
    rc = read_matrix(&matrix_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_b);
        matrix_free(&matrix_a);
        return rc;
    }

    rc = make_matrix_square(&matrix_a);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        return rc;
    }

    rc = make_matrix_square(&matrix_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        return rc;
    }

    rc = extend_matrix(&matrix_a, &matrix_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        return rc;
    }

    int pow_a, pow_b;
    matrix_t pow_matrix_a = { .rows = matrix_a.rows, .cols = matrix_a.cols };
    matrix_t pow_matrix_b = { .rows = matrix_b.rows, .cols = matrix_b.cols };
    matrix_t result = { .rows = pow_matrix_a.rows, .cols = pow_matrix_a.cols };

    printf("Введите степень матрицы А и стпень матрицы B: ");
    if (scanf("%d %d", &pow_a, &pow_b) != 2 || pow_a < 0 || pow_b < 0)
    {
        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        return SIZE_READ_ERROR;
    }

    rc = pow_matrix(&matrix_a, &pow_matrix_a, pow_a);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        matrix_free(&pow_matrix_a);
        return rc;
    }

    rc = pow_matrix(&matrix_b, &pow_matrix_b, pow_b);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_b);
        matrix_free(&matrix_a);
        matrix_free(&pow_matrix_b);
        matrix_free(&pow_matrix_a);
        return rc;
    }


    rc = matrix_mul(&pow_matrix_a, &pow_matrix_b, &result);
    if (rc != EXIT_SUCCESS)
    {
        matrix_free(&matrix_b);
        matrix_free(&matrix_a);
        matrix_free(&pow_matrix_a);
        matrix_free(&pow_matrix_b);
        matrix_free(&result);
        return rc;
    }

    print_matrix(result);

    matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    matrix_free(&pow_matrix_a);
    matrix_free(&pow_matrix_b);
    matrix_free(&result);

    return EXIT_SUCCESS;
}
