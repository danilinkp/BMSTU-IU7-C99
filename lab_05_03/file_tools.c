#include "file_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define ERR_FILE_WORK 2
#define EMPTY_FILE 3
#define ERR_FILE_READ 4

static int get_number_by_pos(FILE *f, long pos, int32_t *num)
{
    fseek(f, pos * sizeof(int32_t), SEEK_SET);
    fread(num, sizeof(int32_t), 1, f);
    return EXIT_SUCCESS;
}

static int put_number_by_pos(FILE *f, long pos, int32_t num)
{
    fseek(f, pos * sizeof(int32_t), SEEK_SET);
    fwrite(&num, sizeof(int32_t), 1, f);
    return EXIT_SUCCESS;
}

static int file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return EXIT_FAILURE;
    sz = ftell(f);
    if (sz < 0)
        return ERR_FILE_WORK;
    if (sz == 0)
        return EMPTY_FILE;
    if (sz % sizeof(int32_t) != 0)
        return ERR_FILE_READ;
    *size = sz;
    return fseek(f, 0L, SEEK_SET);
}

int init_file(FILE *f, size_t size)
{
    int32_t num;
    srand(time(NULL));
    for (size_t i = 0; i < size; i++)
    {
        num = rand() % 100000;
        put_number_by_pos(f, i, num);
    }
    return EXIT_SUCCESS;
}

int print_int_file(FILE *f)
{
    size_t size;
    int32_t num;
    int rc = file_size(f, &size);
    if (rc != EXIT_SUCCESS)
        return rc;
    for (size_t i = 0; i < size / sizeof(int32_t); i++)
    {
        get_number_by_pos(f, i, &num);
        printf("%d ", num);
    }
    return EXIT_SUCCESS;
}


int sort_file(FILE *f)
{
    int32_t tmp_j1, tmp_j2;
    size_t size;
    int rc = EXIT_SUCCESS;
    rc = file_size(f, &size);
    if (rc != EXIT_SUCCESS)
        return rc;
    for (size_t i = 0; i < (size / sizeof(int32_t)) - 1; i++)
        for (size_t j = 0; j < (size / sizeof(int32_t)) - i - 1; j++)
        {
            get_number_by_pos(f, j, &tmp_j1);
            get_number_by_pos(f, j + 1, &tmp_j2);
            if (tmp_j2 < tmp_j1)
            {
                put_number_by_pos(f, j, tmp_j2);
                put_number_by_pos(f, j + 1, tmp_j1);
            }
        }
    return EXIT_SUCCESS;
}