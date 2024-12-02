#include "matrix.h"
#include <stdio.h>


size_t input_matrix(matrix_t matrix, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
            {
                return ELEM_ERROR;
            }
    return EXIT_SUCCESS;
}


int is_sum_of_digits_even(int number)
{
    int abs_number = abs(number);
    int s = 0;
    while (abs_number > 0)
    {
        s += abs_number % 10;
        abs_number /= 10;
    }
    return s % 2 == 0;
}

int is_line_with_odd_elems(array_t arr, size_t len)
{
    int count = 0;
    for (size_t i = 0; i < len; i++)
        if (!is_sum_of_digits_even(arr[i]))
            count++;
    return count >= 2;
}

void assign_array(int arr_1[], int arr_2[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        arr_1[i] = arr_2[i];
}

size_t insert_line(matrix_t matrix, array_t line, size_t row, size_t col)
{
    size_t c = 0;
    for (size_t i = 0; i < row; i++)
        if (is_line_with_odd_elems(matrix[i], col))
            c++;
    int end_index = row - 1 + c;
    for (int i = row - 1; i > -1; i--)
    {
        if (is_line_with_odd_elems(matrix[i], col))
        {
            assign_array(matrix[end_index], matrix[i], col);
            assign_array(matrix[end_index - 1], line, col);
            end_index -= 2;
        }
        else
        {
            assign_array(matrix[end_index], matrix[i], col);
            end_index--;
        }
    }
    return row + c;
}

void print_matrix(matrix_t matrix, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            if (j == col - 1)
                printf("%d\n", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
}
