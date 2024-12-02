#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dynamic_array.h"

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return WRONG_ARGS_ERROR;
    int is_filter_key = 0;
    if (argc == 4 && strcmp(argv[3], "f") == 0)
        is_filter_key = 1;
    else if (argc == 4 && strcmp(argv[3], "f") != 0)
        return WRONG_ARGS_ERROR;

    char *file_src = argv[1];
    char *file_dst = argv[2];

    size_t num_of_elems;
    int rc = count_elems(file_src, &num_of_elems);
    if (rc != EXIT_SUCCESS)
        return rc;

    int *arr = malloc(num_of_elems * sizeof(int));

    rc = read_nums_to_array(file_src, arr, arr + num_of_elems);
    if (rc != EXIT_SUCCESS)
    {
        free(arr);
        return rc;
    }

    if (is_filter_key)
    {
        int *filtered_arr_pb;
        int *filtered_arr_pe;
        rc = key(arr, arr + num_of_elems, &filtered_arr_pb, &filtered_arr_pe);
        if (rc != EXIT_SUCCESS)
        {
            free(arr);
            return rc;
        }
        mysort(filtered_arr_pb, filtered_arr_pe - filtered_arr_pb, sizeof(int), my_comp_int);
        rc = write_array_to_file(file_dst, filtered_arr_pb, filtered_arr_pe);
        if (rc != EXIT_SUCCESS)
        {
            free(filtered_arr_pb);
            free(arr);
            return rc;
        }
        free(filtered_arr_pb);
        free(arr);
    }
    else
    {
        mysort(arr, num_of_elems, sizeof(int), my_comp_int);
        rc = write_array_to_file(file_dst, arr, arr + num_of_elems);
        if (rc != EXIT_SUCCESS)
        {
            free(arr);
            return rc;
        }
        free(arr);
    }

    return EXIT_SUCCESS;
}