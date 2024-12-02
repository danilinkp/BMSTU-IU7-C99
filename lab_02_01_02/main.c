#include <stdio.h>
#include <stdlib.h>
#define ELEM_ERROR 1
#define LEN_ERROR 2
#define NO_NEGATIVES 3
#define NMAX 10

int input_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
        {
            printf("Ошибка ввода элемента");
            return ELEM_ERROR;
        }
    return EXIT_SUCCESS;
}

int average_of_negatives(int a[], size_t n, double *avg)
{
    double sum = 0;
    int count = 0;
    for (size_t i = 0; i < n; i++)
        if (a[i] < 0)
        {
            sum += a[i];
            count++;
        }
    *avg = sum / count;
    if (count < 1)
        return NO_NEGATIVES;
    return EXIT_SUCCESS;
}

int main(void)
{
    size_t alen;
    int a[NMAX];
    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
    {
        printf("Ошибка ввода длины");
        return LEN_ERROR;
    }
    printf("Введите массив: ");
    if (input_array(a, alen) != 0)
        return ELEM_ERROR;

    double avg;
    int res = average_of_negatives(a, alen, &avg);

    if (res > 0)
    {
        printf("Негативных элементов нет");
        return res;
    }
    printf("%.6lf", avg);
    return EXIT_SUCCESS;
}