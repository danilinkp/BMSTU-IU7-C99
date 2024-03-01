#include <math.h>
#include <stdio.h>
#define PI (2.0 * asin(1.0))
#define EPS 1e-8

int main(void)
{
    double a, b;
    double c;
    double s;

    printf("Enter a: ");
    if (scanf("%lf", &a) != 1 || a <= 0)
    {
        printf("Input error");
        return 1;
    }
    printf("Enter b: ");
    if (scanf("%lf", &b) != 1 || b <= 0)
    {
        printf("Input error");
        return 2;
    }
    printf("Enter angle at a large base: ");
    if (scanf("%lf", &c) != 1 || c <= 0)
    {
        printf("Input error");
        return 3;
    }

    if (fabs(c - 90.0) <= EPS)
    {
        s = a * b;
    }
    else
    {
        c = c * PI / 180.0;
        if (a > b)
        {
            s = 0.25 * tan(c) * (a + b) * (a - b);
        }
        else
        {
            s = 0.25 * tan(c) * (a + b) * (b - a);
        }
    }

    printf("Trapezoid square: %.6lf", s);

    return 0;
}