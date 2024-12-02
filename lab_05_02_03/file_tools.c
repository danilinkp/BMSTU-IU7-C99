#include "file_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EMPTY_FILE -1
#define EPS 1e-8

int file_len(FILE *f, int *n)
{
    rewind(f);
    double curr;
    *n = 0;
    if (fscanf(f, "%lf", &curr) == 1)
    {
        (*n)++;
        while (fscanf(f, "%lf", &curr) == 1)
            (*n)++;
        return EXIT_SUCCESS;
    }
    return EMPTY_FILE;
}

static double mean(FILE *f, int n)
{
    rewind(f);
    double sum = 0.0;
    double curr;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(f, "%lf", &curr) == 1)
            sum += curr;
    }
    return sum / n;
}

static double stddev(FILE *f, double avg, int n)
{
    rewind(f);
    double sum = 0.0;
    double curr;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(f, "%lf", &curr) == 1)
            sum += (curr - avg) * (curr - avg);
    }
    return sqrt(sum / n);
}

int three_sigma_rule(FILE *f, int n)
{
    double mu = mean(f, n);
    double sigma = stddev(f, mu, n);
    if (fabs(sigma) < EPS)
        return 0;
    rewind(f);
    double lower_bound = mu - 3 * sigma;
    double upper_bound = mu + 3 * sigma;
    double tmp;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(f, "%lf", &tmp) == 1)
        {
            if (tmp >= lower_bound && tmp <= upper_bound)
                count++;
        }
    }
    if (count * 100.0 / n < 99.73)
        return 0;
    return 1;
}
