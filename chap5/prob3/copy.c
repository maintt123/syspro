#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 1024

int main(int argc, char *argv[]){
	int fd1, fd2, n;
	char buf[BUFSIZE];
	long total = 0;

	//copy src dest (3 of argcs)
	if(argc != 3){
		fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
		exit(0);
	}

	if((fd1 = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(1);
	}

	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1){
                perror(argv[2]);
		exit(2);
        }
	
	while((n = read(fd1, buf, BUFSIZE)) > 0){
		write(fd2, buf, n);
	}

	close(fd1);
	close(fd2);
	exit(0);
}
