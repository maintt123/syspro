#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[]){
	int fd, id;
	int bookId;
	struct book record;
	int borrowFlag;

	if(argc < 2){
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) == -1){
		perror(argv[1]);
		exit(2);
	}

	do{
		printf("--bookupdate--\n");
		printf("0 bookId: borrow book, , 1 bookId: return book ) ");
		scanf("%d %d", &borrowFlag, &bookId);
		if(borrowFlag != 0 && borrowFlag != 1){
			printf("Enter \"0\" or \"1\" bookId\n\n");
			continue;
		}

		lseek(fd, (long)(bookId - 1) * sizeof(record), SEEK_SET);
		read(fd, (char *)&record, sizeof(record));

		if(borrowFlag == 0){
			if(record.borrow == 0){
				record.borrow = 1;
				record.numofborrow++;
				lseek(fd, (long)-sizeof(record), SEEK_CUR);
				write(fd, (char *)&record, sizeof(record));
				printf("You've got bellow book..\n");
				printf("%4s %12s %12s %15s %18s %11s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
				printf("%4d %12s %12s %15d %18d       True\n\n", record.id, record.name, record.author, record.year, record.numofborrow);
			}
			else if(record.borrow == 1){
				printf("You cannot borrow below book since it has been booked.\n");
				printf("%4s %12s %12s %15s %18s %11s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
                                printf("%4d %12s %12s %15d %18d       True\n\n", record.id, record.name, record.author, record.year, record.numofborrow);
			}
		}
		else if(borrowFlag == 1 && (record.borrow == 1)){
			record.borrow = 0;
			lseek(fd, (long)-sizeof(record), SEEK_CUR);
                        write(fd, (char *)&record, sizeof(record));
			printf("You've returned bellow book..\n");
			printf("%4s %12s %12s %15s %18s %11s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
                        printf("%4d %12s %12s %15d %18d      False\n\n", record.id, record.name, record.author, record.year, record.numofborrow);
		}	
	} while (1);
	
	close(fd);
}
