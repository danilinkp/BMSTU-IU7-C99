#include <stdlib.h>
#include "check_key.h"
#include "dynamic_array.h"

// positives
START_TEST(test_arr_without_negatives)
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;
    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(n, filtered_arr_pe - filtered_arr_pb);

    int *pi = filtered_arr_pb;
    for (size_t i = 0; pi < filtered_arr_pe; pi++, i++)
        ck_assert_int_eq(*pi, result[i]);
    free(filtered_arr_pb);
}
END_TEST


START_TEST(test_arr_with_one_negative)
{
    int arr[] = {0, 1, 2, 3, -4, 5, 6, 7, 8};
    int result[] = {0, 1, 2, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t result_n = sizeof (result) / sizeof(result[0]);
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;
    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(result_n, filtered_arr_pe - filtered_arr_pb);

    int *pi = filtered_arr_pb;
    for (size_t i = 0; pi < filtered_arr_pe; pi++, i++)
        ck_assert_int_eq(*pi, result[i]);
    free(filtered_arr_pb);
}
END_TEST

START_TEST(test_arr_with_negatives)
{
    int arr[] = {0, 1, 2, -3, -4, -5, 6, -7, 8};
    int result[] = {0, 1, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t result_n = sizeof (result) / sizeof(result[0]);
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;
    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(result_n, filtered_arr_pe - filtered_arr_pb);

    int *pi = filtered_arr_pb;
    for (size_t i = 0; pi < filtered_arr_pe; pi++, i++)
        ck_assert_int_eq(*pi, result[i]);
    free(filtered_arr_pb);
}
END_TEST

START_TEST(test_arr_with_one_positive)
{
    int arr[] = {1 };
    int result[] = {1 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;
    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(n, filtered_arr_pe - filtered_arr_pb);

    int *pi = filtered_arr_pb;
    for (size_t i = 0; pi < filtered_arr_pe; pi++, i++)
        ck_assert_int_eq(*pi, result[i]);
    free(filtered_arr_pb);
}
END_TEST


//negatives
START_TEST(test_empty_arr)
{
    size_t n = 0;
    int *arr = calloc(n, sizeof (int));
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;

    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, DATA_ARRAY_ERROR);
    free(arr);
}
END_TEST

START_TEST(test_arr_with_first_negative_elem)
{
    int arr[] = {-1, 23, 3, 12, 312, 123, 1675 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;

    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, DATA_ARRAY_ERROR);
}
END_TEST

START_TEST(test_arr_with_one_negative_elem)
{
    int arr[] = {-1 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = count_pos_elems(arr, arr + n);
    int *filtered_arr_pb = malloc(new_size * sizeof(int));
    int *filtered_arr_pe = filtered_arr_pb + new_size;

    int rc = key(arr, arr + n, &filtered_arr_pb, &filtered_arr_pe);
    ck_assert_int_eq(rc, DATA_ARRAY_ERROR);
}
END_TEST


Suite *key_suite(void)
{
    Suite * s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("key");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_arr_without_negatives);
    tcase_add_test(tc_pos, test_arr_with_one_negative);
    tcase_add_test(tc_pos, test_arr_with_negatives);
    tcase_add_test(tc_pos, test_arr_with_one_positive);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_empty_arr);
    tcase_add_test(tc_neg, test_arr_with_first_negative_elem);
    tcase_add_test(tc_neg, test_arr_with_one_negative_elem);
    suite_add_tcase(s, tc_neg);

    return s;
}