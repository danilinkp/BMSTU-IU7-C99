#include "product.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_OPEN_ERR 1
#define FILE_READ_ERR 2
#define NAME_LEN_ERR 3
#define PRICE_ERR 4
#define NOT_NUMBER_ERR 5

int read_products_to_array(char *filename, size_t *num_of_products, product_t products[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return FILE_OPEN_ERR;
    if (fscanf(file, "%zu", num_of_products) != 1 || *num_of_products > MAX_NUM_OF_PRODUCTS)
        return FILE_READ_ERR;
    for (size_t i = 0; i < *num_of_products; i++)
    {
        if (fscanf(file, "%s %d", products[i].name, &products[i].price) == 2)
        {
            if (strlen(products[i].name) > MAX_PRODUCT_NAME_LEN)
                return NAME_LEN_ERR;
            if (products[i].price <= 0)
                return PRICE_ERR;
        }
        else
            return FILE_READ_ERR;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

void print_products(size_t num_of_products, double price, product_t products[])
{
    for (size_t i = 0; i < num_of_products; i++)
        if (products[i].price < price)
            printf("%s\n%d\n", products[i].name, products[i].price);
}

int str_to_double(char *str_price, double *price)
{
    char *endptr;
    *price = strtod(str_price, &endptr);
    if (*endptr != '\0')
        return NOT_NUMBER_ERR;
    return EXIT_SUCCESS;
}
