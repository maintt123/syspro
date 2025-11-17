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
	int queryFlag; //0: list all books, 1: list available books

	if(argc < 2){
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(2);
	}

	int i = 0;
        while(read(fd, (char *)&record, sizeof(record)) > 0){ //storing entire record in buffer of book array
                buffer[i] = record;
		i++;
        }

	for(int j = 0; j < i; j++){ //sorting buffer of book array as descending order of number of borrow 
                for(int k = j; k < i; k++){
                        if(buffer[j].numofborrow <= buffer[k].numofborrow){
                                tmp = buffer[j];
                                buffer[j] = buffer[k];
                                buffer[k] = tmp;
                        }
                }
        }

	do{
		printf("--bookquery--\n");
		printf("0: list of all books, 1: list of available books ) ");
		scanf("%d", &queryFlag);
		
		if(queryFlag != 0 && queryFlag != 1) {
                        printf("Please enter \"1\" or \"0\"\n\n");
                        continue;
                }

		printf("%4s %12s %12s %15s %18s %11s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		
		int z = 0;
		while(z < i){ //printing book list depending on queryFlag
			if(queryFlag == 0){
				printf("%4d %12s %12s %15d %18d", buffer[z].id, buffer[z].name, buffer[z].author, buffer[z].year, buffer[z].numofborrow);
				if(buffer[z].borrow == 1) printf("       True\n");
				else if(buffer[z].borrow == 0) printf("      False\n");	
			}

			else if((queryFlag == 1) && (buffer[z].borrow == 1)){
				printf("%4d %12s %12s %15d %18d       True\n", buffer[z].id, buffer[z].name, buffer[z].author, buffer[z].year, buffer[z].numofborrow);
			}
			z++;
		}

		printf("\n");	
	} while (1);

	close(fd);
}
