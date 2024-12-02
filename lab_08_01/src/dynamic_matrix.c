#include "dynamic_matrix.h"
#include <stdio.h>
#include <math.h>


void matrix_free(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        free(matrix->data[i]);
    free(matrix->data);
}

int matrix_alloc(matrix_t *matrix)
{
    matrix->data = calloc(matrix->rows, sizeof(int *));
    if (!matrix->data)
        return DATA_ALLOC_ERROR;
    for (size_t i = 0; i < matrix->rows; i++)
    {
        matrix->data[i] = calloc(matrix->cols, sizeof(int));
        if (!matrix->data[i])
        {
            matrix_free(matrix);
            return DATA_ALLOC_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int read_matrix(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (scanf("%d", &matrix->data[i][j]) != 1)
                return READ_ELEM_ERROR;
    return EXIT_SUCCESS;
}

static int matrix_realloc_rows(matrix_t *matrix, size_t new_rows_size)
{
    int **tmp_data = realloc(matrix->data, new_rows_size * sizeof(int *));
    if (!tmp_data)
        return DATA_REALLOC_ERR0R;
    matrix->data = tmp_data;
    for (size_t i = matrix->rows; i < new_rows_size; i++)
    {
        matrix->data[i] = calloc(matrix->cols, sizeof(int));
        if (!matrix->data[i])
        {
            for (size_t j = matrix->rows; j < i; j++)
                free(matrix->data[j]);
            return DATA_ALLOC_ERROR;
        }
    }
    matrix->rows = new_rows_size;
    return EXIT_SUCCESS;
}


static int matrix_realloc_cols(matrix_t *matrix, size_t new_cols_size)
{
    for (size_t i = 0; i < matrix->rows; i++)
    {
        int *tmp_row = realloc(matrix->data[i], new_cols_size * sizeof(int));
        if (!tmp_row)
        {
            matrix_free(matrix);
            return DATA_REALLOC_ERR0R;
        }
        matrix->data[i] = tmp_row;
    }
    matrix->cols = new_cols_size;
    return EXIT_SUCCESS;
}

static size_t row_index_with_max_elem(matrix_t *matrix)
{
    int max = matrix->data[0][0];
    size_t index = 0;
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (matrix->data[i][j] > max)
            {
                max = matrix->data[i][j];
                index = i;
            }
    return index;
}

static int del_matrix_row(matrix_t *matrix, size_t del_row)
{
    free(matrix->data[del_row]);
    matrix->data[del_row] = NULL;
    for (size_t i = del_row; i < matrix->rows - 1; i++)
        matrix->data[i] = matrix->data[i + 1];
    matrix->data[matrix->rows - 1] = NULL;
    if (matrix_realloc_rows(matrix, matrix->rows - 1) != EXIT_SUCCESS)
        return DATA_REALLOC_ERR0R;
    return EXIT_SUCCESS;
}

static size_t col_index_with_max_elem(matrix_t *matrix)
{
    int max = matrix->data[0][0];
    size_t index = 0;
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (matrix->data[i][j] > max)
            {
                max = matrix->data[i][j];
                index = j;
            }
    return index;
}

static void del_matrix_col(matrix_t *matrix, size_t del_col)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = del_col; j < matrix->cols - 1; j++)
            matrix->data[i][j] = matrix->data[i][j + 1];
    matrix->cols--;
}

int make_matrix_square(matrix_t *matrix)
{
    if (matrix->rows > matrix->cols)
    {
        size_t difference = matrix->rows - matrix->cols;
        for (size_t k = 0; k < difference; k++)
            if (del_matrix_row(matrix, row_index_with_max_elem(matrix)) != EXIT_SUCCESS)
                return DATA_REALLOC_ERR0R;
    }
    else if (matrix->cols > matrix->rows)
    {
        size_t difference = matrix->cols - matrix->rows;
        for (size_t k = 0; k < difference; k++)
            del_matrix_col(matrix, col_index_with_max_elem(matrix));
        if (matrix_realloc_cols(matrix, matrix->rows) != EXIT_SUCCESS)
            return DATA_REALLOC_ERR0R;
    }
    return EXIT_SUCCESS;
}


static double col_avg(matrix_t matrix, size_t rows, size_t col)
{
    double sum = 0;
    for (size_t i = 0; i < rows; i++)
        sum += matrix.data[i][col];
    return sum / rows;
}

static int max_row_elem(matrix_t matrix, size_t cols, size_t row)
{
    int max = matrix.data[row][0];
    for (size_t j = 1; j < cols; j++)
        if (matrix.data[row][j] > max)
            max = matrix.data[row][j];

    return max;
}

static void matrix_rows_add(matrix_t *matrix, size_t rows_add)
{
    for (size_t i = matrix->rows - rows_add; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            matrix->data[i][j] = (int) floor(col_avg(*matrix, i, j));
}

static void matrix_cols_add(matrix_t *matrix, size_t cols_add)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = matrix->cols - cols_add; j < matrix->cols; j++)
            matrix->data[i][j] = max_row_elem(*matrix, j, i);
}

int extend_matrix(matrix_t *matrix_a, matrix_t *matrix_b)
{
    if (matrix_a->rows < matrix_b->rows)
    {
        size_t diff_rows = matrix_b->rows - matrix_a->rows;
        if (matrix_realloc_rows(matrix_a, matrix_b->rows) != EXIT_SUCCESS)
            return DATA_REALLOC_ERR0R;
        matrix_rows_add(matrix_a, diff_rows);

        size_t diff_cols = matrix_b->cols - matrix_a->cols;
        if (matrix_realloc_cols(matrix_a, matrix_b->rows) != EXIT_SUCCESS)
        {
            matrix_a->cols = matrix_a->cols - diff_cols;
            return DATA_REALLOC_ERR0R;
        }
        matrix_cols_add(matrix_a, diff_cols);
    }
    else if (matrix_b->rows < matrix_a->rows)
    {
        size_t diff_rows = matrix_a->rows - matrix_b->rows;
        if (matrix_realloc_rows(matrix_b, matrix_a->rows) != EXIT_SUCCESS)
        {
            matrix_b->rows = matrix_b->rows - diff_rows;
            return DATA_REALLOC_ERR0R;
        }
        matrix_rows_add(matrix_b, diff_rows);

        size_t diff_cols = matrix_a->cols - matrix_b->cols;
        if (matrix_realloc_cols(matrix_b, matrix_a->cols) != EXIT_SUCCESS)
        {
            matrix_b->cols = matrix_b->cols - diff_cols;
            return DATA_REALLOC_ERR0R;
        }
        matrix_cols_add(matrix_b, diff_cols);
    }
    return EXIT_SUCCESS;
}

int matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result)
{
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

static void matrix_cpy(matrix_t *dest, matrix_t *src)
{
    for (size_t i = 0; i < src->rows; i++)
        for (size_t j = 0; j < src->cols; j++)
            dest->data[i][j] = src->data[i][j];
}

static int matrix_mul_self(const matrix_t *matrix, matrix_t *result)
{
    matrix_t cur_res = { .rows = result->rows, .cols = result->cols };
    if (matrix_alloc(&cur_res) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;
    matrix_cpy(&cur_res, result);
    for (size_t i = 0; i < result->rows; i++)
        for (size_t j = 0; j < result->cols; j++)
        {
            result->data[i][j] = 0;
            for (size_t k = 0; k < matrix->rows; k++)
                result->data[i][j] += cur_res.data[i][k] * matrix->data[k][j];
        }
    matrix_free(&cur_res);
    return EXIT_SUCCESS;
}


int pow_matrix(const matrix_t *matrix, matrix_t *result, size_t pow)
{
    if (matrix_alloc(result) != EXIT_SUCCESS)
        return DATA_ALLOC_ERROR;

    for (size_t i = 0; i < result->rows; i++)
        for (size_t j = 0; j < result->cols; j++)
            result->data[i][j] = (i == j) ? 1 : 0;

    for (size_t i = 0; i < pow; i++)
        if (matrix_mul_self(matrix, result) != EXIT_SUCCESS)
            return DATA_ALLOC_ERROR;

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t matrix)
{
    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
        {
            if (j == matrix.cols - 1)
                printf("%d\n", matrix.data[i][j]);
            else
                printf("%d ", matrix.data[i][j]);
        }
}
