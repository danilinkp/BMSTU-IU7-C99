#include "check_max.h"
#include "associative_array.h"
#include <stdlib.h>

START_TEST(test_max_arr_with_one_elem)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);

    int result = 12;
    int *max;
    int rc = assoc_array_max(assoc_array, &max);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    ck_assert_int_eq(result, *max);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_max_arr_with_few_elems)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 22);
    assoc_array_insert(assoc_array, "aello", 12);
    assoc_array_insert(assoc_array, "bello", 32);
    assoc_array_insert(assoc_array, "gello", 42);

    int result = 22;
    int *max;
    int rc = assoc_array_max(assoc_array, &max);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    ck_assert_int_eq(result, *max);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_max_of_empty_arr)
{
    assoc_array_t assoc_array = assoc_array_create();
    int *max;
    int rc = assoc_array_max(assoc_array, &max);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&assoc_array);
}

START_TEST(test_max_of_null_arr)
{
    assoc_array_t assoc_array = NULL;
    int *max;
    int rc = assoc_array_max(assoc_array, &max);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

Suite *max_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("max");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_max_arr_with_one_elem);
    tcase_add_test(tc_pos, test_max_arr_with_few_elems);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_max_of_null_arr);
    tcase_add_test(tc_neg, test_max_of_empty_arr);
    suite_add_tcase(s, tc_neg);

    return s;
}