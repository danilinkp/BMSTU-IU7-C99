#include "../inc/set.h"
#include <stdio.h>

int main(void)
{
    int rc;
    set_t a, b, result;
    rc = (input_set(&a, NMAX));
    if (rc != EXIT_SUCCESS)
    {
        printf("Ошибка ввода массива.\n");
        return rc;
    }

    rc = (input_set(&b, NMAX));
    if (rc != EXIT_SUCCESS)
    {
        printf("Ошибка ввода массива.\n");
        return rc;
    }

    if (is_duplicate_elem_in_set(&a))
    {
        rc = del_duplicates(&a);
        if (rc != EXIT_SUCCESS)
        {
            printf("Ошибка удаления дубликатов.\n");
            return rc;
        }
    }

    if (is_duplicate_elem_in_set(&b))
    {
        rc = del_duplicates(&b);
        if (rc != EXIT_SUCCESS)
        {
            printf("Ошибка удаления дубликатов.\n");
            return rc;
        }
    }

    rc = set_intersection(&a, &b, &result);
    if (rc != EXIT_SUCCESS)
    {
        return rc;
        printf("Ошибка умножения.\n");
    }

    print_set(result);
    set_free(&a);
    set_free(&b);
    set_free(&result);

    return EXIT_SUCCESS;
}