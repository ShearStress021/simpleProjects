#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;


void insertNodeFront(Node **head, int value){
	Node *n = malloc(sizeof * n);
	n->data = value;
	n->next = *head;
	*head = n;
}

void printLl(const Node *head){
	if(head == NULL){
		printf("Linked List empty\n");
	}

	while(head != NULL){
		printf("%d->", head->data);
		head = head->next;
	}
	head = NULL;

}



 
int main(){
	printf("Hello, World\n");

	return 0;
}
