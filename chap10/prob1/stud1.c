#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	char name[20];
};

int main(){
	struct student *ptr;
	int n, i;

	printf("How many student do you enter? ");
	scanf("%d", &n);
	if(n <= 0){
		fprintf(stderr, "error: invalid number of students entered\n");
		fprintf(stderr, "end program\n");
		exit(1);
	}
	
	ptr = (struct student *)malloc(n*sizeof(struct student));
	if(ptr == NULL){
		perror("malloc");
		exit(2);
	}

	printf("enter %d student numbers and names\n", n);
	for(i = 0; i < n; i++){
		scanf("%d %s", &ptr[i].id, ptr[i].name);
	}

	printf("\n* student Information(reverse order) *\n");
	
	for(i = n-1; i >= 0; i--)
		printf("%d %s\n", ptr[i].id, ptr[i].name);

	printf("\n");
	free(ptr);
	exit(0);
	
}
