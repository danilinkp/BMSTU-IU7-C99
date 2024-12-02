#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "student.h"

#define ERR_FILE_WORK 2
#define EMPTY_FILE 3
#define ERR_FILE_READ 4
#define FILE_OPEN_ERR 7

static int get_student_by_pos(FILE *f, long pos, student_t *student)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fread(student, sizeof(student_t), 1, f);
    return EXIT_SUCCESS;
}

static int file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return EXIT_FAILURE;
    sz = ftell(f);
    if (sz < 0)
        return ERR_FILE_WORK;
    if (sz == 0)
        return EMPTY_FILE;
    if (sz % sizeof(student_t) != 0)
        return ERR_FILE_READ;
    *size = sz;
    return fseek(f, 0L, SEEK_SET);
}

int export_from_bin(char *file_bin, char *file_txt)
{
    FILE *in;
    in = fopen(file_bin, "rb");

    if (in == NULL)
    {
        printf("Ошибка открытия бин файла\n");
        return FILE_OPEN_ERR;
    }

    FILE *out;
    out = fopen(file_txt, "w");

    if (out == NULL)
    {
        printf("Ошибка открытия ткст файла\n");
        return FILE_OPEN_ERR;
    }

    size_t size;
    int rc = file_size(in, &size);

    if (rc != 0)
    {
        fclose(in);
        return rc;
    }

    size /= sizeof(student_t);

    student_t student;

    for (size_t i = 0; i < size; i++)
    {
        get_student_by_pos(in, i, &student);
        fprintf(out, "%s\n", student.surname);
        fprintf(out, "%s\n", student.name);
        fprintf(out, "%u %u %u %u\n", student.marks[0], student.marks[1], student.marks[2], student.marks[3]);
    }

    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}
