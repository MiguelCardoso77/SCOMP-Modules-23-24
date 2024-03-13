#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void print(int init, int end) {
    for (int i = init; i <= end; i++) {
        printf("%d\n", i);
    }
}

int main(void) {
    pid_t child;
    int status;

    for (int i = 0; i < 6; i++) {
        child = fork();

        if (child == 0) {
            int start = i * 200000 + 1;
            int end = (i + 1) * 200000;
            print(child, end);
            exit(1);
        }
    }

    for (int i = 0; i < 6; i++) {
        wait(&status);
    }

    return 0;
}