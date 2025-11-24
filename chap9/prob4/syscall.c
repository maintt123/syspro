#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

int mysystem(const char *cmdstring){
	int pid, status;
	if(cmdstring == NULL){
		return 1;
	}
	pid = fork();

	if(pid == -1){ //fail to making process
		return -1;
	}
	if(pid == 0){
		execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
		_exit(127);
	}
	
	do{
		if(waitpid(pid, &status, 0) == -1){
			if(errno != EINTR){
				return -1;
			}
		}
		else return status;
		
	} while(1);

}


int main(){
	int status;
	
	if((status = mysystem("date")) < 0){
		perror("system() error");
	}
	printf("end code %d\n", WEXITSTATUS(status));

	if((status = mysystem("hello")) < 0){
                perror("system() error");
        }
        printf("end code %d\n", WEXITSTATUS(status));

	if((status = mysystem("who; exit 44")) < 0){
                perror("system() error");
        }
        printf("end code %d\n", WEXITSTATUS(status));
}

