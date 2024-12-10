#include "check_read_products.h"
#include "products.h"
#include <stdio.h>
#include <stdlib.h>

// positives
START_TEST(test_read_five_products)
{
    int rc;
    products_t products;

    FILE *file = fopen("func_tests/data/pos_01_in.txt", "r");
    rc = read_products_num(file, &products);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    products_alloc(&products);

    rc = read_products(file, &products);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    fclose(file);
    products_free(&products);
}
END_TEST


//negatives
START_TEST(test_wrong_price)
{
    int rc;
    products_t products;

    FILE *file = fopen("func_tests/data/neg_02_in.txt", "r");
    rc = read_products_num(file, &products);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    products_alloc(&products);

    rc = read_products(file, &products);
    ck_assert_int_eq(rc, FILE_READ_ERR);

    fclose(file);
    products_free(&products);
}
END_TEST

START_TEST(test_read_wrong_size)
{
    int rc;
    products_t products;

    FILE *file = fopen("func_tests/data/neg_03_in.txt", "r");
    rc = read_products_num(file, &products);

    fclose(file);
    ck_assert_int_eq(rc, FILE_READ_ERR);
}
END_TEST


Suite *read_products_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("read_products");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_read_five_products);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_wrong_price);
    tcase_add_test(tc_neg, test_read_wrong_size);
    suite_add_tcase(s, tc_neg);

    return s;
}
