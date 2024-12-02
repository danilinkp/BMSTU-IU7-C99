#include "array.h"

int is_prime(int n)
{
    if (n <= 1)
    {
        return 0;
    }
    for (int i = 2; i <= n / 2; ++i)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

size_t make_array(matrix_t matrix, array_t arr, size_t row, size_t col)
{
    size_t c = 0;
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            if (is_prime(matrix[i][j]))
            {
                arr[c] = matrix[i][j];
                c++;
            }
    return c;
}

void reverse_array(array_t arr, size_t len)
{
    int buff;
    for (size_t i = 0; i < len / 2; i++)
    {
        buff = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = buff;
    }
}

