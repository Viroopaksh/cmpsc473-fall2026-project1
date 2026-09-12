#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int child_global = 900;

int main(void)
{
    int child_stack = 901;
    int *child_heap = malloc(sizeof *child_heap);
    if (child_heap == NULL) {
        perror("malloc");
        return 1;
    }
    *child_heap = 902;

    printf("AFTER_EXEC pid=%ld global=%p stack=%p heap=%p values=%d,%d,%d\n",
           (long)getpid(), (void *)&child_global, (void *)&child_stack,
           (void *)child_heap, child_global, child_stack, *child_heap);
    printf("[CHILD_AFTER_EXEC] press ENTER to exit\n");
    fflush(stdout);
    (void)getchar();

    free(child_heap);
    return 0;
}
