#include "check_matrix_determinant.h"
#include "dynamic_matrix.h"
#include <stdlib.h>

START_TEST(test_matrix_with_one_elem)
{
    matrix_t matrix_a = { .rows = 1, .cols = 1 };

    matrix_alloc(&matrix_a);
    double data_a[][1] = {{ 4 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    double result = 4.0;

    double cur_res;
    int rc = matrix_determinant(&matrix_a, matrix_a.rows, &cur_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_double_eq_tol(cur_res, result, 0.000001);
    matrix_free(&matrix_a);
}
END_TEST

START_TEST(test_matrix_with_size_two)
{
    matrix_t matrix_a = { .rows = 2, .cols = 2 };

    matrix_alloc(&matrix_a);
    double data_a[][2] = {{ 1, 2 }, { 3, 4 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    double result = -2.0;

    double cur_res;
    int rc = matrix_determinant(&matrix_a, matrix_a.rows, &cur_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_double_eq_tol(cur_res, result, 0.000001);
    matrix_free(&matrix_a);
}
END_TEST

START_TEST(test_matrix_with_size_four)
{
    matrix_t matrix_a = { .rows = 4, .cols = 4 };

    matrix_alloc(&matrix_a);
    double data_a[][4] = {{ 1, 0, 2, -1 }, { 2, 3, 3, 1 }, { 4, 2, 3, 1 }, { 1, 3, 4, 3 }};

    for (size_t i = 0; i < matrix_a.rows; i++)
        for (size_t j = 0; j < matrix_a.cols; j++)
            matrix_a.data[i][j] = data_a[i][j];

    double result = -40.0;

    double cur_res;
    int rc = matrix_determinant(&matrix_a, matrix_a.rows, &cur_res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_double_eq_tol(cur_res, result, 0.000001);
    matrix_free(&matrix_a);
}
END_TEST

Suite *matrix_determinant_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_determinant");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_with_one_elem);
    tcase_add_test(tc_pos, test_matrix_with_size_two);
    tcase_add_test(tc_pos, test_matrix_with_size_four);
    suite_add_tcase(s, tc_pos);
    return s;
}
