/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 25, 2017
*
* select sort
* - find minimal number from unsorted list, put on the end of sorted list
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

void selectSort (int a[]) {
	int min, i, j;
	for (i = 0; i < LEN; i++) {
		min = i;
		for (j = i + 1; j < LEN; j++) {
			if(a[j] < a[min]) min = j;
		}
		if (min != i) swap(a, min, i);
	}
}

main () {
	int a[LEN];
	init(a);
	traverse(a);
	selectSort(a);
	traverse(a);
}

