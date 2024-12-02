#include "check_make_square.h"
#include "dynamic_matrix.h"
#include <stdlib.h>

START_TEST(test_rows_more_than_cols)
{
    matrix_t matrix = { .rows = 5, .cols = 3 };
    matrix_alloc(&matrix);

    int data[][3] = {{ 0, 2, 9 },
                     { 1, 2, 2 },
                     { 3, 3, 3 },
                     { 8, 8, 2 },
                     { 1, 8, 3 }};

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = data[i][j];

    int result[][3] = {{ 1, 2, 2 },
                       { 3, 3, 3 },
                       { 1, 8, 3 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    int rc = make_matrix_square(&matrix);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix.rows, result_rows);
    ck_assert_int_eq(matrix.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix.data[i][j], result[i][j]);

    matrix_free(&matrix);
}
END_TEST

START_TEST(test_cols_more_than_rows)
{
    matrix_t matrix = { .rows = 2, .cols = 3 };
    matrix_alloc(&matrix);

    int data[][3] = {{ 4, 7, 1 },
                     { 3, 2, 7 }};

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = data[i][j];

    int result[][2] = {{ 4, 1 },
                       { 3, 7 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    int rc = make_matrix_square(&matrix);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix.rows, result_rows);
    ck_assert_int_eq(matrix.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix.data[i][j], result[i][j]);

    matrix_free(&matrix);
}
END_TEST

START_TEST(test_square_matrix)
{
    matrix_t matrix = { .rows = 3, .cols = 3 };
    matrix_alloc(&matrix);

    int data[][3] = {{ 4, 7, 1 },
                     { 3, 2, 7 },
                     { 5, 8, 2 }};

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = data[i][j];

    int result[][3] = {{ 4, 7, 1 },
                       { 3, 2, 7 },
                       { 5, 8, 2 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    int rc = make_matrix_square(&matrix);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix.rows, result_rows);
    ck_assert_int_eq(matrix.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_int_eq(matrix.data[i][j], result[i][j]);

    matrix_free(&matrix);
}

Suite *make_square_suite(void)
{
    Suite * s;
    TCase *tc_pos;

    s = suite_create("make_square");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_rows_more_than_cols);
    tcase_add_test(tc_pos, test_cols_more_than_rows);
    tcase_add_test(tc_pos, test_square_matrix);
    suite_add_tcase(s, tc_pos);
    return s;
}
