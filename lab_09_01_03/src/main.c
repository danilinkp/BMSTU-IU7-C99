#include <stdlib.h>
#include <stdio.h>
#include "products.h"

#define WRONG_ARGS_ERR 7
#define FILE_OPEN_ERR 8

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

    FILE *file = fopen(argv[1], "rt");
    if (file == NULL)
        return FILE_OPEN_ERR;

    products_t products;

    rc = read_products_num(file, &products);
    if (rc != EXIT_SUCCESS)
    {
        fclose(file);
        return rc;
    }

    rc = products_alloc(&products);
    if (rc != EXIT_SUCCESS)
    {
        fclose(file);
        return rc;
    }


    rc = read_products(file, &products);
    if (rc != EXIT_SUCCESS)
    {
        fclose(file);
        products_free(&products);
        return rc;
    }

    print_products(price, &products);
    fclose(file);
    products_free(&products);

    return rc;
}
