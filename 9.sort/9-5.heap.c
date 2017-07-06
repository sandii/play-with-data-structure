/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 11, 2017
*
* heap sort
* - invented in 1964
* - to simulate tree nodes, array's indexes start from 1
* - firstly, build a max heap, which mean biggest element on top
* - then, swap top to tail, and make max heap again, until array was sorted
*/

#include <stdio.h>
#include <stdlib.h> // rand

#define LEN 20

void init (int a[]) {
	for (int i = 1; i <= LEN; i++) {
		a[i] = rand() % 100;
	}
}
void traverse (int a[]) {
	for (int i = 1; i <= LEN; i++) {
		printf("%2d ", a[i]);
	}
	printf("\n");
}
void swap (int a[], int i, int j) {
	if (i == j) return;
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
void heapAdjust (int a[], int sta, int end) {
	int parent = sta;
	int child = parent * 2;		// child is lchild
	while (child <= end) {
		// if rchild exists and is bigger than lchild
		// then child is rchild
		if (child + 1 <= end && a[child + 1] > a[child]) {
			child++;
		}
		if (a[child] > a[parent]) {
			swap(a, parent, child);
		}
		parent = child;
		child = parent * 2;
	}
}
void heapSort (int a[]) {
	for (int i = LEN / 2; i >= 1; i--) {
		heapAdjust(a, i, LEN);
	}
	for (int i = LEN; i >= 2; i--) {
		swap(a, 1, i);
		heapAdjust(a, 1, i - 1);
	}
}

main () {
	int a[LEN + 1];
	init(a);
	traverse(a);
	heapSort(a);
	traverse(a);
}

