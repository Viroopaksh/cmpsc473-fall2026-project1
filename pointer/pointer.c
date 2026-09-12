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
    struct pair *arr= malloc(100 * sizeof *arr);                   /* (a) no hard-coded struct size */

    if (arr== NULL) {
        free(heap);
        return 1;
    }

    for (int i= 0; i< 100; i++) { arr[i].x= i;                   /* (b) initialized {i, 2*i} */
    arr[i].y= 2 * i;
    }
    
    free(arr);                                                   /* (c) with exactly one free */

    free(heap);
    return 0;
}
