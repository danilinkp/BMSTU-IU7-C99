#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACTION_LEN 10

#define WRONG_ACTION_ERROR 5
#define EMPTY_INPUT_ERROR 6
#define MATRIX_SIZES_ERROR 7

int main(void)
{
    char action[MAX_ACTION_LEN];
    if (fgets(action, MAX_ACTION_LEN, stdin) == NULL)
        return EMPTY_INPUT_ERROR;
    action[strcspn(action, "\n")] = '\0';
    if (strcmp("out", action) == 0 || strcmp("lin", action) == 0)
    {
        matrix_t matrix = { .head = NULL };
        int rc = read_matrix(&matrix);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(&matrix);
            return rc;
        }
        if (strcmp("lin", action) == 0)
        {
            rc = matrix_lin(&matrix);
            if (rc != EXIT_SUCCESS)
            {
                free_matrix(&matrix);
                return rc;
            }
        }
        print_matrix(&matrix);
        free_matrix(&matrix);
    }
    else if (strcmp("add", action) == 0 || strcmp("mul", action) == 0)
    {
        matrix_t matrix_1 = { .head = NULL };
        int rc = read_matrix(&matrix_1);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(&matrix_1);
            return rc;
        }
        matrix_t matrix_2 = { .head = NULL };
        rc = read_matrix(&matrix_2);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(&matrix_1);
            free_matrix(&matrix_2);
            return rc;
        }
        matrix_t result = { .head = NULL };

        if (strcmp("add", action) == 0)
            rc = matrix_add(&matrix_1, &matrix_2, &result);
        else
            rc = matrix_mul(&matrix_1, &matrix_2, &result);

        if (rc != EXIT_SUCCESS)
        {
            free_matrix(&matrix_1);
            free_matrix(&matrix_2);
            free_matrix(&result);
            return MATRIX_SIZES_ERROR;
        }
        print_matrix(&result);
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);
        free_matrix(&result);
    }
    else
        return WRONG_ACTION_ERROR;
    return EXIT_SUCCESS;
}
