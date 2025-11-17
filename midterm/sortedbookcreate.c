#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[]){
	int fd;
	struct book record;
	struct book tmp;
	struct book buffer[MAX];

	if(argc < 2){
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) == -1){
		perror(argv[1]);
		exit(2);
	}

	int i = 0;
        while(read(fd, (char *)&record, sizeof(record)) > 0){ //storing entire record in buffer of book array
                buffer[i] = record;
		i++;
        }

	for(int j = 0; j < i - 1; j++){ //bubble sorting in buffer of book array as year
                for(int k = 0; k < i - 1 - j; k++){
                        if(buffer[k].year < buffer[k+1].year){
                                tmp = buffer[k];
                                buffer[k] = buffer[k+1];
                                buffer[k+1] = tmp;
                        }
                }
        }

	lseek(fd, 0, SEEK_SET);
	for(int l = 0; l < i; l++){
		record = buffer[l];
		write(fd, (char *)&record, sizeof(record));	
	}

	close(fd);
}
