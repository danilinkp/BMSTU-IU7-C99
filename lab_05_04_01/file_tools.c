#include "file_tools.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
int fileno(FILE *stream);

#define ERR_FILE_WORK 2
#define EMPTY_FILE 3
#define ERR_FILE_READ 4
#define NO_SUBSTR 5
#define NOTHING_PRINT 8

static int get_student_by_pos(FILE *f, long pos, student_t *student)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fread(student, sizeof(student_t), 1, f);
    return EXIT_SUCCESS;
}

static int put_student_by_pos(FILE *f, long pos, student_t student)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fwrite(&student, sizeof(student_t), 1, f);
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

int sort_file(FILE *f)
{
    size_t size;
    int rc = EXIT_SUCCESS;
    rc = file_size(f, &size);
    if (rc != EXIT_SUCCESS)
        return rc;
    for (size_t i = 0; i < (size / sizeof(student_t)) - 1; i++)
        for (size_t j = 0; j < (size / sizeof(student_t)) - i - 1; j++)
        {
            student_t tmp_st1, tmp_st2;

            get_student_by_pos(f, j, &tmp_st1);
            get_student_by_pos(f, j + 1, &tmp_st2);
            if ((strcmp(tmp_st1.surname, tmp_st2.surname) > 0))
            {
                put_student_by_pos(f, j, tmp_st2);
                put_student_by_pos(f, j + 1, tmp_st1);
            }
            else if ((strcmp(tmp_st1.surname, tmp_st2.surname) == 0 && strcmp(tmp_st1.name, tmp_st2.name) > 0))
            {
                put_student_by_pos(f, j, tmp_st2);
                put_student_by_pos(f, j + 1, tmp_st1);
            }
        }
    for (size_t i = 0; i < size / sizeof(student_t); i++)
    {
        student_t temp;
        get_student_by_pos(f, i, &temp);
        printf("%s\n", temp.surname);
        printf("%s\n", temp.name);
        printf("%u %u %u %u\n", temp.marks[0], temp.marks[1], temp.marks[2], temp.marks[3]);
    }

    return EXIT_SUCCESS;
}

int print_student_file(FILE *f_src, FILE *f_dst, char *substr)
{
    size_t size;
    student_t student;
    int rc = file_size(f_src, &size);
    if (rc != EXIT_SUCCESS)
        return rc;
    if (strlen(substr) > SURNAME_LEN || strlen(substr) == 0)
        return NO_SUBSTR;
    long count = 0;
    for (size_t i = 0; i < size / sizeof(student_t); i++)
    {
        get_student_by_pos(f_src, i, &student);
        char *start = strstr(student.surname, substr);
        if (start != NULL && start - student.surname == 0)
        {
            put_student_by_pos(f_dst, count, student);
            count++;
        }
    }
    if (count == 0)
        return NOTHING_PRINT;
    return EXIT_SUCCESS;
}

static int get_avg_marks(FILE *f, double *avg)
{
    *avg = 0;
    size_t size;
    int rc = EXIT_SUCCESS;
    rc = file_size(f, &size);
    if (rc != EXIT_SUCCESS)
        return rc;
    for (size_t i = 0; i < size / sizeof(student_t); i++)
    {
        double sum = 0;
        student_t student;
        get_student_by_pos(f, i, &student);
        for (size_t j = 0; j < 4; j++)
        {
            sum += student.marks[j];
        }
        double cur_avg = sum / 4;
        *avg += cur_avg;
    }
    *avg /= size / sizeof(student_t);
    return EXIT_SUCCESS;
}

int del_student(FILE *f)
{
    double avg;
    size_t size;
    int rc = EXIT_SUCCESS;
    rc = file_size(f, &size);
    if (rc != EXIT_SUCCESS)
        return rc;
    if (get_avg_marks(f, &avg) != 0)
        return ERR_FILE_WORK;
    size_t c = 0;
    for (size_t i = 0; i < size / sizeof(student_t); i++)
    {
        double sum = 0;
        student_t student;
        get_student_by_pos(f, i, &student);
        for (size_t j = 0; j < 4; j++)
            sum += student.marks[j];
        double cur_avg = sum / 4;
        if (cur_avg < avg)
            c++;
        else
            put_student_by_pos(f, i - c, student);
    }
//    fflush(f);

    ftruncate(fileno(f), size - c * sizeof(student_t));
    return EXIT_SUCCESS;
}