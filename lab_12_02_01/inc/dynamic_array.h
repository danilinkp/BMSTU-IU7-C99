#ifndef C_LABS_DYN_ARR_LIB_H
#define C_LABS_DYN_ARR_LIB_H

#include <stdlib.h>

enum error_codes
{
    FILE_OPEN_ERROR = 1,
    EMPTY_FILE_ERROR,
    FILE_READ_ERROR,
    MEMORY_ALLOCATION_ERROR,
    DATA_ARRAY_ERROR,
    WRONG_ARGS_ERROR
};

int read_nums_to_array(const char *file_src, int *pb, int *pe);

int file_count_elems(const char *file_src, size_t *num_of_elems);

int my_comp_int(const void *pl, const void *pr);

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

int write_array_to_file(const char *file_dst, int *pb, int *pe);

size_t count_pos_elems(const int *pb_src, const int *pe_src);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif //C_LABS_DYN_ARR_LIB_H
