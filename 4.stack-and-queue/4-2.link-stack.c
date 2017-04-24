/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 24, 2017
*
* link stack
*
*/

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

struct node {
	ElemType data;
	struct node* next;
};
typedef struct node* LinkStack;


int isEmpty (LinkStack* sp) { return *sp == NULL ? TRUE : FALSE; }
int getLength (LinkStack* sp) {
	int len = 0;
	struct node* np = *sp;
	while (np != NULL) {
		len++;
		np = np -> next;
	}
	return len;
}

Status clear (LinkStack* sp) {
	struct node* np = *sp;
	*sp = NULL;
	while (np != NULL) {
		struct node* next = np -> next;
		free(np);
		np = next;
	}
	return OK;
}
Status push (LinkStack* sp, ElemType n) {
	struct node* np = (struct node*) malloc(sizeof(struct node));
	np -> data = n;
	np -> next = *sp;
	*sp = np;
	return OK;
}
ElemType pop (LinkStack* sp) {
	if (isEmpty(sp)) return 0;
	ElemType n = (*sp) -> data;
	struct node* next = (*sp) -> next;
	free(*sp);
	*sp = next;
	return n;
}
ElemType getTop (LinkStack* sp) {
	if (isEmpty(sp)) return 0;
	return (*sp) -> data;
}


main () {
	LinkStack stack = NULL;
	

	for (int i = 0; i < 10; i++) {
		push(&stack, i * 10);
		printf("push: %d\n", i * 10);
	}
	printf("pop: %d\n", pop(&stack));
	printf("top: %d\n", getTop(&stack));
	printf("len: %d\n", getLength(&stack));
	printf("pop: %d\n", pop(&stack));
	printf("pop: %d\n", pop(&stack));
	printf("is empty: %d\n", isEmpty(&stack));
	clear(&stack); printf("clear..\n");
	printf("is empty: %d\n", isEmpty(&stack));
}
