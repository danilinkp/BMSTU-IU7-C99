#include "dynamic_matrix.h"
#include <string.h>

enum
{
    ARGS_NUM_ERROR = 8,
    ARGS_ELEM_ERROR,
    FILE_OPEN_ERROR,
} errors;

int main(int argc, char **argv)
{
    if (argc < 4 || argc > 5)
        return ARGS_NUM_ERROR;

    if (strcmp(argv[1], "a") != 0 && strcmp(argv[1], "m") != 0 && strcmp(argv[1], "o") != 0)
        return ARGS_ELEM_ERROR;

    if ((strcmp(argv[1], "o") == 0 && argc > 4)
        || ((strcmp(argv[1], "a") == 0 || strcmp(argv[1], "m") == 0) && argc < 5))
        return ARGS_NUM_ERROR;

    if (strcmp(argv[1], "o") == 0)
    {
        FILE *mtr_file = fopen(argv[2], "rt");
        if (mtr_file == NULL)
            return FILE_OPEN_ERROR;

        FILE *result_file = fopen(argv[3], "wt");
        if (result_file == NULL)
            return FILE_OPEN_ERROR;

        matrix_t mtr_1;
        int rc = read_matrix(mtr_file, &mtr_1);
        if (rc == READ_ELEM_ERROR)
        {
            printf("%zu %zu", mtr_1.rows, mtr_1.cols);
            printf("Ошибка чтения элемента\n");
            fclose(mtr_file);
            fclose(result_file);
            matrix_free(&mtr_1);
            return rc;
        }
        else if (rc != EXIT_SUCCESS)
        {
            fclose(mtr_file);
            fclose(result_file);
            return rc;
        }
        if (mtr_1.rows != mtr_1.cols)
        {
            fclose(mtr_file);
            fclose(result_file);
            matrix_free(&mtr_1);
            return DETERMINANT_CALC_ERROR;
        }

        double determinant;
        if (matrix_determinant(&mtr_1, mtr_1.rows, &determinant) != EXIT_SUCCESS)
        {
            fclose(mtr_file);
            fclose(result_file);
            matrix_free(&mtr_1);
            return DETERMINANT_CALC_ERROR;
        }
        fprintf(result_file, "%lf", determinant);

        fclose(mtr_file);
        fclose(result_file);
        matrix_free(&mtr_1);
    }
    else
    {
        FILE *mtr_file_1 = fopen(argv[2], "rt");
        if (mtr_file_1 == NULL)
            return FILE_OPEN_ERROR;

        FILE *mtr_file_2 = fopen(argv[3], "rt");
        if (mtr_file_2 == NULL)
            return FILE_OPEN_ERROR;

        FILE *result_file = fopen(argv[4], "wt");
        if (result_file == NULL)
            return FILE_OPEN_ERROR;

        matrix_t mtr_1;
        int rc = read_matrix(mtr_file_1, &mtr_1);
        if (rc == READ_ELEM_ERROR)
        {
            fclose(mtr_file_1);
            fclose(mtr_file_2);
            fclose(result_file);
            matrix_free(&mtr_1);
            return rc;
        }
        else if (rc != EXIT_SUCCESS)
        {
            fclose(mtr_file_1);
            fclose(mtr_file_2);
            fclose(result_file);
            return rc;
        }

        matrix_t mtr_2;
        rc = read_matrix(mtr_file_2, &mtr_2);
        if (rc == READ_ELEM_ERROR)
        {
            fclose(mtr_file_1);
            fclose(mtr_file_2);
            fclose(result_file);
            matrix_free(&mtr_1);
            matrix_free(&mtr_2);
            return rc;
        }
        else if (rc != EXIT_SUCCESS)
        {
            fclose(mtr_file_1);
            fclose(mtr_file_2);
            fclose(result_file);
            matrix_free(&mtr_1);
            return rc;
        }

        matrix_t result;
        if (strcmp(argv[1], "a") == 0)
        {
            if (mtr_1.rows != mtr_2.rows || mtr_1.cols != mtr_2.cols)
            {
                fclose(mtr_file_1);
                fclose(mtr_file_2);
                fclose(result_file);
                matrix_free(&mtr_1);
                matrix_free(&mtr_2);
                return MATRIX_ADD_ERROR;
            }
            rc = matrix_add(&mtr_1, &mtr_2, &result);
            if (rc != EXIT_SUCCESS)
            {
                fclose(mtr_file_1);
                fclose(mtr_file_2);
                fclose(result_file);
                matrix_free(&mtr_1);
                matrix_free(&mtr_2);
                return rc;
            }
        }
        else
        {
            if (mtr_1.cols != mtr_2.rows)
            {
                fclose(mtr_file_1);
                fclose(mtr_file_2);
                fclose(result_file);
                matrix_free(&mtr_1);
                matrix_free(&mtr_2);
                return MATRIX_MUL_ERROR;
            }
            rc = matrix_mul(&mtr_1, &mtr_2, &result);
            if (rc != EXIT_SUCCESS)
            {
                fclose(mtr_file_1);
                fclose(mtr_file_2);
                fclose(result_file);
                matrix_free(&mtr_1);
                matrix_free(&mtr_2);
                return rc;
            }
        }
        print_matrix_to_file(result_file, result);

        fclose(mtr_file_1);
        fclose(mtr_file_2);
        fclose(result_file);
        matrix_free(&mtr_1);
        matrix_free(&mtr_2);
        matrix_free(&result);
    }
    return EXIT_SUCCESS;
}
