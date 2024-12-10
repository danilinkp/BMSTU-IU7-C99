#include "products.h"
#include <stdio.h>

void products_free(products_t *products)
{
    for (size_t i = 0; i < products->size; i++)
        product_free(products->products[i]);
    free(products->products);
}

int products_alloc(products_t *products)
{
    products->products = malloc(products->size * sizeof(product_t *));
    if (!products->products)
        return PRODUCTS_ALLOC_ERR;
    return EXIT_SUCCESS;
}

int read_products_num(FILE *file, products_t *products)
{
    if (fscanf(file, "%zu\n", &products->size) != 1 || (int) products->size <= 0)
        return FILE_READ_ERR;
    return EXIT_SUCCESS;
}

int read_products(FILE *file, products_t *products)
{
    product_t *product = NULL;
    size_t products_read_len = 0;
    for (size_t i = 0; i < products->size; i++)
    {
        int rc = product_read(file, &product);
        if (rc != EXIT_SUCCESS)
        {
            products->size = products_read_len;
            return FILE_READ_ERR;
        }
        products->products[i] = product;
        products_read_len++;
        product = NULL;
    }
    products->size = products_read_len;
    return EXIT_SUCCESS;
}

void print_products(double price, const products_t *products)
{
    for (size_t i = 0; i < products->size; i++)
    {
        if (products->products[i]->price < price)
            printf("%s\n%d\n", products->products[i]->name, products->products[i]->price);
    }
}

int str_to_double(char *str_price, double *price)
{
    char *endptr;
    *price = strtod(str_price, &endptr);
    if (*endptr != '\0')
        return NOT_NUMBER_ERR;
    return EXIT_SUCCESS;
}
