#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int counter = 0;
int shouldContinue = 1; 
int resetTimeInSec , signalTimeInSec;
pid_t childID[3];
void sigAlarmHandler(int sig) {
counter = 0;
 	printf("Times up!! Resetting the timer for %d seconds \n", resetTimeInSec);
 	alarm(resetTimeInSec);
}
void sigUser1Handler(int sig) {
 if(counter < 3)  {
counter++; 
printf("Total number of SIGUSR1 received: %d\n", counter);
}
else {
int i; 
for (i = 0; i < 3; i++) {
kill(childID[i] , 2);
}
shouldContinue = 0;
}
}
int main(int argc, char* argv[]) {
const int MIN_TIME_IN_SECS = 2; 
const int BUFFER_LEN = 64;
if(argc != 3) {
printf ("Invalid number arguments: %d\n", argc); 
return(EXIT_FAILURE);
}
resetTimeInSec = atoi(argv[1]); 
signalTimeInSec = atoi(argv[2]);
if((resetTimeInSec < MIN_TIME_IN_SECS) || (signalTimeInSec < MIN_TIME_IN_SECS)) 
{
printf ("the time you have entered is less than Min time\n"); 
return(EXIT_FAILURE);
}
struct sigaction act;
memset(&act, '\0', sizeof(act));
act.sa_handler = sigAlarmHandler; 
sigaction(SIGALRM, &act, NULL);
act.sa_handler = sigUser1Handler; 
sigaction(SIGUSR1, &act, NULL);
int i; 
for (i = 0; i < 3; i++) {
childID[i] = fork(); 
if (childID[i]== 0){
execl("signaller", "signaller", argv[2], NULL);
	}
}
alarm(resetTimeInSec);

while (shouldContinue) 	sleep(1);
printf("received three SIGUSR1 signals, tataaaaaa!\n");
return(EXIT_SUCCESS);
}
