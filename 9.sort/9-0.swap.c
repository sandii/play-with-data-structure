/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 25, 2017
*
* swap sort
* 
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

void swapSort (int a[]) {
	for (int i = 0; i < LEN; i++) {
		for (int j = i + 1; j < LEN; j++) {
			if(a[j] < a[i]) swap(a, i, j);
		}
	}
}

main () {
	int a[LEN];
	init(a);
	traverse(a);
	swapSort(a);
	traverse(a);
}

