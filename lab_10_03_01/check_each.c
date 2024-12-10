#include "check_each.h"
#include "associative_array.h"
#include <stdlib.h>

void action(const char *key, int *num, void *param)
{
    *num += strlen(key) % *(int *) param;
}

START_TEST(test_each_few_elems)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);
    assoc_array_insert(assoc_array, "hi", 22);
    assoc_array_insert(assoc_array, "privet", 32);
    assoc_array_insert(assoc_array, "salam", 42);

    int param = 2;
    int rc = assoc_array_each(assoc_array, action, &param);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_each_one_elem)
{
    assoc_array_t assoc_array = assoc_array_create();
    assoc_array_insert(assoc_array, "hello", 12);

    int param = 2;
    int rc = assoc_array_each(assoc_array, action, &param);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&assoc_array);
}
END_TEST

START_TEST(test_each_null_arr)
{
    assoc_array_t assoc_array = NULL;

    int rc = assoc_array_clear(assoc_array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *each_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("each");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_each_few_elems);
    tcase_add_test(tc_pos, test_each_one_elem);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_each_null_arr);
    suite_add_tcase(s, tc_neg);

    return s;
}