#include "file_tools.h"
#include "import.h"
#include "export.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARGS_ERR 5
#define ERROR_WRONG_ARGS 6
#define FILE_OPEN_ERR 7

// Для работы с целочисленными числами был выбран тип int32_t,
// поскольку он обеспечивает достаточный диапазон для большинства приложений и имеет приемлемый размер для хранения
// Алгоритм сортировки - сортировка пузырьком
// Направление упорядочения - по возрастанию

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        printf("Аргументов не достаточно или их слишком много");
        return ARGS_ERR;
    }

    FILE *file;
    int rc = EXIT_SUCCESS;
    if (*argv[1] == 'c' && argc == 4)
    {
        file = fopen(argv[3], "wb");
        if (file == NULL)
        {
            printf("Ошибка открытия файла\n");
            return FILE_OPEN_ERR;
        }
        rc = init_file(file, atoi(argv[2]));
        fclose(file);
    }
    else if (*argv[1] == 'p' && argc == 3)
    {
        file = fopen(argv[2], "rb");
        if (file == NULL)
        {
            printf("Ошибка открытия файла\n");
            return FILE_OPEN_ERR;
        }
        rc = print_int_file(file);
        fclose(file);
    }
    else if (*argv[1] == 's' && argc == 3)
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
