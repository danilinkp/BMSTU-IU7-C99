#include <stdio.h>
#include <stdlib.h>
#define ARRAY_IS_FULL 100
#define NMAX 10

size_t input_array_until_10_elems(int a[])
{
    size_t c = 0;
    int input_elem;
    while (scanf("%d", &input_elem) == 1)
    {
        if (c == 10)
            return ++c;
        a[c] = input_elem;
        c++;
    }
    return c;
}

void print_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}

void bubble_sort(int a[], size_t alen)
{
    for (size_t i = 0; i < alen - 1; i++)
        for (size_t j = 0; j < alen - i - 1; j++)
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

int main(void)
{
    int a[NMAX];
    int arr_is_full = 0;
    printf("Введите массив: ");
    size_t array_size = input_array_until_10_elems(a);
    if (array_size == 0)
    {
        printf("Массив пустой");
        return EXIT_FAILURE;
    }
    if (array_size > 10)
    {
        array_size = 10;
        arr_is_full = 1;
    }
    bubble_sort(a, array_size);
    print_array(a, array_size);
    if (arr_is_full)
        return ARRAY_IS_FULL;
    return EXIT_SUCCESS;
}
