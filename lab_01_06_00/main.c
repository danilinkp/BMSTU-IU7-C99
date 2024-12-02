#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NOT_VALID_A 1
#define NOT_VALID_B 2
#define NOT_VALID_C 3
#define SQUARE_ERROR 4
#define EPS 1e-8
#define PI (2.0 * asin(1.0))

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int triangle_definition(double a, double b, double c)
{
    double angle_a, angle_b, angle_c;

    angle_a = acos((b * b + c * c - a * a) / (2.0 * b * c)) * (180.0 / PI);
    angle_b = acos((a * a + c * c - b * b) / (2.0 * a * c)) * (180.0 / PI);
    angle_c = acos((a * a + b * b - c * c) / (2.0 * a * b)) * (180.0 / PI);

    if (fabs(angle_a - 90) < EPS || fabs(angle_b - 90) < EPS || fabs(angle_c - 90) < EPS)
        return 1;

    if (angle_a > 90 || angle_b > 90 || angle_c > 90)
        return 2;

    return 0;
}

int main(void)
{
    double xa, ya, xb, yb, xc, yc;

    printf("Enter coordinates of A (xA, yA): ");
    if (scanf("%lf%lf", &xa, &ya) != 2)
    {
        printf("Input error");
        return NOT_VALID_A;
    }
    printf("Enter coordinates of B (xB, yB): ");
    if (scanf("%lf%lf", &xb, &yb) != 2)
    {
        printf("Input error");
        return NOT_VALID_B;
    }
    printf("Enter coordinates of C (xC, yC): ");
    if (scanf("%lf%lf", &xc, &yc) != 2)
    {
        printf("Input error");
        return NOT_VALID_C;
    }

    double s = 0.5 * fabs((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));

    if (s <= EPS)
    {
        printf("Треугольника не существует");
        return SQUARE_ERROR;
    }

    double ab, bc, ca;
    ab = distance(xa, ya, xb, yb);
    bc = distance(xb, yb, xc, yc);
    ca = distance(xc, yc, xa, ya);

    int res = triangle_definition(ab, bc, ca);

    printf("Res: %d", res);
    return EXIT_SUCCESS;
}
