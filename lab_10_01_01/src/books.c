#include "books.h"
#include <stdio.h>
#include <stdlib.h>

int read_books(FILE *file, node_t **book_list)
{
    book_t *book = NULL;
    size_t len = 0;
    while (read_book(file, &book) == EXIT_SUCCESS)
    {
        node_t *tmp;
        int rc = node_alloc(&tmp);
        if (rc != EXIT_SUCCESS)
        {
            book_free(book);
            return rc;
        }
        tmp->data = book;
        tmp->next = NULL;
        *book_list = push_back(*book_list, tmp);
        len++;
        book = NULL;
    }
    if (!len)
        return FILE_EMPTY_ERR;

    if (!feof(file))
    {
        free_list(*book_list, book_free);
        return FILE_READ_ERR;
    }

    return EXIT_SUCCESS;
}

void print_books(FILE *file, int year, node_t *book_list)
{
    node_t *curr = book_list;
    for (; curr; curr = curr->next)
    {
        book_t *book = (book_t *)curr->data;
        if (book->year > year)
            fprintf(file, "%s\n%s\n%d\n", book->author, book->title, book->year);
    }
}
