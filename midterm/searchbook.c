#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "book.h"


int main(int argc, char *argv[]){
	int fd;
	struct book record;
	char bookname_buf[MAX];
	if(argc < 2){
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(2);
	}

	do{
		printf("input name of book ) ");
		scanf("%s", bookname_buf);

		lseek(fd, 0, SEEK_SET);
			
		int findFlag = 0;
		while(read(fd, (char *)&record, sizeof(record)) > 0){ //printing book list depending on queryFlag
			if(strcmp(bookname_buf, record.name) == 0){
				printf("%4s %12s %12s %15s %18s %11s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
				printf("%4d %12s %12s %15d %18d", record.id, record.name, record.author, record.year, record.numofborrow);
                                if(record.borrow == 1) printf("       True\n");
                                else if(record.borrow == 0) printf("      False\n");
				findFlag = 1;
			}
			else continue;
		}
		if(findFlag == 0) printf("not found book name : '%s'\n", bookname_buf);

		printf("\n");	
	} while (1);

	close(fd);
}
