/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 24, 2017
*
* sequence stack
*
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
	int top;	// -1 when stack is empty
} SqStack;


int getLength (SqStack* sp) { return sp -> top + 1; }
int isEmpty (SqStack* sp) { return getLength(sp) == 0 ? TRUE : FALSE; }
int isFull (SqStack* sp) { return getLength(sp) == MAXSIZE ? TRUE : FALSE; }
Status init (SqStack* sp) { sp -> top = -1; return OK; }
Status clear (SqStack* sp) { return init(sp); }

Status push (SqStack* sp, ElemType n) {
	if (isFull(sp)) return ERROR;
	(sp -> top)++;
	sp -> data[sp -> top] = n;
	return OK;
}
ElemType pop (SqStack* sp) {
	if (isEmpty(sp)) return 0;
	(sp -> top)--;
	return sp -> data[sp -> top + 1];
}
ElemType getTop (SqStack* sp) {
	if (isEmpty(sp)) return 0;
	return sp -> data[sp -> top];
}


main () {
	SqStack stack;
	init(&stack);

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
