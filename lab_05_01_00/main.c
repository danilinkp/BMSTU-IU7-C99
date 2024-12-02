#include <stdio.h>
#include <stdlib.h>
#include "file_tools.h"

int main(void)
{
    int max;
    printf("Введите числа: ");
    int rc = process(stdin, &max);
    if (rc != 0)
    {
        printf("Not enough data\n");
        return rc;
    }
    printf("%d\n", max);
    return EXIT_SUCCESS;
}
