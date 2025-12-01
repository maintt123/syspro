#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

void addq(struct node *head, struct node *tail, int data){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;
	tail->next = new_node;
}

int delete(struct node *head, struct node *tail){
	if(head->next == NULL){
		return -1;
	}
	
	struct node *rem_node = head->next;
	int rem_data = rem_node->data;
	
	head->next = rem_node->next;
	free(rem_node);

	return rem_data;
}

int main(){
	struct node *head = (struct node *)malloc(sizeof(struct node));
	int input, output;
	head->data = 0;
	head->next = NULL;
	struct node *tail = head;

	while(scanf("%d", &input) == 1){
		addq(head, tail, input);
		tail = tail->next;
	}
	
	printf("Print queue\n");

	while((output = delete(head, tail)) != -1){
		printf("%d\n", output);
	}
}
