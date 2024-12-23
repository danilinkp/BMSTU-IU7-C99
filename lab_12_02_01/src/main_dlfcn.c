#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

enum errors
{
    WRONG_ARGS_ERROR = 6,
    LIB_LOAD_ERROR,
    LIB_FUNCS_LOAD_ERROR,
    MEMORY_ALLOCATION_ERROR,
};

typedef int (*fn_read_nums_to_array_t)(const char *, int *, int *);
typedef int (*fn_file_count_elems_t)(const char *, size_t *);
typedef int (*fn_my_comp_int_t)(const void *, const void *);
typedef int (*fn_mysort_t)(void *, size_t, size_t, int (*compar)(const void *, const void *));
typedef int (*fn_write_array_to_file_t)(const char *, int *, int *);
typedef int (*fn_count_pos_elems_t)(const int *, const int *);
typedef int (*fn_key_t)(const int *, const int *, int **, int **);

int main(int argc, char **argv)
{
    void *hlib = dlopen("libarr.so", RTLD_NOW);
    if (!hlib)
    {
        printf("Cannot open library. %s\n", dlerror());
        return LIB_LOAD_ERROR;
    }

    fn_read_nums_to_array_t read_nums_to_array = (fn_read_nums_to_array_t) dlsym(hlib, "read_nums_to_array");
    fn_file_count_elems_t file_count_elems = (fn_file_count_elems_t) dlsym(hlib, "file_count_elems");
    fn_my_comp_int_t my_comp_int = (fn_my_comp_int_t) dlsym(hlib, "my_comp_int");
    fn_mysort_t mysort = (fn_mysort_t) dlsym(hlib, "mysort");
    fn_write_array_to_file_t write_array_to_file = (fn_write_array_to_file_t) dlsym(hlib, "write_array_to_file");
    fn_count_pos_elems_t count_pos_elems = (fn_count_pos_elems_t) dlsym(hlib, "count_pos_elems");
    fn_key_t key = (fn_key_t) dlsym(hlib, "key");

    if (!read_nums_to_array || !file_count_elems || !my_comp_int || !mysort || !write_array_to_file || !count_pos_elems || !key)
    {
        dlclose(hlib);
        return LIB_FUNCS_LOAD_ERROR;
    }

    if (argc < 3 || argc > 4)
    {
        dlclose(hlib);
        return WRONG_ARGS_ERROR;
    }
    int is_filter_key = 0;
    if (argc == 4 && strcmp(argv[3], "f") == 0)
        is_filter_key = 1;
    else if (argc == 4 && strcmp(argv[3], "f") != 0)
    {
        dlclose(hlib);
        return WRONG_ARGS_ERROR;
    }
    char *file_src = argv[1];
    char *file_dst = argv[2];

    size_t num_of_elems;
    int rc = file_count_elems(file_src, &num_of_elems);
    if (rc != EXIT_SUCCESS)
    {
        dlclose(hlib);
        return rc;
    }

    int *arr = malloc(num_of_elems * sizeof(int));

    rc = read_nums_to_array(file_src, arr, arr + num_of_elems);
    if (rc != EXIT_SUCCESS)
    {
        free(arr);
        dlclose(hlib);
        return rc;
    }

    if (is_filter_key)
    {
        size_t new_size = count_pos_elems(arr, arr + num_of_elems);
        int *filtered_arr_pb = malloc(new_size * sizeof(int));
        int *filtered_arr_pe = filtered_arr_pb + new_size;
        rc = key(arr, arr + num_of_elems, &filtered_arr_pb, &filtered_arr_pe);
        if (rc != EXIT_SUCCESS)
        {
            dlclose(hlib);
            free(arr);
            return rc;
        }
        mysort(filtered_arr_pb, filtered_arr_pe - filtered_arr_pb, sizeof(int), my_comp_int);
        rc = write_array_to_file(file_dst, filtered_arr_pb, filtered_arr_pe);
        if (rc != EXIT_SUCCESS)
        {
            dlclose(hlib);
            free(filtered_arr_pb);
            free(arr);
            return rc;
        }
        free(filtered_arr_pb);
        free(arr);
        dlclose(hlib);
    }
    else
    {
        mysort(arr, num_of_elems, sizeof(int), my_comp_int);
        rc = write_array_to_file(file_dst, arr, arr + num_of_elems);
        if (rc != EXIT_SUCCESS)
        {
            free(arr);
            dlclose(hlib);
            return rc;
        }
        free(arr);
        dlclose(hlib);
    }

    return EXIT_SUCCESS;
}
