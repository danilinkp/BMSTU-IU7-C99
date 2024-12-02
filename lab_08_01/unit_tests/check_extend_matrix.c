#include "check_extend_matrix.h"
#include "dynamic_matrix.h"
#include <stdlib.h>

START_TEST(test_matrix_add_one_row_one_col)
{
    matrix_t matrix_a = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix_a);

    int data_a[][2] = {{ 4, 1 },
                       { 3, 7 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    matrix_t matrix_b = { .rows = 3, .cols = 3 };

    int result[][3] = {{ 4, 1, 4 },
                       { 3, 7, 7 },
                       { 3, 4, 4 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    int rc = extend_matrix(&matrix_a, &matrix_b);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix_a.rows, result_rows);
    ck_assert_int_eq(matrix_a.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_a.data[i][j], result[i][j]);

    matrix_free(&matrix_a);
}
END_TEST

START_TEST(test_matrices_with_same_sizes)
{
    matrix_t matrix_a = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix_a);

    int data_a[][2] = {{ 4, 1 },
                       { 3, 7 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    matrix_t matrix_b = { .rows = 2, .cols = 2 };

    int result[][2] = {{ 4, 1 },
                       { 3, 7 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    int rc = extend_matrix(&matrix_a, &matrix_b);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix_a.rows, result_rows);
    ck_assert_int_eq(matrix_a.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix_a.data[i][j], result[i][j]);

    matrix_free(&matrix_a);
}
END_TEST


Suite *extend_matrix_suite(void)
{
    Suite * s;
    TCase *tc_pos;

    s = suite_create("extend_matrix");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_add_one_row_one_col);
    tcase_add_test(tc_pos, test_matrices_with_same_sizes);
    suite_add_tcase(s, tc_pos);
    return s;
}
