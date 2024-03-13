#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    pid_t p, a;
    int status;

    p = fork();
    if (p == 0) {
        printf("I am the first child, ");
        printf("%d\n", getpid());
        sleep(5);
        exit(1);
    }

    a = fork();
    if (a == 0) {
        printf("I am the second child, ");
        printf("%d\n", getpid());
        exit(2);
    }

    printf("I am the father, ");
    printf("%d\n", getpid());

    waitpid(p, &status, 0);
    if (WIFEXITED(status)) {
        printf("First child terminated %d \n", WEXITSTATUS(status));
    }
    
    waitpid(a, &status, 0);
    if (WIFEXITED(status)) {
        printf("Second child terminated %d \n", WEXITSTATUS(status));
    }

    return 0;
}