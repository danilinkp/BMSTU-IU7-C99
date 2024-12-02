#ifndef LAB6_ITEM_H
#define LAB6_ITEM_H

#include <stdlib.h>

#define MAX_PRODUCT_NAME_LEN 25
#define MAX_NUM_OF_PRODUCTS 15

typedef struct
{
    char name[MAX_PRODUCT_NAME_LEN + 1];
    int price;
} product_t;

int read_products_to_array(char *filename, size_t *num_of_products, product_t products[]);
void print_products(size_t num_of_products, double price, product_t products[]);
int str_to_double(char *str_price, double *price);

#endif //LAB6_ITEM_H
