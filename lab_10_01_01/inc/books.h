#ifndef LAB10_BOOKS_H
#define LAB10_BOOKS_H

#include "book.h"
#include "linked_list.h"

enum file_errors
{
    FILE_EMPTY_ERR = 7,
    FILE_READ_ERR
};

int read_books(FILE *file, node_t **book_list);

void print_books(FILE *file, int year, node_t *book_list);

#endif //LAB10_BOOKS_H
