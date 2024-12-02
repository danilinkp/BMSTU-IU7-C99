#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double g(void)
{
    int n = 0;
    double x, y;
    double s = 0.0;
    printf("Enter x:\n");
    if (scanf("%lf", &x) != 1 || x < 0)
    {
        printf("Input Error");
        return -1;
    }
    while (x >= 0)
    {
        n++;
        y = exp(0.5 * log(x + n));
        s += y;
        if (scanf("%lf", &x) != 1)
        {
            printf("Input Error");
            return -1;
        }
    }
    s /= n;
    return s;
}

int main(void)
{
    double res = g();

    if (res < 0)
        return EXIT_FAILURE;

    printf("Result: %.6lf", res);
    return EXIT_SUCCESS;
}
