#include "file_tools.h"
#include <stdio.h>

#define EMPTY_FILE -1
#define NOT_ENOUGH_DATA -2

int process(FILE *f, int *max)
{
    int prev, curr;
    *max = -1;
    if (fscanf(f, "%d", &prev) != 1)
    {
        return EMPTY_FILE;
    }
    while (fscanf(f, "%d", &curr) == 1)
    {
        if (prev < 0 && curr > 0)
            if (curr > *max)
                *max = curr;
        prev = curr;
    }
    if (*max == -1)
        return NOT_ENOUGH_DATA;

    return 0;
}
