/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 21, 2017
*
* static link list
* - array of struct
* - array head point to beginning of list, or array tail if list is empty
* - array tail point to next free space, or itself if list is full
* - list tail point to array tail
* - index from 1 to maxsize - 2
*/

#include <stdio.h>

#define MAXSIZE 30
#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0


typedef int Status;
typedef int ElemType;

typedef struct {
	ElemType data;
	int cur;
} Node, SLinkList[MAXSIZE];


Status init (SLinkList list) {
	for (int i = 0; i < MAXSIZE; i++) {
		list[i].cur = i + 1;
	}
	list[0].cur = MAXSIZE - 1;
	list[MAXSIZE - 1].cur = 1;
}
Status clear (SLinkList list) { init(list); }

int getLength (SLinkList list) {
	int len = 0;
	for (int i = list[0].cur; i != MAXSIZE - 1; i = list[i].cur) {
		len++;
	}
	return len;
}

int getPrevIndex (SLinkList list, int i) {
	int prev = 0;
	for (int j = 1; j < i; j++) {
		prev = list[prev].cur;
	}
	return prev;
}

Status insert (SLinkList list, int i, ElemType n) {
	if (i <= 0 || i > MAXSIZE - 2) return ERROR;	// phisically beyond array
	if (i > getLength(list) + 1) return ERROR;		// logically beyond list
	int prev = getPrevIndex(list, i);
	int curr = list[MAXSIZE - 1].cur;
	list[MAXSIZE - 1].cur = list[curr].cur;
	list[curr].data = n;
	list[curr].cur = list[prev].cur;
	list[prev].cur = curr;
	return OK;
}

Status remove (SLinkList list, int i) {
	if (i <= 0 || i > MAXSIZE - 2) return ERROR;// phisically beyond array
	if (i > getLength(list)) return ERROR;		// logically beyond list
	int prev = getPrevIndex(list, i);
	int curr = list[prev].cur;
	int next = list[curr].cur;

	list[prev].cur = next;
	int prep = list[MAXSIZE - 1].cur;
	list[curr].cur = prep;
	list[MAXSIZE - 1].cur = curr;
	return OK;
}

Status traverse (SLinkList list) {
	for (int i = list[0].cur; i != MAXSIZE - 1; i = list[i].cur) {
		printf("%d ", list[i].data);
	}
	printf("\n");
	return OK;
}

ElemType getElem (SLinkList list, int i) {
	if (i <= 0 || i > MAXSIZE - 2) return 0;// phisically beyond array
	if (i > getLength(list) + 1) return 0;	// logically beyond list
	int index = 0;
	for (int j = 0; j < i; j++) {
		index = list[index].cur;
	}
	return list[index].data;
}

int locateElem (SLinkList list, ElemType n) {
	int j = 1;
	for (int i = list[0].cur; i != MAXSIZE - 1; i = list[i].cur) {
		if (list[i].data == n) return j;
		j++;
	}
	return -1;
}

int isEmpty (SLinkList list) {
	return list[0].cur == MAXSIZE - 1 ? TRUE : FALSE;
}


main () {
	SLinkList list;
	init(list);

	for (int i = 0; i < 10; i++) insert(list, 1, i * 3);
	for (int i = 0; i < 10; i++) insert(list, 11, i * 2);
	printf("Length: %d\n", getLength(list));
	printf("Is list empty: %d\n", isEmpty(list));

	traverse(list);
	remove(list, 5);
	traverse(list);
	
	printf("At position 6: %d\n", getElem(list, 6));

	printf("Position of 12 is: %d\n", locateElem(list, 12));
	printf("Position of 88 is: %d\n", locateElem(list, 88));

	clear(list);
	printf("Is list empty: %d\n", isEmpty(list));
}
