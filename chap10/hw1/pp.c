#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

void push(struct node *top, int data){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = top->next;
	top->next = new_node;
}

int pop(struct node *top){
	if(top->next == NULL){
		return -1;
	}
	struct node *rem_node = top->next;
	int rem_data = rem_node->data;
	top->next = rem_node->next;
	free(rem_node);
	return rem_data;
}

int main(){
	struct node *head;
	head = (struct node *)malloc(sizeof(struct node)); // node for starting stack
	head->data = 0; //dummy node data
	head->next = NULL; //dummy node pointer
	int input, output;

	while(scanf("%d", &input) == 1 && input > 0){
		push(head, input);
	}
	
	printf("Print stack\n");
	while((output = pop(head)) != -1){
		printf("%d\n", output);
	}
}
