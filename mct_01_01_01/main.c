#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define X_ERR 1
#define EPS_ERR 2

double f(double x)
{
    return sin(x) * x;
}


double s(double x, double eps)
{
    int i = 2;
    double a_i = pow(x, 5) / (i * (i + 1));
    double s = a_i;
    printf("|  N  |  a_i  | s_temp |\n");
    printf("|-----|-------|--------|\n");
    printf("|%5.d|%7.2lf|%8.2lf|\n", i - 1, a_i, s);
    while (fabs(a_i) < eps)
    {
        a_i *= x * x / (i + 1);
        s += -a_i;
        printf("|%5.d|%7.2lf|%7.2lf|\n", i, a_i, s);
        i += 1;
    }
    printf("|-----|-------|--------|\n");
    return s;
}

int main(void)
{
    double x;
    double eps;

    printf("Enter x: ");
    if (scanf("%lf", &x) != 1)
        return X_ERR;
    printf("Enter Eps: ");
    if (scanf("%lf", &eps) != 1)
        return EPS_ERR;
    double s_x = s(x, eps);
    double f_x = f(x);
    printf("f_x = %-.2lf\n", f_x);
    printf("s_x = %e\n", s_x);
    return EXIT_SUCCESS;
}