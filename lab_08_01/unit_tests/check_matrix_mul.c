#include "check_matrix_mul.h"
#include "dynamic_matrix.h"
#include <stdlib.h>

START_TEST(test_mul_two_non_zeros_matrices)
{
    matrix_t matrix_a = { .rows = 2, .cols = 2 };

    matrix_alloc(&matrix_a);
    int data_a[][2] = {{ 4, 1 },
                       { 3, 7 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    matrix_t matrix_b = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix_b);

    int data_b[][2] = {{ 2, 5 },
                       { 3, 12 }};

    for (size_t i = 0; i < matrix_b.rows; i++)
        for (size_t j = 0; j < matrix_b.cols; j++)
            matrix_b.data[i][j] = data_b[i][j];

    int result[][2] = {{ 11, 32 },
                       { 27, 99 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    matrix_t matrix_res = { .rows = 2, .cols = 2 };

    int rc = matrix_mul(&matrix_a, &matrix_b, &matrix_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix_res.rows, result_rows);
    ck_assert_int_eq(matrix_res.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_res.data[i][j], result[i][j]);

    matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    matrix_free(&matrix_res);
}
END_TEST

START_TEST(test_mul_unit_matrix)
{
    matrix_t matrix_a = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix_a);

    int data_a[][2] = {{ 1, 0 },
                       { 0, 1 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    matrix_t matrix_b = { .rows = 2, .cols = 2 };

    matrix_alloc(&matrix_b);
    int data_b[][2] = {{ 2, 5 },
                       { 3, 12 }};

    for (size_t i = 0; i < matrix_b.rows; i++)
        for (size_t j = 0; j < matrix_b.cols; j++)
            matrix_b.data[i][j] = data_b[i][j];

    int result[][2] = {{ 2, 5 },
                       { 3, 12 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    matrix_t matrix_res = { .rows = 2, .cols = 2 };

    int rc = matrix_mul(&matrix_a, &matrix_b, &matrix_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix_res.rows, result_rows);
    ck_assert_int_eq(matrix_res.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_res.data[i][j], result[i][j]);

    matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    matrix_free(&matrix_res);
}
END_TEST

Suite *matrix_mul_suite (void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_mul");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_mul_two_non_zeros_matrices);
    tcase_add_test(tc_pos, test_mul_unit_matrix);
    suite_add_tcase(s, tc_pos);
    return s;
}
