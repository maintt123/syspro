#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAXARG 64
#define MAXLINE 256

int main(){
	char line[MAXLINE];
	char *args[MAXARG];
	char *token, *saveptr;
	int background;

	while(1){
		printf("Pls input cmd : ");

		if(fgets(line, sizeof(line), stdin) == NULL) break;

		line[strcspn(line, "\n")] = '\0';
		
		printf("[%d] Parent process start\n", getpid());

		if(strcmp(line, "Exit") == 0){
			printf("Parent process end\n");
			break;
		}

		background = 0;
		int len = strlen(line);
		if(len > 0 && line[len - 1] == '&'){
			background = 1;
			line[len - 1] = '\0';
		}


		int count = 0;
		token = strtok_r(line, " ", &saveptr);

		while(token != NULL && count < MAXARG - 1){
			args[count++] = token;
			token = strtok_r(NULL, " ", &saveptr);
		}

		args[count] = NULL;

		if(count == 0) continue;

		pid_t pid = fork();

		if(pid == 0){
				if(background){
				printf("[%d] child process start\n", getpid());
			}

			execvp(args[0], args);
			_exit(127);
		}
		
		int status;
		waitpid(pid, &status, 0);
		
		if(WIFEXITED(status) && WEXITSTATUS(status) == 127){
			printf("Parent process end\n");
			break;
		}

		if(!background){
			printf("SUCCESS\n\n");
		}
		else{
			printf("[%d] child process end %d\n", getpid(), pid);
			printf("SUCCESS\n\n");
		}
	}
	printf("Exit\n");
	return 0;
}
