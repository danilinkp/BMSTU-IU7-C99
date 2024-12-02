#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define FILE_OPEN_ERR 7
#define EMPTY_FILE 3

static int file_len(FILE *f, long *n)
{
    rewind(f);
    student_t student;
    *n = 0;
    if (fscanf(f, "%s %s %u %u %u %u", student.surname, student.name, &student.marks[0], &student.marks[1], &student.marks[2], &student.marks[3]) == 6)
    {
        (*n) += 1;
        while (fscanf(f, "%s %s %u %u %u %u", student.surname, student.name, &student.marks[0], &student.marks[1], &student.marks[2], &student.marks[3]) == 6)
            (*n) += 1;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int import_to_bin(char *txt_file, char *bin_file)
{
    FILE *in;
    in = fopen(txt_file, "r");
    if (in == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }
    FILE *out;
    out = fopen(bin_file, "wb");
    if (out == NULL)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERR;
    }
    long n;
    file_len(in, &n);
    if (n <= 0)
    {
        return EMPTY_FILE;
    }
    student_t student;
    rewind(in);
    for (long i = 0; i < n; i++)
    {
        if (fscanf(in, "%s %s %u %u %u %u", student.surname, student.name, &student.marks[0], &student.marks[1], &student.marks[2], &student.marks[3]) == 6)
        {
//            printf("%s %s %u %u %u %u\n", student.surname, student.name, student.marks[0], student.marks[1], student.marks[2], student.marks[3]);
            fseek(out, 0, SEEK_END);
            fwrite(&student, sizeof(student_t), 1, out);
        }
    }
    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}