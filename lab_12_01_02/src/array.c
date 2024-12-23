#include "array.h"
#include <math.h>

#define ARRAY_SUCCESS 0
#define ARRAY_NEED_MORE 1

static void reverse(int arr[], int start, int end)
{
    for (int i = 0; i < (end - start) / 2; i++)
    {
        int tmp = arr[start + i];
        arr[start + i] = arr[end - 1 - i];
        arr[end - 1 - i] = tmp;
    }
}

void left_shift(int arr[], int len, int k)
{
    int shift = k % len;

    reverse(arr, 0, shift);
    reverse(arr, shift, len);
    reverse(arr, 0, len);
}

static int is_full_square(int num)
{
    if (num < 0)
        return 0;
    int root = (int) sqrt(num);
    return root * root == num;
}

int filter_squares(int src[], int src_len, int dst[], int *dst_len)
{
    int n = 0;

    for (int i = 0; i < src_len; i++)
        if (is_full_square(src[i]))
            n++;

    if (n > *dst_len)
    {
        *dst_len = n;
        return ARRAY_NEED_MORE;
    }

    n = 0;
    for (int i = 0; i < src_len; i++)
        if (is_full_square(src[i]))
        {
            dst[n] = src[i];
            n++;
        }
    *dst_len = n;

    return ARRAY_SUCCESS;
}
