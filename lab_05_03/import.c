#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FILE_OPEN_ERR 7

static int file_len(FILE *f, long *n)
{
    rewind(f);
    double curr;
    *n = 0;
    if (fscanf(f, "%lf", &curr) == 1)
    {
        (*n)++;
        while (fscanf(f, "%lf", &curr) == 1)
            (*n)++;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int import_to_bin(char *txt_file, char *bin_file)
{
    FILE *in;
    in = fopen(txt_file, "r");
    if (in == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }
    FILE *out;
    out = fopen(bin_file, "wb");
    if (out == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }
    long n;
    file_len(in, &n);
    int32_t t;
    rewind(in);
    for (long i = 0; i < n; i++)
    {
        if (fscanf(in, "%d", &t) == 1)
        {
            fseek(out, 0, SEEK_END);
            fwrite(&t, sizeof(int32_t), 1, out);
        }
    }
    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}