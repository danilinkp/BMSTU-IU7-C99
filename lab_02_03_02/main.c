#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define ELEM_ERROR 1
#define LEN_ERROR 2
#define EMPTY_ARRAY 3
#define NMAX 10

int input_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
        {
            printf("Ошибка ввода элементов");
            return ELEM_ERROR;
        }
    return EXIT_SUCCESS;
}

void print_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}

int is_full_square(int number)
{
    if ((int) sqrt(number) * (int) sqrt(number) == number)
        return 1;
    return 0;
}

size_t remove_full_square(int a[], size_t alen)
{
    size_t c = 0;
    for (size_t i = 0; i < alen; i++)
        if (is_full_square(a[i]))
            c++;
        else
            a[i - c] = a[i];
    return alen - c;
}

int main(void)
{
    size_t alen;
    int a[NMAX];

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
    {
        printf("Ошибка ввода длины массива");
        return LEN_ERROR;
    }
    printf("Введите массив: ");
    if (input_array(a, alen) != 0)
        return ELEM_ERROR;

    size_t size = remove_full_square(a, alen);
    if (size < 1)
    {
        printf("Массив пустой");
        return EMPTY_ARRAY;
    }

    print_array(a, size);
    return EXIT_SUCCESS;
}