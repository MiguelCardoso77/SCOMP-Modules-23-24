#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define numberSearch 50000

void process(int start, int end, int* array, int child) {
    for (int i = start; i <= end; i++) {
        if (*(array + i) == numberSearch) {
			printf("%d Found in Position %d\n", numberSearch, i);
			exit(child);
		}
    }
    exit(0);
}

int main(void) {
    int array[100000];

    for (int i = 0; i < 100000; i++) {
        array[i] = i;
    }

    pid_t pids[5];
	int status;

    for (int i = 0; i < 5; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
			int start = i * 20000;
			int end = (i + 1) * 20000;
			process(start, end, array, i);
		}
    }

    pid_t pidEnd;

    for (int i = 0; i < 5; i++){
		pidEnd = waitpid(pids[i], &status, 0);
		
		if(WIFEXITED(status)){
		
			if (WEXITSTATUS(status) != 0) {
				printf("PID %d, Child Number: %d NUMBER FOUND\n", pidEnd, WEXITSTATUS(status));
			} else {
				printf("PID %d, NUMBER NOT FOUND!\n", pidEnd);
			}
        }
	}

    return 0;
}