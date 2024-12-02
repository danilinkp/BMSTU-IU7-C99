#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NOT_VALID_A 1
#define NOT_VALID_B 2
#define NOT_VALID_C 3
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
        return NOT_VALID_A;
    }
    printf("Enter b: ");
    if (scanf("%lf", &b) != 1 || b <= 0)
    {
        printf("Input error");
        return NOT_VALID_B;
    }
    printf("Enter angle at a large base: ");
    if (scanf("%lf", &c) != 1 || c <= 0)
    {
        printf("Input error");
        return NOT_VALID_C;
    }

    c = c * PI / 180.0;
    if (a > b)
        s = 0.25 * tan(c) * (a + b) * (a - b);
    else
        s = 0.25 * tan(c) * (a + b) * (b - a);
    printf("Trapezoid square: %.6lf", s);

    return EXIT_SUCCESS;
}
