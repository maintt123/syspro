#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int child, pid, fd, status;

	pid = fork();
	
	if(pid == 0) {//when proccess is child proccess
		fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0600);
		dup2(fd, 1);
		close(fd);
		execvp(argv[2], &argv[2]);
		fprintf(stderr, "%s can't execute\n", argv[1]); //when child proccess can't execute the execvp(), printing fp() because execvp() returns it's error code,
	}
	else{
		child = wait(&status);
		printf("[%d] child proccess %d end\n", getpid(), child);
	}
}
