#include "check_clear.h"
#include "associative_array.h"
#include <stdlib.h>

START_TEST(test_clear_arr_with_one_elem)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);

    int rc = assoc_array_clear(assoc_array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_clear_arr_with_few_elems)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 22);
    assoc_array_insert(assoc_array, "privet", 32);
    assoc_array_insert(assoc_array, "salam", 42);

    int rc = assoc_array_clear(assoc_array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_clear_empty_arr)
{
    assoc_array_t assoc_array = assoc_array_create();

    int rc = assoc_array_clear(assoc_array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_clear_null_arr)
{
    assoc_array_t assoc_array = NULL;

    int rc = assoc_array_clear(assoc_array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *clear_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("clear");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_clear_arr_with_few_elems);
    tcase_add_test(tc_pos, test_clear_arr_with_one_elem);
    tcase_add_test(tc_pos, test_clear_empty_arr);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_clear_null_arr);
    suite_add_tcase(s, tc_neg);

    return s;
}
