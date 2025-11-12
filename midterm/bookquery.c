#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[]){
	int fd, id;
	char c;
	struct book record;
	int queryFlag; //0: list all books, 1: list available books

	if(argc < 2){
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(2);
	}

	do{
		printf("--bookquery--\n");
		printf("0: list of all books, 1: list of available books ) ");
		scanf("%d", &queryFlag);

		lseek(fd, 0, SEEK_SET);
		
		if(queryFlag != 0 && queryFlag != 1) {
                        printf("Please enter \"1\" or \"0\"\n\n");
                        continue;
                }

		printf("%4s %12s %12s %15s %18s %11s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		
		while(read(fd, (char *)&record, sizeof(record)) > 0){ //printing book list depending on queryFlag
			if(queryFlag == 0){
				printf("%4d %12s %12s %15d %18d", record.id, record.name, record.author, record.year, record.numofborrow);
				if(record.borrow == 1) printf("       True\n");
				else if(record.borrow == 0) printf("      False\n");	
			}

			else if(queryFlag == 1 && record.borrow == 1){
				printf("%4d %12s %12s %15d %18d       True\n", record.id, record.name, record.author, record.year, record.numofborrow);
			}
		}

		printf("\n");	
	} while (1);

	close(fd);
}
