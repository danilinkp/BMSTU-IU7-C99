#include "check_my_snprintf.h"
#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

START_TEST(test_d)
{
    char buf[15];
    char result[15];

    int my_rc = my_snprintf(buf, sizeof(buf), "%d + %d = %d", 2, 2, 4);
    int rc = snprintf(result, sizeof(result), "%d + %d = %d", 2, 2, 4);

    ck_assert_int_eq(my_rc, rc);
    ck_assert_str_eq(buf, result);
}
END_TEST

START_TEST(test_ld)
{
    char buf[100];
    char result[100];

    int my_rc = my_snprintf(buf, sizeof(buf), "Very large num %ld", LONG_MIN);
    int rc = snprintf(result, sizeof(result), "Very large num %ld", LONG_MIN);

    ck_assert_int_eq(my_rc, rc);
    ck_assert_str_eq(buf, result);
}
END_TEST

START_TEST(test_o)
{
    char buf[25];
    char result[25];

    int my_rc = my_snprintf(buf, sizeof(buf), "Oct num - %o", 256);
    int rc = snprintf(result, sizeof(result), "Oct num - %o", 256);

    ck_assert_int_eq(my_rc, rc);
    ck_assert_str_eq(buf, result);
}
END_TEST

START_TEST(test_negative_elem)
{
    char buf[25];
    char result[25];

    int my_rc = my_snprintf(buf, sizeof(buf), "%d - %d = %d", 0, 52412, -52412);
    int rc = snprintf(result, sizeof(result), "%d - %d = %d", 0, 52412, -52412);

    ck_assert_int_eq(my_rc, rc);
    ck_assert_str_eq(buf, result);
}

START_TEST(test_all_formats)
{
    char buf[100];
    char result[100];

    int my_rc = my_snprintf(buf, sizeof(buf), "Dec num - %d, long num - %ld, oct num - %o", 2018, 99999999999999, 256);
    int rc = snprintf(result, sizeof(result), "Dec num - %d, long num - %ld, oct num - %o", 2018, 99999999999999, 256);

    ck_assert_int_eq(my_rc, rc);
    ck_assert_str_eq(buf, result);
}
END_TEST

START_TEST(test_zero_len)
{
    char buf[20];
    char result[20];

    int my_rc = my_snprintf(buf, 0, "%d + %d = %d", 2, 2, 4);
    int rc = snprintf(result, 0, "%d + %d = %d", 2, 2, 4);

    ck_assert_int_eq(my_rc, rc);
}
END_TEST

START_TEST(test_without_specifiers)
{
    char buf[35];
    char result[35];

    int my_rc = my_snprintf(buf, sizeof(buf), "Test without spec");
    int rc = snprintf(result, sizeof(result), "Test without spec");

    ck_assert_int_eq(my_rc, rc);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_tests;

    s = suite_create("my_snprintf");

    tc_tests = tcase_create("tests");
    tcase_add_test(tc_tests, test_d);
    tcase_add_test(tc_tests, test_ld);
    tcase_add_test(tc_tests, test_o);
    tcase_add_test(tc_tests, test_negative_elem);
    tcase_add_test(tc_tests, test_all_formats);
    tcase_add_test(tc_tests, test_zero_len);
    tcase_add_test(tc_tests, test_without_specifiers);
    suite_add_tcase(s, tc_tests);
    return s;
}
