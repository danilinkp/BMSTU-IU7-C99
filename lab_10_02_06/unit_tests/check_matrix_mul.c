#include "check_matrix_mul.h"
#include "matrix.h"
#include <stdlib.h>

START_TEST(test_one_matrix_empty)
{
    matrix_t matrix_1 = { .head = NULL };
    matrix_1.cols = 2;
    matrix_1.rows = 2;

    matrix_t matrix_2 = { .head = NULL };
    matrix_2.cols = 1;
    matrix_2.rows = 1;
    matrix_elem_add(&matrix_2, 4, 0, 0);

    matrix_t multiplication = { .head = NULL };

    int rc = matrix_mul(&matrix_1, &matrix_2, &multiplication);
    ck_assert_int_eq(rc, MATRIX_EMPTY_ERROR);

    free_matrix(&matrix_2);
}
END_TEST

START_TEST(test_mul_empty_matrices)
{
    matrix_t matrix_1 = { .head = NULL };
    matrix_1.cols = 2;
    matrix_1.rows = 2;

    matrix_t matrix_2 = { .head = NULL };
    matrix_2.cols = 1;
    matrix_2.rows = 1;

    matrix_t result = { .head = NULL };

    int rc = matrix_mul(&matrix_1, &matrix_2, &result);

    ck_assert_int_eq(rc, MATRIX_EMPTY_ERROR);
}
END_TEST

START_TEST(test_correct_mul)
{
    matrix_t matrix_1 = { .head = NULL };
    matrix_1.cols = 2;
    matrix_1.rows = 2;
    int elems_1[2][2] = {{ 1, 0 }, { 3, -2 }};

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            if (elems_1[i][j] != 0)
                matrix_elem_add(&matrix_1, elems_1[i][j], i, j);

    matrix_t matrix_2 = { .head = NULL };
    matrix_2.cols = 3;
    matrix_2.rows = 3;
    int elems_2[3][3] = {{1, 0, 1}, {0, 0, 0}, {0, 0, 5}};
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (elems_2[i][j] != 0)
                matrix_elem_add(&matrix_2, elems_2[i][j], i, j);

    matrix_t result = { .head = NULL };
    int res_elems[3][3] = { {1, 0, 1}, {3, 0, 3}, {0, 0, 0}};
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (res_elems[i][j] != 0)
                matrix_elem_add(&result, res_elems[i][j], i, j);

    matrix_t mul = {.head = NULL};

    int rc = matrix_mul(&matrix_1, &matrix_2, &mul);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    node_t *res_elem = result.head;
    node_t *mul_elem = mul.head;

    while (res_elem && mul_elem)
    {
        ck_assert_int_eq(res_elem->data, mul_elem->data);
        res_elem = res_elem->next;
        mul_elem = mul_elem->next;
    }

    free_matrix(&matrix_1);
    free_matrix(&matrix_2);
    free_matrix(&result);
    free_matrix(&mul);
}
END_TEST

Suite *matrix_mul_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_mul");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_correct_mul);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_mul_empty_matrices);
    tcase_add_test(tc_neg, test_one_matrix_empty);
    suite_add_tcase(s, tc_neg);

    return s;
}
