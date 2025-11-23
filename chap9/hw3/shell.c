#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#define MAX_LENGTH 512
#define MAX_CMD 128


int parsing_cmd(char *commands, char *args[]){
	int count = 0;
	char *start = commands;

	for(int i = 0; commands[i] != '\0'; i++){
		if(commands[i]  == ';'){
			commands[i] = '\0';
			args[count++] = start;
			start = &commands[i+1];
		}
	}
	args[count++] = start;
	return count;
}

int execute_cmd(char *command){
	int status, pid;
	int len = strlen(command);
	if(command == NULL){
		return 1;
	}
	
	pid = fork();

	if(pid == 0){
		execl("/bin/sh", "sh", "-c", command, NULL);
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
	int fd, pid, cmd_count;
	char commands[MAX_LENGTH];
	char *args[MAX_CMD];

	while(1){
		printf("Pls input cmd : ");
		fgets(commands, sizeof(commands), stdin);
		
		cmd_count = parsing_cmd(commands, args);
		
		for(int i = 0; i < cmd_count; i++){
			execute_cmd(args[i]);
		}	
		printf("\n");
	}
}
