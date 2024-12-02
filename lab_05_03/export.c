#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ERR_FILE_WORK 2
#define EMPTY_FILE 3
#define ERR_FILE_READ 4
#define FILE_OPEN_ERR 7

static int get_number_by_pos(FILE *f, long pos, int32_t *num)
{
    fseek(f, pos * sizeof(int32_t), SEEK_SET);
    fread(num, sizeof(int32_t), 1, f);
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

int export_from_bin(char *file_bin, char *file_txt)
{
    FILE *in;
    in = fopen(file_bin, "rb");

    if (in == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }

    FILE *out;
    out = fopen(file_txt, "w");

    if (out == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }

    size_t size;
    int rc = file_size(in, &size);

    if (rc != 0)
    {
        fclose(in);
        return rc;
    }

    size /= sizeof(int32_t);

    int32_t t;

    for (size_t i = 0; i < size; i++)
    {
        get_number_by_pos(in, i, &t);
        fprintf(out, "%d" "\n", t);
    }

    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}