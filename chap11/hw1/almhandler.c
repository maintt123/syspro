#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

struct sigaction newact;
struct sigaction oldact;
void sigalrm_handler(int signo);
void my_signal(int signo, void (*func)(int));

int main(){
	my_signal(SIGALRM, sigalrm_handler);
	alarm(5);
	short i = 0;
	while(1){
		sleep(1);
		i++;
		printf("%d second\n", i);
	}
	printf("end\n");
}

void my_signal(int signo, void (*func)(int)){
	newact.sa_handler = func;
        sigfillset(&newact.sa_mask);

        sigaction(signo, &newact, &oldact);
}

void sigalrm_handler(int signo){
	printf("Wake up\n");
	sigaction(SIGALRM, &oldact, NULL);
	exit(0);
}
