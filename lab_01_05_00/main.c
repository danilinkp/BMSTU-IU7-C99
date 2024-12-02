#include <stdio.h>
#include <stdlib.h>

#define NOT_VALID_A 1
#define NOT_VALID_N 2

int exponentiation(int a, int n)
{
    int res = 1;
    for (int i = 0; i < n; i++)
        res *= a;
    return res;
}


int main(void)
{
    int a;
    int n;
    int res;

    printf("Enter the integer you want to exponentiate: ");
    if (scanf("%d", &a) != 1)
    {
        printf("Input error");
        return NOT_VALID_A;
    }

    printf("Enter the degree to which you want to raise: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Input error");
        return NOT_VALID_N;
    }

    res = exponentiation(a, n);

    printf("Result: %d", res);

    return EXIT_SUCCESS;
}
