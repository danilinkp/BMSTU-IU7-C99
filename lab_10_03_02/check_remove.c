#include "check_remove.h"
#include "associative_array.h"
#include <stdlib.h>

START_TEST(test_remove_arr_with_one_elem)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);

    int rc = assoc_array_remove(assoc_array, "hello");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_remove_arr_with_few_elems)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 22);
    assoc_array_insert(assoc_array, "privet", 32);
    assoc_array_insert(assoc_array, "salam", 42);

    int rc = assoc_array_remove(assoc_array, "privet");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}

START_TEST(test_remove_non_exist_elem)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 22);
    assoc_array_insert(assoc_array, "privet", 32);
    assoc_array_insert(assoc_array, "salam", 42);

    int rc = assoc_array_remove(assoc_array, "bonjour");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&assoc_array);
}

START_TEST(test_remove_at_null_arr)
{
    assoc_array_t assoc_array = NULL;
    int rc = assoc_array_remove(assoc_array, "hi");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_remove_empty_key)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 21);
    assoc_array_insert(assoc_array, "privet", 32);


    int rc = assoc_array_remove(assoc_array, "\0");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&assoc_array);
}
END_TEST

Suite *remove_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("remove");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_remove_arr_with_one_elem);
    tcase_add_test(tc_pos, test_remove_arr_with_few_elems);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_remove_at_null_arr);
    tcase_add_test(tc_neg, test_remove_empty_key);
    tcase_add_test(tc_neg, test_remove_non_exist_elem);
    suite_add_tcase(s, tc_neg);

    return s;
}