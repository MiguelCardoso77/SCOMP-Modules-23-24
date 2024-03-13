#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void signalHandler(int sig) {
    printf("Handled SIGUSR1. \n");
}

int main () {
    pid_t child;

    child = fork();

    if (child < 0) {
        perror("Fork failed.");
        exit(0);
    }

    if (child > 0) {
        // Parent
        sleep(2);
        kill(child, SIGUSR1);
    } else {
        // Child
        struct sigaction actChild;
        actChild.sa_handler = signalHandler;
        sigaction(SIGUSR1, &actChild, NULL);

        while(1) {
            pause();
        }
    }

    return 0;
}
