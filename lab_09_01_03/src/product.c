#include "product.h"
#include <stdlib.h>
#include <string.h>

void product_free(product_t *product)
{
    if (strlen(product->name) != 0)
        free(product->name);
    free(product);
}

int product_create(product_t **product, char *name, int price)
{
    *product = malloc(sizeof(product_t));
    if (!(*product))
        return PRODUCT_ALLOC_ERR;
    (*product)->name = name;
    (*product)->price = price;

    return EXIT_SUCCESS;
}

static int name_read(FILE *file, char **name)
{
    size_t len = 0;
    char *line = NULL;
    ssize_t read;

    read = getline(&line, &len, file);
    if (read == -1)
    {
        free(line);
        return PRODUCT_NAME_READ_ERR;
    }
    if (len == 0)
    {
        free(line);
        return PRODUCT_NAME_READ_ERR;
    }

    line[strcspn(line, "\n")] = '\0';
    *name = line;

    return EXIT_SUCCESS;
}

int product_read(FILE *file, product_t **product)
{
    char *name = NULL;

    int rc = name_read(file, &name);
    if (rc != EXIT_SUCCESS)
        return rc;

    int price;
    if (fscanf(file, "%d\n", &price) != 1 || price <= 0)
    {
        free(name);
        return PRICE_READ_ERR;
    }

    rc = product_create(product, name, price);
    if (rc != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}


