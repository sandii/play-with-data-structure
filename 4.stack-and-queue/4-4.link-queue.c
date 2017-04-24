/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 24, 2017
*
* link queue
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
typedef struct {
	struct node* head;
	struct node* tail;
	int len ;
} LinkQueue;


struct node* createNode () {
	return (struct node*) malloc(sizeof(struct node));
}
Status init (LinkQueue* qp) {
	qp -> head = createNode();
	qp -> tail = qp -> head;
	qp -> len = 0;
	return OK;
}
int getLength (LinkQueue* qp) { return qp -> len; }
int isEmpty (LinkQueue* qp) { return qp -> len == 0 ? TRUE : FALSE; }
Status clear (LinkQueue* qp) {
	// todo
	return OK;
}

Status enQueue (LinkQueue* qp, ElemType n) {
	if (isFull(qp)) return ERROR;
	int tail = qp -> tail;
	qp -> data[tail] = n;
	qp -> tail = (tail == MAXSIZE - 1) ? 0 : tail + 1;
	(qp -> len)++;
	return OK;
}
ElemType deQueue (LinkQueue* qp) {
	if (isEmpty(qp)) return 0;
	struct node* curr = qp -> head -> next;
	ElemType n = curr -> data;
	qp -> head -> next = curr -> next;
	

	int head = qp -> head;
	ElemType n = qp -> data[head];
	qp -> head = (head == MAXSIZE - 1) ? 0 : head + 1;
	(qp -> len)--;
	return n;
}
ElemType getHead (LinkQueue* qp) {
	if (isEmpty(qp)) return 0;
	return qp -> head -> next -> data;
}


main () {
	LinkQueue queue;
	init(&queue);

	for (int i = 0; i < 30; i++) {
		Status rs = enQueue(&queue, i * 10);
		if (rs == ERROR) continue;
		printf("enQueue: %d\n", i * 10);
	}
	printf("is full: %d\n", isFull(&queue));
	printf("deQueue: %d\n", deQueue(&queue));
	printf("is full: %d\n", isFull(&queue));
	printf("head: %d\n", getHead(&queue));
	printf("len: %d\n", getLength(&queue));
	printf("deQueue: %d\n", deQueue(&queue));
	printf("deQueue: %d\n", deQueue(&queue));
	printf("is empty: %d\n", isEmpty(&queue));
	clear(&queue); printf("clear..\n");
	printf("is empty: %d\n", isEmpty(&queue));
}
