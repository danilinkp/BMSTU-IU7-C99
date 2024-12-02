#include <stdio.h>
#include <stdlib.h>

#define NOT_VALID_V1_T1 1
#define NOT_VALID_V2_T2 2

int main(void)
{
    double v1, t1;
    double v2, t2;
    double v, t;

    printf("Enter v first and t first: ");
    if (scanf("%lf%lf", &v1, &t1) != 2 || v1 <= 0)
    {
        printf("Input error");
        return NOT_VALID_V1_T1;
    }

    printf("Enter v second and t second: ");
    if (scanf("%lf%lf", &v2, &t2) != 2 || v2 <= 0)
    {
        printf("Input error");
        return NOT_VALID_V2_T2;
    }

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("Volume is: %.6lf\n", v);
    printf("Temperature is: %.6lf\n", t);

    return EXIT_SUCCESS;
}
