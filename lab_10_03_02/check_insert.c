#include "check_insert.h"
#include "associative_array.h"
#include <stdlib.h>

START_TEST(test_insert_at_empty_arr)
{
    assoc_array_t assoc_array = assoc_array_create();
    int rc = assoc_array_insert(assoc_array, "hello", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_insert_few_elems)
{
    assoc_array_t assoc_array = assoc_array_create();
    int rc = assoc_array_insert(assoc_array, "hello", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_insert(assoc_array, "hello2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_insert(assoc_array, "hello3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_insert_empty_key)
{
    assoc_array_t assoc_array = assoc_array_create();
    int rc = assoc_array_insert(assoc_array, "\0", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_insert_exist_key)
{
    assoc_array_t assoc_array = assoc_array_create();
    int rc = assoc_array_insert(assoc_array, "abcd", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_insert(assoc_array, "abcd", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_insert_at_null_arr)
{
    assoc_array_t assoc_array = NULL;
    int rc = assoc_array_insert(assoc_array, "qwerty", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *insert_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("insert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_insert_at_empty_arr);
    tcase_add_test(tc_pos, test_insert_few_elems);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_insert_at_null_arr);
    tcase_add_test(tc_neg, test_insert_empty_key);
    tcase_add_test(tc_neg, test_insert_exist_key);
    suite_add_tcase(s, tc_neg);

    return s;
}