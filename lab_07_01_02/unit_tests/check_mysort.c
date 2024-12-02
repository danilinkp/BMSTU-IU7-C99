#include <stdlib.h>
#include "check_mysort.h"
#include "dynamic_array.h"


START_TEST(test_sorted_arr)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    mysort(arr, n, sizeof(int), my_comp_int);
    for (size_t i = 1; i < n; i++)
        ck_assert_int_le(arr[i - 1], arr[i]);
}
END_TEST

START_TEST(test_reversed_sorted_arr)
{
    int arr[] = {10, 10, 9, 7, 6, 5, 4, 3, 2, 1, -1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    mysort(arr, n, sizeof(int), my_comp_int);
    for (size_t i = 1; i < n; i++)
        ck_assert_int_le(arr[i - 1], arr[i]);
}

END_TEST

START_TEST(test_arr_with_same_elems)
{
    int arr[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    mysort(arr, n, sizeof(int), my_comp_int);
    for (size_t i = 1; i < n; i++)
        ck_assert_int_le(arr[i - 1], arr[i]);
}
END_TEST

START_TEST(test_arr_with_one_elem)
{
    int arr[] = {5};
    int res[] = {5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    mysort(arr, n, sizeof(int), my_comp_int);
    ck_assert_int_eq(sizeof(res) / sizeof(res[0]), n);
    for (size_t i = 0; i < n; i++)
        ck_assert_int_eq(res[i], arr[i]);
}
END_TEST

START_TEST(test_arr_with_random_order)
{
    int arr[] = {123, 23, 233, 43, 32, 42, 56, 78, 92, 2345};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    mysort(arr, n, sizeof(int), my_comp_int);
    for (size_t i = 1; i < n; i++)
        ck_assert_int_le(arr[i - 1], arr[i]);
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("my_sort");
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_sorted_arr);
    tcase_add_test(tc_pos, test_reversed_sorted_arr);
    tcase_add_test(tc_pos, test_arr_with_same_elems);
    tcase_add_test(tc_pos, test_arr_with_one_elem);
    tcase_add_test(tc_pos, test_arr_with_random_order);

    suite_add_tcase(s, tc_pos);
    return s;
}