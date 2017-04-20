/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 17, 2017
*
* link list
* - position 0 is head node, store no data
* - LinkList is actually a pointer to struct Node
*/

#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0


typedef int Status;
typedef int ElemType;

struct Node {
	ElemType data;
	struct Node* next;
};
typedef struct Node* LinkList;





LinkList newNode () {
	return (LinkList) malloc(sizeof(struct Node));
}

void addNode (LinkList target, ElemType n) {
	LinkList p = newNode();
	p -> data = n;
	p -> next = target -> next;
	target -> next = p;
}

Status delNode (LinkList prev) {
	LinkList curr = prev -> next;
	if (curr == NULL) return ERROR;
	prev -> next = curr -> next;
	free(curr);
	return OK;
}

int getLength (LinkList list) {
	int len = 0;
	for (LinkList p = list -> next; p != NULL; p = p -> next) {
		len++;
	}
	return len;
}

Status insertAtHead (LinkList list, ElemType n) {
	addNode(list, n);
	return OK;
}

Status insertAtTail (LinkList list, ElemType n) {
	LinkList target = list -> next;
	while (target -> next != NULL) {
		target = target -> next;
	}
	addNode(target, n);
	return OK;
}

Status insert (LinkList list, int i, ElemType n) {
	i = i < 1 ? 1 : i;	// i is too small, insert at head

	LinkList target = list;
	for (int j = 0; j < i; j++) {
		if (target -> next == NULL) break; // i is too large, insert at tail
		target = target -> next;
	}
	addNode(target, n);
	return OK;
}

Status traverse (LinkList list) {
	for (LinkList p = list -> next; p != NULL; p = p -> next) {
		printf("%d ", p -> data);
	}
	printf("\n");
	return OK;
}

Status del (LinkList list, int i) {
	if (i <= 0) return ERROR;
	LinkList prev = list;
	for (int j = 0; j < i - 1; j++) {
		prev = prev -> next;
		if (prev == NULL) return ERROR;
	}
	return delNode(prev);
}

int isEmpty (LinkList list) {
	if (list -> next == NULL) return TRUE;
	return FALSE;
}

ElemType getElem (LinkList list, int i) {
	if (i <= 0) return 0;
	LinkList p = list;
	for (int j = 0; j < i; j++) {
		p = p -> next;
		if (p == NULL) return 0;
	}
	return p -> data;
}

Status clear (LinkList list) {
	while (list -> next != NULL) {
		delNode(list);
	}
	return OK;
}

int locateElem (LinkList list, ElemType n) {
	int i = 1;
	for (LinkList p = list -> next; p != NULL; p = p -> next) {
		if (p -> data == n) return i;
		i++;
	}
	return -1;
}


main () {
	LinkList list = newNode();
	list -> next = NULL;

	for (int i = 0; i < 10; i++) insertAtHead(list, i * 3);
	for (int i = 0; i < 10; i++) insertAtTail(list, i * 3);
	insert(list, 10, 100);
	traverse(list);
	printf("Length: %d\n", getLength(list));
	
	printf("At position 6: %d\n", getElem(list, 6));

	del(list, 6);
	traverse(list);

	printf("Position of 12 is: %d\n", locateElem(list, 12));
	printf("Position of 88 is: %d\n", locateElem(list, 88));

	clear(list);
	printf("Is list empty: %d\n", isEmpty(list));
}
