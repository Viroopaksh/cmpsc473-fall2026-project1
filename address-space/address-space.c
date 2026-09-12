#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void recurse(int depth, int max_depth)
{
    int local = depth;
    int *heap = malloc(sizeof *heap);
    if (heap == NULL) {
        perror("malloc");
        exit(1);
    }
    *heap = depth;

    printf("depth=%2d  &local=%p  heap=%p\n",
           depth, (void *)&local, (void *)heap);
    fflush(stdout);

    if (depth < max_depth) {
        recurse(depth + 1, max_depth);
    } else {
        printf("\nPID = %ld. Press ENTER after inspecting /proc/%ld/...\n",
               (long)getpid(), (long)getpid());
        fflush(stdout);
        (void)getchar();
    }

    free(heap);
}

int main(void)
{
    recurse(0, 9);
    return 0;
}
