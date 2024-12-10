#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EMPTY_ARRAY 1
#define NMAX 100


size_t input_arr_by_end(int a[], int n_max)
{
    int c = 0;
    double temp;
    while (scanf("%lf", &temp) == 1 || c > n_max)
    {
        a[c] = temp;
        c++;
    }

    return c;
}


void print_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}


int is_full_square(double num)
{
    return (int) sqrt(num) * (int) sqrt(num) == num;
}


int remove_full_square(int a[], size_t alen)
{
    int c = 0;
    for (size_t i = 0; i < alen; i++)
        if (is_full_square(a[i]))
            c++;
        else
            a[i - c] = a[i];
    return alen - c;
}


int main(void)
{
    int is_working = 1;
    do
    {
        int a[NMAX];
        printf("Enter elems of array: \n");
        size_t alen = input_arr_by_end(a, NMAX);
        printf("%zu\n", alen);
        size_t len_after_remove = remove_full_square(a, alen);
        if (len_after_remove < 1)
        {
            printf("Массив пустой");
            return EMPTY_ARRAY;
        }
        print_array(a, len_after_remove);
    }
    while (is_working);
    return EXIT_SUCCESS;

}