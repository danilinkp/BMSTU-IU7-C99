#include "dynamic_matrix.h"


void matrix_free(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        free(matrix->data[i]);
    free(matrix->data);
}

int matrix_alloc(matrix_t *matrix)
{
    matrix->data = calloc(matrix->rows, sizeof(double *));
    if (!matrix->data)
        return DATA_ALLOC_ERROR;
    for (size_t i = 0; i < matrix->rows; i++)
    {
        matrix->data[i] = calloc(matrix->cols, sizeof(double));
        if (!matrix->data[i])
        {
            matrix_free(matrix);
            return DATA_ALLOC_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int read_matrix(FILE *file, matrix_t *matrix)
{
    if (fscanf(file, "%zu %zu", &matrix->rows, &matrix->cols) != 2 || matrix->rows <= 0 || matrix->cols <= 0)
        return SIZE_READ_ERROR;

    if (matrix_alloc(matrix) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (fscanf(file, "%lf", &matrix->data[i][j]) != 1)
                return READ_ELEM_ERROR;

    return EXIT_SUCCESS;
}

int matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result)
{
    result->rows = matrix_1->rows;
    result->cols = matrix_2->cols;
    if (matrix_alloc(result) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;

    for (size_t i = 0; i < result->rows; i++)
        for (size_t j = 0; j < result->cols; j++)
        {
            result->data[i][j] = 0;
            for (size_t k = 0; k < matrix_1->cols; k++)
                result->data[i][j] += matrix_1->data[i][k] * matrix_2->data[k][j];
        }
    return EXIT_SUCCESS;
}

int matrix_add(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result)
{
    result->rows = matrix_1->rows;
    result->cols = matrix_1->cols;
    if (matrix_alloc(result) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;

    for (size_t i = 0; i < result->rows; i++)
        for (size_t j = 0; j < result->cols; j++)
            result->data[i][j] = matrix_1->data[i][j] + matrix_2->data[i][j];

    return EXIT_SUCCESS;
}

static int get_minor(const matrix_t *matrix, matrix_t *submatrix, size_t n, size_t row, size_t col)
{
    submatrix->rows = n - 1;
    submatrix->cols = n - 1;
    if (matrix_alloc(submatrix) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;

    size_t minor_i = 0, minor_j;
    for (size_t i = 0; i < n; i++)
    {
        if (i == row)
            continue;
        minor_j = 0;
        for (size_t j = 0; j < n; j++)
        {
            if (j == col)
                continue;
            submatrix->data[minor_i][minor_j] = matrix->data[i][j];
            minor_j++;
        }
        minor_i++;
    }
    return EXIT_SUCCESS;
}

int matrix_determinant(matrix_t *matrix, size_t n, double *result)
{
    if (n == 1)
    {
        *result = matrix->data[0][0];
        return EXIT_SUCCESS;
    }
    else if (n == 2)
    {
        *result = matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
        return EXIT_SUCCESS;
    }
    double det = 0;
    matrix_t minor;
    for (size_t i = 0; i < n; i++)
    {
        if (get_minor(matrix, &minor, n, i, 0) != EXIT_SUCCESS)
            return DETERMINANT_CALC_ERROR;
        double minor_determinant = 0;
        if (matrix_determinant(&minor, n - 1, &minor_determinant) != EXIT_SUCCESS)
        {
            matrix_free(&minor);
            return DETERMINANT_CALC_ERROR;
        }
        int sign = (i % 2) == 0 ? 1 : -1;
        det += sign * matrix->data[i][0] * minor_determinant;
        matrix_free(&minor);
    }
    *result = det;
    return EXIT_SUCCESS;
}

void print_matrix_to_file(FILE *file, matrix_t matrix)
{
    fprintf(file, "%zu %zu\n", matrix.rows, matrix.cols);
    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
        {
            if (j == matrix.cols - 1)
                fprintf(file, "%lf\n", matrix.data[i][j]);
            else
                fprintf(file, "%lf ", matrix.data[i][j]);
        }
}
