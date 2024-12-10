#include "check_find.h"
#include "associative_array.h"
#include <stdlib.h>

START_TEST(test_correct_find)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 21);
    assoc_array_insert(assoc_array, "privet", 32);

    int result = 21;

    int *finded_num;
    int rc = assoc_array_find(assoc_array, "hi", &finded_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    ck_assert_int_eq(result, *finded_num);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_find_at_null_arr)
{
    assoc_array_t assoc_array = NULL;
    int *finded_num;
    int rc = assoc_array_find(assoc_array, "hi", &finded_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_find_empty_key)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 21);
    assoc_array_insert(assoc_array, "privet", 32);

    int *finded_num;
    int rc = assoc_array_find(assoc_array, "\0", &finded_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_not_found_key)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 21);
    assoc_array_insert(assoc_array, "privet", 32);

    int *finded_num;
    int rc = assoc_array_find(assoc_array, "salam", &finded_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&assoc_array);
}
END_TEST

Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("find");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_correct_find);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_find_at_null_arr);
    tcase_add_test(tc_neg, test_find_empty_key);
    tcase_add_test(tc_neg, test_not_found_key);
    suite_add_tcase(s, tc_neg);

    return s;
}