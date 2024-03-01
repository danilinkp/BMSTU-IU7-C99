#include <math.h>
#include <stdio.h>
#define EPS 1e-8

int main(void)
{
    double v1, t1;
    double v2, t2;
    double v, t;

    printf("Enter v first and t first: ");
    if (scanf("%lf%lf", &v1, &t1) != 2 || v1 <= 0)
    {
        printf("Input error");
        return 1;
    }

    printf("Enter v second and t second: ");
    if (scanf("%lf%lf", &v2, &t2) != 2 || v2 <= 0)
    {
        printf("Input error");
        return 2;
    }

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("Volume is: %.6lf\n", v);
    printf("Temperature is: %.6lf\n", t);
    
    return 0;
}