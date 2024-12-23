#include "dynamic_array.h"
#include <stdio.h>
#include <string.h>

int file_count_elems(const char *file_src, size_t *num_of_elems)
{
    FILE *file = fopen(file_src, "rt");
    if (file == NULL)
        return FILE_OPEN_ERROR;

    int elem;
    *num_of_elems = 0;
    while (fscanf(file, "%d", &elem) == 1)
        (*num_of_elems)++;
    if (!feof(file))
    {
        fclose(file);
        return FILE_READ_ERROR;
    }
    fclose(file);
    if (*num_of_elems == 0)
        return EMPTY_FILE_ERROR;
    return EXIT_SUCCESS;
}

int read_nums_to_array(const char *file_src, int *pb, int *pe)
{
    FILE *file = fopen(file_src, "rt");
    if (file == NULL)
        return FILE_OPEN_ERROR;

    for (int *pi = pb; pi < pe; pi++)
        if (fscanf(file, "%d", pi) != 1)
        {
            fclose(file);
            return FILE_READ_ERROR;
        }
    fclose(file);
    return EXIT_SUCCESS;
}

int my_comp_int(const void *pl, const void *pr)
{
    const int *int_pl = (const int *) pl;
    const int *int_pr = (const int *) pr;
    if (*int_pl < *int_pr)
        return -1;
    else if (*int_pl == *int_pr)
        return 0;
    else
        return 1;
}

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char *pb = base;
    char *pe = pb + nmemb * size;
    for (char *pi = pb + size; pi < pe; pi += size)
        for (char *pk = pi; pk > pb && compar((pk - size), pk) > 0; pk -= size)
        {
            char buf[size];
            memcpy(buf, (pk - size), size);
            memcpy((pk - size), pk, size);
            memcpy(pk, buf, size);
        }
}

int write_array_to_file(const char *file_dst, int *pb, int *pe)
{
    FILE *file = fopen(file_dst, "wt");
    if (file == NULL)
        return FILE_OPEN_ERROR;

    for (int *pi = pb; pi < pe; pi++)
        fprintf(file, "%d ", *pi);

    fclose(file);
    return EXIT_SUCCESS;
}

size_t count_pos_elems(const int *pb_src, const int *pe_src)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
        return 0;

    size_t count = 0;
    for (const int *pi = pb_src; pi < pe_src && *pi >= 0; pi++)
        count++;

    return count;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
        return DATA_ARRAY_ERROR;

    size_t count = *pe_dst - *pb_dst;

    if (count == 0)
        return DATA_ARRAY_ERROR;

    memcpy(*pb_dst, pb_src, count * sizeof(int));

    return EXIT_SUCCESS;
}
