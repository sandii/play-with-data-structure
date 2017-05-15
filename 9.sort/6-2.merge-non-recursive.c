/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 12, 2017
*
* merge sort
* - non-recursive version
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
void doMerge () {}
void mergePass () {}
void mergeSort () {}

main () {
	int a[LEN];
	init(a);
	traverse(a);
	mergeSort(a, 0, LEN - 1);
	traverse(a);
}

