#include <stdio.h>
#include "stats.h"

int main(void)
{
    double values[] = {4.0, 7.5, 2.0, 9.5, 3.0};
    int n = (int)(sizeof values / sizeof values[0]);

    printf("mean = %.2f\n", mean(values, n));
    printf("max  = %.2f\n", maximum(values, n));
    return 0;
}
