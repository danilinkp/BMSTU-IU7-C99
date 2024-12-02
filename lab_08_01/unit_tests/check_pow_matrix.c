#include "check_pow_matrix.h"
#include "dynamic_matrix.h"
#include <stdlib.h>

START_TEST(test_zero_pow)
{
    matrix_t matrix = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix);

    int data[][3] = {{ 4, 1 },
                     { 3, 7 }};

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = data[i][j];

    int result[][2] = {{ 1, 0 },
                       { 0, 1 }};

    matrix_t matrix_powered = { .rows = 2, .cols = 2 };

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    pow_matrix(&matrix, &matrix_powered, 0);

    ck_assert_int_eq(matrix_powered.rows, result_rows);
    ck_assert_int_eq(matrix_powered.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_powered.data[i][j], result[i][j]);

    matrix_free(&matrix);
    matrix_free(&matrix_powered);
}
END_TEST

START_TEST(test_first_pow)
{
    matrix_t matrix = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix);
    int data[][3] = {{ 4, 1 },
                     { 3, 7 }};

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = data[i][j];

    int result[][2] = {{ 4, 1 },
                       { 3, 7 }};

    matrix_t matrix_powered = { .rows = 2, .cols = 2 };

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    pow_matrix(&matrix, &matrix_powered, 1);

    ck_assert_int_eq(matrix_powered.rows, result_rows);
    ck_assert_int_eq(matrix_powered.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_powered.data[i][j], result[i][j]);

    matrix_free(&matrix);
    matrix_free(&matrix_powered);
}
END_TEST

START_TEST(test_pow_more_one)
{
    matrix_t matrix = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix);

    int data[][3] = {{ 4, 1 },
                     { 3, 7 }};

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = data[i][j];

    int result[][2] = {{ 109, 96 },
                       { 288, 397 }};
    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    matrix_t matrix_powered = { .rows = 2, .cols = 2 };

    pow_matrix(&matrix, &matrix_powered, 3);

    ck_assert_int_eq(matrix_powered.rows, result_rows);
    ck_assert_int_eq(matrix_powered.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_powered.data[i][j], result[i][j]);

    matrix_free(&matrix);
    matrix_free(&matrix_powered);
}

Suite *pow_matrix_suite (void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("pow_matrix");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_zero_pow);
    tcase_add_test(tc_pos, test_first_pow);
    tcase_add_test(tc_pos, test_pow_more_one);
    suite_add_tcase(s, tc_pos);
    return s;
}
