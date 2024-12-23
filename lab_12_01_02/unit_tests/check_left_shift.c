#include "check_left_shift.h"
#include "array.h"
#include <stdlib.h>

START_TEST(test_shift_to_zero)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int res[] = { 1, 2, 3, 4, 5 };
    left_shift(arr, 5, 0);

    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST

START_TEST(test_shift_to_small_position)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int res[] = { 3, 4, 5, 1, 2 };
    left_shift(arr, 5, 2);

    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST

START_TEST(test_shift_to_position_longer_than_len)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int res[] = { 4, 5, 1, 2, 3 };
    left_shift(arr, 5, 13);

    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(arr[i], res[i]);
}

Suite *left_shift_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("shift_left");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_shift_to_zero);
    tcase_add_test(tc_pos, test_shift_to_small_position);
    tcase_add_test(tc_pos, test_shift_to_position_longer_than_len);
    suite_add_tcase(s, tc_pos);
    return s;
}