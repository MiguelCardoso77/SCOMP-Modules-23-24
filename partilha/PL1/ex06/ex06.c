#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void) {
    int status;
    int size = 100000;
    int data[size];
    int result[size];

    for (int i = 0; i < size; i++) {
        data[i] = rand() % 10 + 1;  // Preencher array data com valores aleatórios entre 1 e 10
    }

    pid_t child = fork();
    if (child > 0) {

        for (int i = size / 2; i < size; i++) {
			result[i] = data[i] * 4 + 20;
		}
		
		waitpid(child, &status, 0);
		
		for (int i = size / 2; i < size; i ++) {
			printf("Posição %d, Valor: %d\n", i, result[i]);
		}

    } else {

        for (int i = 0; i < size / 2; i++) {
			result[i] = data[i] * 4 + 20;
		}
		
		for (int i = 0; i < size / 2; i ++) {
			printf("Posição %d, Valor: %d\n", i, result[i]);
		}
        exit(1);
        
    }

    return 0;
}