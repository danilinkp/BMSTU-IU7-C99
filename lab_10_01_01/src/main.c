#include "linked_list.h"
#include "books.h"
#include <stdio.h>
#include <stdlib.h>

#define WRONG_ARGS_ERR 9
#define FILE_OPEN_ERR 10
#define NOT_NUMBER_ERR 11

int str_to_int(const char *str_price, int *price)
{
    char *endptr;
    *price = (int) strtol(str_price, &endptr, 10);
    if (*endptr != '\0')
        return NOT_NUMBER_ERR;
    return EXIT_SUCCESS;
}

/*
 Файл содержит данные о книгах: имя автора, название книги и год выпуска.
 Требуется вывести все книги, выпущенные позже указанного года,
 в порядке убывания года выпуска.

 Запуск: app.exe price file_in file_out
 */
int main(int argc, char **argv)
{
    if (argc != 4)
        return WRONG_ARGS_ERR;
    int year;

    int rc = str_to_int(argv[1], &year);
    if (rc != EXIT_SUCCESS || year < 0)
        return WRONG_ARGS_ERR;

    FILE *file_in = fopen(argv[2], "rt");
    if (file_in == NULL)
        return FILE_OPEN_ERR;

    FILE *file_out = fopen(argv[3], "w");
    if (file_out == NULL)
        return FILE_OPEN_ERR;

    node_t *books = NULL;
    rc = read_books(file_in, &books);
    if (rc != EXIT_SUCCESS)
    {
        fclose(file_in);
        fclose(file_out);
        return rc;
    }

    node_t *sorted_books = sort(books, book_year_comparator);

    node_t *reversed_books = reverse(sorted_books);

    print_books(file_out, year, reversed_books);

    fclose(file_in);
    fclose(file_out);
    free_list(reversed_books, book_free);

    return EXIT_SUCCESS;
}
