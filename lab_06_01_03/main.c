#include <stdlib.h>
#include <stdio.h>
#include "product.h"

#define WRONG_ARGS_ERR 6

int main(int argc, char **argv)
{
    if (argc != 3)
        return WRONG_ARGS_ERR;
    int rc = EXIT_SUCCESS;
    double price;
    rc = str_to_double(argv[2], &price);
    if (rc != EXIT_SUCCESS)
        return rc;
    if (price <= 0)
        return WRONG_ARGS_ERR;

    product_t products[MAX_NUM_OF_PRODUCTS];
    size_t num_of_products;

    rc = read_products_to_array(argv[1], &num_of_products, products);
    if (rc != EXIT_SUCCESS)
        return rc;
    print_products(num_of_products, price, products);
    return rc;
}