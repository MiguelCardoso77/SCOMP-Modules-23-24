#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handleSIGUSR1(int signo, siginfo_t* sinfo, void *context) {
	char output [100];
	int length;
	length = snprintf(output, 100, "I captured a SIGUSR1 sent by the process with PID %d\n", sinfo -> si_pid);
	write(STDOUT_FILENO, output, length + 1);
}

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid > 0) {
        sleep(2);
        kill(pid, SIGUSR1);
        wait(&status);
    } else {
        struct sigaction act;
        
        memset(&act, 0, sizeof(struct sigaction));
        act.sa_sigaction = handleSIGUSR1;
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, NULL);
        
        pause();
    }

    return 0;
}