#include "stats.h"

double mean(const double *values, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += values[i];
    return sum / n;
}

double maximum(const double *values, int n)
{
    double max = values[0];
    for (int i = 1; i < n; i++)
        if (values[i] > max)
            max = values[i];
    return max;
}
