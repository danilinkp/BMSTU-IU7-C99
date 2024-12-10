#define _GNU_SOURCE

#include "book.h"
#include <stdlib.h>
#include <string.h>

void book_free(void *data)
{
    book_t *book = (book_t *) data;
    if (strlen(book->author) != 0)
        free(book->author);
    if (strlen(book->title) != 0)
        free(book->title);
    free(book);
}

int book_create(book_t **book, char *author, char *title, int year)
{
    *book = malloc(sizeof(book_t));
    if (!(*book))
        return BOOK_ALLOC_ERR;
    (*book)->author = author;
    (*book)->title = title;
    (*book)->year = year;

    return EXIT_SUCCESS;
}

static int read_str(FILE *file, char **str)
{
    size_t len = 0;
    char *line = NULL;
    ssize_t read;

    read = getline(&line, &len, file);
    if (read == -1)
    {
        free(line);
        return STR_READ_ERR;
    }
    if (len == 0)
    {
        free(line);
        return STR_READ_ERR;
    }

    line[strcspn(line, "\n")] = '\0';
    *str = line;

    return EXIT_SUCCESS;
}

int read_book(FILE *file, book_t **book)
{
    char *author = NULL;
    int rc = read_str(file, &author);
    if (rc != EXIT_SUCCESS)
        return BOOK_AUTHOR_READ_ERR;

    char *title = NULL;
    rc = read_str(file, &title);
    if (rc != EXIT_SUCCESS)
    {
        free(author);
        return BOOK_TITLE_READ_ERR;
    }

    int year;
    if (fscanf(file, "%d\n", &year) != 1 || year <= 0)
    {
        free(author);
        free(title);
        return YEAR_READ_ERR;
    }

    rc = book_create(book, author, title, year);
    if (rc != EXIT_SUCCESS)
        return rc;
    return EXIT_SUCCESS;
}

int book_year_comparator(const void *pbook_1, const void *pbook_2)
{
    book_t *book_1 = (book_t *) pbook_1;
    book_t *book_2 = (book_t *) pbook_2;
    return book_1->year - book_2->year;
}
