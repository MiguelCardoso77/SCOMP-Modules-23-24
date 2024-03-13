#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void M(char* print){
    printf("%s\n", print);
}

int main (void) {
    pid_t father = getpid();
    pid_t child;

    int i;
    for (i = 0; i < 2; i++) {
        printf("Iteration %d\n", i + 1);
        if (i == 1 && getpid() == father) {
            sleep(1);
        } else {
            child = fork();
        }

        if (child > 0) {
            M("A");
        } else {
            M("B");
            child = fork();
            
            if (child > 0) {
                M("A");
            }
        }
    }

    return 0;
}