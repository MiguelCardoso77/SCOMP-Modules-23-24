#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void handleSIGUSR1(int signo){
	char output [100];
	int length;
	int number;
	
	FILE *file = fopen("data.txt", "r");
    if (file) {
        fscanf(file, "%d", &number);
		length = snprintf(output, 100, "Parent: Read number from file: %d\n", number);
		write (STDOUT_FILENO, output, length + 1);
        fclose(file);
    } else {
        length = snprintf(output, 100, "Parent: File 'data.txt' not found.\n");
		write(STDOUT_FILENO, output, length + 1);;
    }
}

void handleSIGUSR2(int signo){
	char output [100];
	int length;
	
	srand(time(NULL)); 
	int new_number = rand();
    FILE *file = fopen("data.txt", "w");
    
    if (file) {
        fprintf(file, "%d", new_number);
        fclose(file);
    } else {
        length = snprintf(output, 100, "Child: Error opening file 'data.txt'.\n");
		write(STDOUT_FILENO, output, length + 1);;
    }
}

int main(){
	pid_t pid;
	sigset_t mask, pending;
	struct sigaction act;
	
	memset(&act, 0, sizeof(struct sigaction));
	sigfillset(&act.sa_mask);           /* All signals blocked */
	sigdelset(&act.sa_mask, SIGUSR1);   /* Unblock SIGUSR1 */
	sigdelset(&act.sa_mask, SIGUSR2);   /* Unblock SIGUSR2 */

	pid = fork();
	
	if (pid > 0) {
		act.sa_handler = handleSIGUSR1;
		sigaction(SIGUSR1, &act, NULL);
		
		sigprocmask(SIG_BLOCK, &mask, 0);
		
		while (1) {
	    	sigpending(&pending);
			if(sigismember(&pending, SIGINT)){
				exit(0);
			}
			pause();
			sleep(1);
			kill(pid, SIGUSR2);	
		}
		sigprocmask(SIG_UNBLOCK, &mask, 0);
        
	} else {
		act.sa_handler = handleSIGUSR2;
		sigaction(SIGUSR2, &act, NULL);
		
		sigprocmask(SIG_BLOCK, &mask, 0);
		
		while (1) {
			sigpending(&pending);
			if(sigismember(&pending, SIGINT)){
				exit(0);
			}
			kill(getppid(), SIGUSR1);
			pause();
		}	
		sigprocmask(SIG_UNBLOCK, &mask, 0);	

	}
	
	return 0;
}