/*
* author: chenzhi <chenzhibupt@qq.com>
* data: Apr 25, 2017
*
* quick sort
* - updated insert-sort, was invented in 1959
* - insert-sort compares data one by one
* - shell-sort compares them in some distance
*/

#include <stdio.h>
#include <stdlib.h> // rand

#define LEN 20

void init (int a[]) {
	for (int i = 0; i < LEN; i++) { 
		a[i] = rand() % 100;
	}
}
void traverse (int a[]) {
	for (int i = 0; i < LEN; i++) {
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

void quickSort (int a[], int l, int r) {
	if (l >= r) return;
	int pivotK = (l + r) / 2;
	int pivotV = a[pivotK];
	swap(a, l, pivotK);
	int writer = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] < pivotV) {
			writer++;
			swap(a, writer, i);
		}
	}
	swap(a, l, writer);
	quickSort(a, l, writer - 1);
	quickSort(a, writer + 1, r);
}

main () {
	int a[LEN];
	init(a);
	traverse(a);
	quickSort(a, 0, LEN - 1);
	traverse(a);
}

