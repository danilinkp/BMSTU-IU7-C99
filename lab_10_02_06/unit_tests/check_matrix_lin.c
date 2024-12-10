#include "check_matrix_lin.h"
#include "matrix.h"
#include <stdlib.h>

START_TEST(test_empty_matrix)
{
    matrix_t matrix = { .head = NULL };

    int rc = matrix_lin(&matrix);
    ck_assert_int_eq(rc, MATRIX_EMPTY_ERROR);
}
END_TEST

START_TEST(test_del_one_max_elem)
{
    matrix_t matrix = { .head = NULL };
    int elems[2][2] = {{ 1, 0 }, { 3, -2 }};

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            if (elems[i][j] != 0)
                matrix_elem_add(&matrix, elems[i][j], i, j);

    matrix_t result = { .head = NULL };
    int res_elems[1][2] = {{ 1, 0 }};

    for (size_t i = 0; i < 1; i++)
        for (size_t j = 0; j < 2; j++)
            if (res_elems[i][j] != 0)
                matrix_elem_add(&result, res_elems[i][j], i, j);

    int rc = matrix_lin(&matrix);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    node_t *res_elem = result.head;
    node_t *elem = matrix.head;

    while (res_elem && elem)
    {
        ck_assert_int_eq(res_elem->data, elem->data);
        res_elem = res_elem->next;
        elem = elem->next;
    }
    free_matrix(&matrix);
    free_matrix(&result);
}
END_TEST

START_TEST(test_del_two_max_elems)
{
    matrix_t matrix = { .head = NULL };
    int elems[3][2] = {{ 1, 0 }, { 3, -2 }, {4, 3}};

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            if (elems[i][j] != 0)
                matrix_elem_add(&matrix, elems[i][j], i, j);

    matrix_t result = { .head = NULL };
    int res_elems[2][2] = {{ 1, 0 }, {4, 3}};

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            if (res_elems[i][j] != 0)
                matrix_elem_add(&result, res_elems[i][j], i, j);

    int rc = matrix_lin(&matrix);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    node_t *res_elem = result.head;
    node_t *elem = matrix.head;

    while (res_elem && elem)
    {
        ck_assert_int_eq(res_elem->data, elem->data);
        res_elem = res_elem->next;
        elem = elem->next;
    }
    free_matrix(&matrix);
    free_matrix(&result);
}
END_TEST


Suite *matrix_lin_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_lin");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_del_one_max_elem);
    tcase_add_test(tc_pos, test_del_two_max_elems);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_empty_matrix);
    suite_add_tcase(s, tc_neg);

    return s;
}
