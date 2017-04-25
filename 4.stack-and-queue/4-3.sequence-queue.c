/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 24, 2017
*
* sequence queue
* - head indexes head
* - tail indexes the empty position that ready to contain next data
* - so when queue is empty, head and tail index the same empty position
* - when queue is full, head and tail index the same head position
*/

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20


typedef int ElemType;
typedef int Status;

typedef struct {
	ElemType data[MAXSIZE];
	int head;
	int tail;
	int len;
} SqQueue;

Status init (SqQueue* qp) {
	qp -> head = 0;
	qp -> tail = 0;
	qp -> len = 0;
	return OK;
}
Status clear (SqQueue* qp) { return init(qp); }
int getLength (SqQueue* qp) { return qp -> len; }
int isEmpty (SqQueue* qp) { return qp -> len == 0 ? TRUE : FALSE; }
int isFull (SqQueue* qp) { return qp -> len == MAXSIZE ? TRUE : FALSE; }

Status enQueue (SqQueue* qp, ElemType n) {
	if (isFull(qp)) return ERROR;
	int tail = qp -> tail;
	qp -> data[tail] = n;
	qp -> tail = (tail == MAXSIZE - 1) ? 0 : tail + 1;
	(qp -> len)++;
	return OK;
}
ElemType deQueue (SqQueue* qp) {
	if (isEmpty(qp)) return 0;
	int head = qp -> head;
	ElemType n = qp -> data[head];
	qp -> head = (head == MAXSIZE - 1) ? 0 : head + 1;
	(qp -> len)--;
	return n;
}
ElemType getHead (SqQueue* qp) {
	if (isEmpty(qp)) return 0;
	return qp -> data[qp -> head];
}


main () {
	SqQueue queue;
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
