#ifndef LAB9_PRODUCTS_H
#define LAB9_PRODUCTS_H

#include "product.h"

typedef struct
{
    product_t **products;
    size_t size;
} products_t;

enum products_errors
{
    FILE_READ_ERR = 1,
    NOT_NUMBER_ERR,
    PRODUCTS_ALLOC_ERR
};

void products_free(products_t *products);

int products_alloc(products_t *products);

int read_products_num(FILE *file, products_t *products);

int read_products(FILE *file, products_t *products);

void print_products(double price, const products_t *products);

int str_to_double(char *str_price, double *price);

#endif //LAB9_PRODUCTS_H
