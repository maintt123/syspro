#include <stdio.h>
#include <unistd.h>

int main(){
	int pid, gid;
	printf("PARENT: PID = %d GID = %d\n", getpid(), getpgrp()); //why getpdid using? -> this line doesn't contain child proccess, so it is only parent ps
	pid = fork();
	if(pid == 0){
		printf("CHILD: PID = %d GID = %d\n", getpid(), getpgrp());
	}
}
