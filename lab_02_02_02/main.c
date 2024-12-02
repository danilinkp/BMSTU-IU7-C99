#include <stdio.h>
#include <stdlib.h>
#define ELEM_ERROR 1
#define LEN_ERROR 2
#define NO_SAME_DIGITS 3
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

int get_first_digit(int number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    return number;
}

int get_last_digit(int number)
{
    return number % 10;
}

int is_same_first_and_last_digits(int number)
{   
    if (number < 0)
        number *= -1;
    int first_digit = get_first_digit(number);
    int last_digit = get_last_digit(number);
    if (first_digit == last_digit)
        return 1;
    
    return 0;
}

size_t copy_numbers_with_same_digits(int a[], size_t alen, int b[])
{
    size_t c = 0;
    for (size_t i = 0; i < alen; i++)
        if (is_same_first_and_last_digits(a[i]))
        {
            c++;
            b[c - 1] = a[i];
        }
    return c;
}

int main(void)
{
    size_t alen;
    int a[NMAX];
    int b[NMAX];

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen > 10)
    {
        printf("Ошибка ввода длины");
        return LEN_ERROR;
    }

    printf("Введите массив: ");
    if (input_array(a, alen) != EXIT_SUCCESS)
        return ELEM_ERROR;

    size_t size = copy_numbers_with_same_digits(a, alen, b);
    if (size < 1)
    {
        printf("В массиве нет подходящих элементов");
        return NO_SAME_DIGITS;
    }
    print_array(b, size);

    return EXIT_SUCCESS;
}