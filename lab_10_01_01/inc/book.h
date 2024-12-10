#ifndef LAB10_BOOK_H
#define LAB10_BOOK_H

#include "stdio.h"
#include "linked_list.h"

typedef struct
{
    char *author;
    char *title;
    int year;
} book_t;

enum errors
{
    BOOK_ALLOC_ERR = 2,
    STR_READ_ERR,
    BOOK_AUTHOR_READ_ERR,
    BOOK_TITLE_READ_ERR,
    YEAR_READ_ERR
};

void book_free(void *data);

int book_create(book_t **book, char *author, char *title, int year);

int read_book(FILE *file, book_t **book);

int book_year_comparator(const void *pbook_1, const void *pbook_2);

#endif //LAB10_BOOK_H
