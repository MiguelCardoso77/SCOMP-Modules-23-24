#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signalHandler(int sig) {
    printf("I got SIGSEGV. \n");
    exit(0);
}

int main () {
    int a;

    signal(SIGSEGV, signalHandler);

    a = *(int *) 0;

    return 0;
}
