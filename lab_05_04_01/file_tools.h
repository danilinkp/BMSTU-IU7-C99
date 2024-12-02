#ifndef LAB5_FILE_TOOLS_H
#define LAB5_FILE_TOOLS_H

#include <stdlib.h>
#include <stdio.h>

int print_student_file(FILE *f_src, FILE *f_dst, char *substr);
int del_student(FILE *f);
int sort_file(FILE *f);

#endif //LAB5_FILE_TOOLS_H
