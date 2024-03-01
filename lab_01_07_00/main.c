#include <stdio.h>
#include <math.h>

double f(double x)
{
    return exp(x);
}

double s(double x, double eps)
{
    double s_x = 1.0;
    double x_i = 1.0;
    int n = 1;

    while (fabs(x_i) > eps)
    {
        x_i *= x / n;
        s_x += x_i;
        n++;
    }
    return s_x;
}

double absolute(double f_x, double s_x)
{
    return fabs(f_x - s_x);
}

double relative(double f_x, double s_x)
{
    return fabs(f_x - s_x) / fabs(f_x);
}

int main(void)
{
    double x;
    double eps;
    double s_x, f_x, d_a, d_r; 
    
    printf("Input x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Not valid x");
        return 1;
    }

    printf("Input eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0 || eps > 1)
    {
        printf("Not valid eps");
        return 2;
    }
    
    f_x = f(x);
    s_x = s(x, eps);
    d_a = absolute(f_x, s_x);
    d_r = relative(f_x, s_x);

    printf("Approximate value: %.6lf\n", s_x);
    printf("Exact value: %.6lf\n", f_x);
    printf("Absolute error: %.6lf\n", d_a);
    printf("Relative error: %.6lf\n", d_r);

    return 0;
}
