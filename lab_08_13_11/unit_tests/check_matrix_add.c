#include "check_matrix_add.h"
#include "dynamic_matrix.h"
#include <stdlib.h>

START_TEST(test_two_usual_matrices)
{
    matrix_t matrix_a = { .rows = 2, .cols = 2 };

    matrix_alloc(&matrix_a);
    double data_a[][2] = {{ 4, 1 },
                          { 3, 7 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    matrix_t matrix_b = { .rows = 2, .cols = 2 };
    matrix_alloc(&matrix_b);

    double data_b[][2] = {{ 2, 5 },
                          { 3, 12 }};

    for (size_t i = 0; i < matrix_b.rows; i++)
        for (size_t j = 0; j < matrix_b.cols; j++)
            matrix_b.data[i][j] = data_b[i][j];

    double result[][2] = {{ 6.0, 6.0 },
                          { 6.0, 19.0 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    matrix_t matrix_res = { .rows = 2, .cols = 2 };

    int rc = matrix_add(&matrix_a, &matrix_b, &matrix_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix_res.rows, result_rows);
    ck_assert_int_eq(matrix_res.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_double_eq_tol(matrix_res.data[i][j], result[i][j], 0.000001);

    matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    matrix_free(&matrix_res);
}
END_TEST

START_TEST(test_one_elem_matrices)
{
    matrix_t matrix_a = { .rows = 1, .cols = 1 };

    matrix_alloc(&matrix_a);
    double data_a[][1] = {{ 4 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    matrix_t matrix_b = { .rows = 1, .cols = 1 };
    matrix_alloc(&matrix_b);

    double data_b[][1] = {{ 2 }};

    for (size_t i = 0; i < matrix_b.rows; i++)
        for (size_t j = 0; j < matrix_b.cols; j++)
            matrix_b.data[i][j] = data_b[i][j];

    double result[][1] = {{ 6.0 }};

    size_t result_rows = sizeof(result) / sizeof(result[0]);
    size_t result_cols = sizeof(result[0]) / sizeof(result[0][0]);

    matrix_t matrix_res = { .rows = 2, .cols = 2 };

    int rc = matrix_add(&matrix_a, &matrix_b, &matrix_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    ck_assert_int_eq(matrix_res.rows, result_rows);
    ck_assert_int_eq(matrix_res.cols, result_cols);

    for (size_t i = 0; i < result_rows; i++)
        for (size_t j = 0; j < result_cols; j++)
            ck_assert_double_eq_tol(matrix_res.data[i][j], result[i][j], 0.000001);

    matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    matrix_free(&matrix_res);
}
END_TEST


Suite *matrix_add_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_add");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_two_usual_matrices);
    tcase_add_test(tc_pos, test_one_elem_matrices);
    suite_add_tcase(s, tc_pos);
    return s;
}
