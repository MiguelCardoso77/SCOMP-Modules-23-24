#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void){
    pid_t p, a;                     // 1 Processo

    p = fork();                     // 2 Processos
    if (p == -1) {
        perror("Fork Failed");
        return 1;
    }

    a = fork();                     // 4 Processos
    if (a == -1) {
        perror("Fork Failed");
        return 1;
    }

    printf("Computer Systems\n" );
    return 0;
}