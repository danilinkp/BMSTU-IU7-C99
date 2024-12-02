#include "file_tools.h"
#include "import.h"
#include "export.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARGS_ERR 6
#define ERROR_WRONG_ARGS 53
#define FILE_OPEN_ERR 7


int main(int argc, char **argv)
{
    if (argc < 3 || argc > 5)
    {
        printf("Аргументов не достаточно или их слишком много");
        return ERROR_WRONG_ARGS;
    }

    FILE *file;
    int rc = EXIT_SUCCESS;
    if (strcmp(argv[1], "sb") == 0 && argc == 3)
    {
        file = fopen(argv[2], "r+b");
        if (file == NULL)
        {
            printf("Ошибка открытия файла\n");
            return FILE_OPEN_ERR;
        }
        rc = sort_file(file);
        fclose(file);
    }
    else if (strcmp(argv[1], "fb") == 0 && argc == 5)
    {
        FILE *file_src = fopen(argv[2], "rb");
        if (file_src == NULL)
        {
            printf("Ошибка открытия файла\n");
            return FILE_OPEN_ERR;
        }
        FILE *file_dst = fopen(argv[3], "wb");

        rc = print_student_file(file_src, file_dst, argv[4]);
        fclose(file_src);
        fclose(file_dst);
    }
    else if (strcmp(argv[1], "db") == 0 && argc == 3)
    {
        file = fopen(argv[2], "r+b");
        if (file == NULL)
        {
            printf("Ошибка открытия файла\n");
            return FILE_OPEN_ERR;
        }
        rc = del_student(file);
        fclose(file);
    }
    else if (strcmp(argv[1], "import") == 0 && argc == 4)
    {
        rc = import_to_bin(argv[2], argv[3]);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    else if (strcmp(argv[1], "export") == 0 && argc == 4)
    {
        rc = export_from_bin(argv[2], argv[3]);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    else
        rc = ERROR_WRONG_ARGS;
    return rc;
}
