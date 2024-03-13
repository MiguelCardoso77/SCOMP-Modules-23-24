#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void divisionByZero(int sig) {
    printf("Error: Division by zero\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <dividend> <divisor>\n", argv[0]);
        return 0;
    }

    int firstN = atoi(argv[1]);
    int secondN = atoi(argv[2]);
    double result;

    signal(SIGFPE, divisionByZero);

    if (secondN == 0) {
        divisionByZero(SIGFPE);
    } else {
        result = (double) firstN / secondN;
    }

    printf("Result: %f\n", result);

    return 0;
}