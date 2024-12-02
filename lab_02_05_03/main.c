#include <stdio.h>
#include <stdlib.h>

#define ELEM_ERROR 1
#define LEN_ERROR 2
#define NMAX 10

int input_array(int *pb, int *pe)
{
    for (int *pcur = pb; pcur < pe; pcur++)
        if (scanf("%d", pcur) != 1)
        {
            printf("Ошибка ввода элемента");
            return ELEM_ERROR;
        }
    return EXIT_SUCCESS;
}

int min_of_array(int *pb, int *pe)
{
    int min = *pb * *(pb + 1);
    for (int *pcur = pb; pcur < pe - 1; pcur++)
        if ((*pcur * *(pcur + 1)) < min)
            min = *pcur * *(pcur + 1);
    return min;
}

int main(void)
{
    size_t alen;
    int a[NMAX];
    int *pa = a;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen < 2 || alen > 10)
    {
        printf("Ошибка ввода длины массива");
        return LEN_ERROR;
    }

    printf("Введите массив: ");
    if (input_array(pa, pa + alen) != EXIT_SUCCESS)
        return ELEM_ERROR;

    printf("Минимальное значение: %d\n", min_of_array(pa, pa + alen));

    return EXIT_SUCCESS;
}
