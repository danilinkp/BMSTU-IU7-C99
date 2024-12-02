#ifndef LAB5_STUDENT_H
#define LAB5_STUDENT_H

#include <stdint.h>

#define SURNAME_LEN 25
#define NAME_LEN 10
#define NUM_OF_MARKS 4

typedef struct
{
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    uint32_t marks[NUM_OF_MARKS];
} student_t;

#endif //LAB5_STUDENT_H