#include <stdio.h>
#include <stdlib.h>

struct pair {
    int x;
    int y;
};

static void update(int *p, struct pair *q)
{
    *p += 10;
    q->y = *p;
}

int main(void)
{
    int a[4] = {10, 20, 30, 40};
    int *p = a;
    int **pp = &p;

    struct pair local = {1, 2};
    struct pair *heap = malloc(sizeof *heap);
    if (heap == NULL)
        return 1;

    heap->x = 5;
    heap->y = 6;

    update(&a[1], heap);

    printf("%d %d %d\n", *p, *(*pp + 1), heap->y);
    printf("local = {%d, %d}\n", local.x, local.y);

    /* TODO (Part I): dynamically allocate an array of 100 struct pair
       objects, initialize element i to {i, 2*i}, and free it. */

    free(heap);
    return 0;
}
