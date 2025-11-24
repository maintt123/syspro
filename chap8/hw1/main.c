#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc > 3){
		fprintf(stderr, "How to use: %s -(option) [argv]\n", argv[0]);
		exit(1);
	}
	
	char option_number;
	if(!strcmp(argv[1], "-e")) option_number = 1;
	else if(!strcmp(argv[1], "-u")) option_number = 2;
	else if(!strcmp(argv[1], "-g")) option_number = 3;
	else if(!strcmp(argv[1], "-i")) option_number = 4;
	else if(!strcmp(argv[1], "-p")) option_number = 5;

	switch(option_number){
		case 1: 
			char **ptr;
			extern char **environ;
			for(ptr = environ; *ptr != 0; ptr++){
				if(argc == 3){
					int lengthOfEnv = strlen(argv[2]);
					if (strncmp(*ptr, argv[2], lengthOfEnv) == 0 && (*ptr)[lengthOfEnv] == '='){
       						printf("%s\n", *ptr);
						break;
					}
					else continue;
				}
				printf("%s \n", *ptr);
			}
			break;
		case 2:
			printf("My Realistic User ID: %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
			printf("My Valid User ID: %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
			break;
		case 3:
			printf("My Realistic Group ID: %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
			printf("My Valid Group ID: %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
			break;
		case 4:
			printf("my process number: [%d]\n", getpid());
			break;
		case 5:
			printf("my parent's process number: [%d]\n", getppid());
			break;
		default:
			fprintf(stderr, "option is not found");
			exit(2);
	}
	exit(0);
}
