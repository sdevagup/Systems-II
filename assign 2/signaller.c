#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <signal.h> 
#include <unistd.h> 
#include <sys/types.h>

int maxSignalTime; 
int shouldContinue = 1; 
const int MIN_TIME_IN_SECS = 2;

void sigAlarmHandler(int sig) {
	kill(getppid(), 10); 
	printf("child %d signalling parent %d\n", getpid(), getppid());
	alarm(rand() % maxSignalTime + 1);
}

void sigIntHandler(int sig) {
	shouldContinue = 0;
}
int main(int argc, char* argv[]) {
 	if(argc == 0) {
		printf("No command argument received\n");
		exit(EXIT_FAILURE);
	}
	maxSignalTime = atoi (argv[1]); 
	if(maxSignalTime < MIN_TIME_IN_SECS) {
	printf("Max Signal Time is incorrect\n"); 
	exit(EXIT_FAILURE);
	}
	struct sigaction act; 
	memset (&act, '\0', sizeof(act)); 
	act.sa_handler = sigAlarmHandler; 
	sigaction(SIGALRM, &act, NULL); 
	act.sa_handler = sigIntHandler; 
	sigaction(SIGINT, &act, NULL);
	
	srand(getpid());
	alarm(rand() % maxSignalTime + 1);
	while(shouldContinue)  sleep(1);
	printf("Terminated Child : %d\n",getpid());
	return(EXIT_SUCCESS);
}
