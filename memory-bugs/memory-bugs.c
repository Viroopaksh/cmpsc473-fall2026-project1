#include <stdio.h>
#include <stdlib.h>

/*
 * Each test contains one intentional memory error.  The helper routines are
 * deliberately ordinary-looking so that compiler warnings do not simply
 * identify the answer.  Students should diagnose the problems with a memory
 * checker and by reasoning about ownership, bounds, and initialization.
 */

static size_t array_length(void)
{
    /* Imagine that this value came from a configuration file or input. */
    return 4;
}

static void initialize_prefix(int *a, size_t count)
{
    for (size_t i = 0; i < count; ++i)
        a[i] = (int)(10 * (i + 1));
}

static void release_int(int *p)
{
    free(p);
}

static char *make_message(void)
{
    char *message = malloc(64);
    if (message == NULL)
        return NULL;

    snprintf(message, 64, "operating systems");
    return message;
}

static void test1(void)
{
    size_t n = array_length();
    int *a = malloc(n * sizeof *a);
    if (a == NULL)
        exit(EXIT_FAILURE);

    for (size_t i = 0; i <= n; ++i)
        a[i] = (int)(i * 10);

    printf("test1: %d\n", a[n - 1]);
    free(a);
}

static void test2(void)
{
    size_t n = array_length();
    int *a = malloc(n * sizeof *a);
    if (a == NULL)
        exit(EXIT_FAILURE);

    initialize_prefix(a, n - 1);
    printf("test2: %d\n", a[0] + a[1] + a[n - 1]);
    free(a);
}

static void test3(void)
{
    int *p = malloc(sizeof *p);
    if (p == NULL)
        exit(EXIT_FAILURE);

    *p = 473;
    release_int(p);
    printf("test3: %d\n", *p);
}

static void test4(void)
{
    char *message = make_message();
    if (message == NULL)
        exit(EXIT_FAILURE);

    printf("test4: %s\n", message);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <1|2|3|4>\n", argv[0]);
        return 2;
    }

    switch (argv[1][0]) {
    case '1': test1(); break;
    case '2': test2(); break;
    case '3': test3(); break;
    case '4': test4(); break;
    default:
        fprintf(stderr, "test must be 1, 2, 3, or 4\n");
        return 2;
    }

    return 0;
}
