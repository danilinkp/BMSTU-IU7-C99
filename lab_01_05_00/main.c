#include <stdio.h>
#include <math.h>

int exponentiation(int a, int n)
{
    int res = 1;

    for (int i = 0; i < n; i++)
    {
        res *= a;
    }

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
        return 1;
    }

    printf("Enter the degree to which you want to raise: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Input error");
        return 2;
    }

    res = exponentiation(a, n);

    printf("Result: %d", res);

    return 0;
}