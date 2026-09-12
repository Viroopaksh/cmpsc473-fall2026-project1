#include <stdio.h>
#include <stdlib.h>

struct record {
    int id;
    int score;
};

static int total_scores(struct record *records, int n)
{
    int total = 0;
    for (int i = 0; i <= n; i++) {   /* BUG: diagnose with GDB before editing */
        total += records[i].score;
    }
    return total;
}

int main(void)
{
    const int n = 4;
    struct record *records = malloc((size_t)n * sizeof *records);
    if (records == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        records[i].id = 100 + i;
        records[i].score = 10 * (i + 1);
    }

    printf("total = %d\n", total_scores(records, n));
    free(records);
    return 0;
}
