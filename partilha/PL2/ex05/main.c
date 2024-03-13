#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

void sigusr1Handler() {}
void sigusr2Handler() {}

int main() {
    printf("Enter a sentence: ");
    fflush(stdout);

    signal(SIGUSR1, sigusr1Handler);
    signal(SIGUSR2, sigusr2Handler);

    fd_set descriptor;
    FD_ZERO(&descriptor);
    FD_SET(STDIN_FILENO, &descriptor);

    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int ready = select(STDIN_FILENO + 1, &descriptor, NULL, NULL, &timeout);

    if (ready == -1) {
        perror("Error!");
        exit(0);
    } else if (ready == 0) {
        printf("\nYou are too slow!\n");
    } else {
        char sentence[100];
        fgets(sentence, sizeof(sentence), stdin);
        printf("\nYou entered: %s", sentence);
    }
    return 0;
}