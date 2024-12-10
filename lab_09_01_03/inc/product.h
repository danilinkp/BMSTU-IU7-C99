#ifndef LAB9_PRODUCT_H
#define LAB9_PRODUCT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char *name;
    int price;
} product_t;

enum errors
{
    PRODUCT_ALLOC_ERR = 4,
    PRODUCT_NAME_READ_ERR,
    PRICE_READ_ERR
};

void product_free(product_t *product);

int product_create(product_t **product, char *name, int price);

int product_read(FILE *file, product_t **product);

#endif //LAB9_PRODUCT_H
