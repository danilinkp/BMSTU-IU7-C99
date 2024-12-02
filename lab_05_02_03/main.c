#include <stdio.h>
#include <stdlib.h>
#include "file_tools.h"

#define EMPTY_FILE -1
#define FILE_OPEN_ERR 2
#define ARGS_ERR 3

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 2)
    {
        printf("Аргументов не достаточно или их слишком много");
        return ARGS_ERR;
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }
    int n;
    if (file_len(file, &n) != EXIT_SUCCESS)
    {
        printf("Файл пустой или в нем нет вещественных чисел.");
        return EMPTY_FILE;
    }

    int res = three_sigma_rule(file, n);
    printf("%d\n", res);

    fclose(file);
    return EXIT_SUCCESS;
}
