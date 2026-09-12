#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int global_value = 100;

static void pause_here(const char *label)
{
    printf("[%s] pid=%ld: press ENTER to continue\n", label, (long)getpid());
    fflush(stdout);
    (void)getchar();
}

int main(void)
{
    int stack_value = 200;
    int *heap_value = malloc(sizeof *heap_value);
    if (heap_value == NULL) {
        perror("malloc");
        return 1;
    }
    *heap_value = 300;

    printf("BEFORE_FORK pid=%ld global=%p stack=%p heap=%p values=%d,%d,%d\n",
           (long)getpid(), (void *)&global_value, (void *)&stack_value,
           (void *)heap_value, global_value, stack_value, *heap_value);
    fflush(stdout);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        free(heap_value);
        return 1;
    }

    if (pid == 0) {
        printf("CHILD_AFTER_FORK pid=%ld ppid=%ld global=%p stack=%p heap=%p values=%d,%d,%d\n",
               (long)getpid(), (long)getppid(), (void *)&global_value,
               (void *)&stack_value, (void *)heap_value,
               global_value, stack_value, *heap_value);

        global_value = 101;
        stack_value = 201;
        *heap_value = 301;
        printf("CHILD_AFTER_WRITE values=%d,%d,%d\n",
               global_value, stack_value, *heap_value);
        pause_here("CHILD_BEFORE_EXEC");

        execl("./child", "child", (char *)NULL);
        perror("execl");
        _exit(127);
    }

    printf("PARENT_AFTER_FORK pid=%ld child=%ld global=%p stack=%p heap=%p values=%d,%d,%d\n",
           (long)getpid(), (long)pid, (void *)&global_value,
           (void *)&stack_value, (void *)heap_value,
           global_value, stack_value, *heap_value);
    pause_here("PARENT_WHILE_CHILD_EXISTS");

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        free(heap_value);
        return 1;
    }

    printf("PARENT_AFTER_WAIT values=%d,%d,%d child_status=%d\n",
           global_value, stack_value, *heap_value, status);
    free(heap_value);
    return 0;
}
