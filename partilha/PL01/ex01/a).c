// 4 processos

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void){
    pid_t p, a;                     // 1 Processo
    p = fork();                     // 2 Processos
    a = fork();                     // 4 Processos
    printf("Computer Systems\n" );  // 4 Processos
    return 0;                       // 4 Processos
}