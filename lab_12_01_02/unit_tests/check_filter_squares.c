#include "check_filter_squares.h"
#include "array.h"

START_TEST(test_no_squares)
{
    int src[] = { 2, 3, 5, 7, 10, 11 };
    int dst[10];
    int dst_len = 10;

    int rc = filter_squares(src, 6, dst, &dst_len);

    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 0);
}
END_TEST

START_TEST(test_some_squares)
{
    int src[] = { 2, 4, 5, 9, 10, 11 };
    int dst[10];
    int dst_len = 10;
    int res[] = { 4, 9 };
    int res_len = sizeof(res) / sizeof(res[0]);

    int rc = filter_squares(src, 6, dst, &dst_len);

    for (int i = 0; i < dst_len; i++)
        ck_assert_int_eq(res[i], dst[i]);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, res_len);
}
END_TEST

START_TEST(test_all_squares)
{
    int src[] = { 16, 4, 25, 9, 100, 36 };
    int dst[10];
    int dst_len = 10;
    int res[] = { 16, 4, 25, 9, 100, 36 };
    int res_len = sizeof(res) / sizeof(res[0]);

    int rc = filter_squares(src, 6, dst, &dst_len);

    for (int i = 0; i < dst_len; i++)
        ck_assert_int_eq(res[i], dst[i]);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, res_len);
}
END_TEST

START_TEST(test_with_negatives)
{
    int src[] = { -6, 4, -25, 9, -100, 36 };
    int dst[10];
    int dst_len = 10;
    int res[] = { 4, 9, 36 };
    int res_len = sizeof(res) / sizeof(res[0]);

    int rc = filter_squares(src, 6, dst, &dst_len);

    for (int i = 0; i < dst_len; i++)
        ck_assert_int_eq(res[i], dst[i]);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, res_len);
}
END_TEST

START_TEST(test_small_dst_len)
{
    int src[] = { 6, 4, -15, 9, -120, 36 };
    int dst[10];
    int dst_len = 0;

    int rc = filter_squares(src, 6, dst, &dst_len);

    ck_assert_int_eq(rc, 1);
    ck_assert_int_eq(dst_len, 3);
}

Suite *filter_square_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("filter_square");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_no_squares);
    tcase_add_test(tc_pos, test_all_squares);
    tcase_add_test(tc_pos, test_with_negatives);
    tcase_add_test(tc_pos, test_some_squares);
    tcase_add_test(tc_pos, test_small_dst_len);
    suite_add_tcase(s, tc_pos);
    return s;
}