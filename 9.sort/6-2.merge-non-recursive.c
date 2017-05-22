/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 22, 2017
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

// a little different from recursive version
// mid should be a parameter instead of (sta + end) / 2
// because lengths of two sub-arrays might be different a lot
void doMerge (int src[], int dst[], int sta, int mid, int end) {
	int writer = sta;
	int reader1 = sta;
	int reader2 = mid + 1;
	while (reader1 <= mid && reader2 <= end) {
		if (src[reader1] < src[reader2]) {
			dst[writer++] = src[reader1++];
		} else {
			dst[writer++] = src[reader2++];
		}
	}
	while (reader1 <= mid) {
		dst[writer++] = src[reader1++];
	}
	while (reader2 <= end) {
		dst[writer++] = src[reader2++];
	}
}
void mergePass (int src[], int dst[], int subLen) {
	int i = 0;
	while (i + subLen * 2 <= LEN) {
		doMerge(src, dst, i, i + subLen - 1, i + subLen * 2 - 1);
		i = i + subLen * 2;
	}
	// less than two sub-arrays left
	if (i + subLen < LEN) {
		doMerge(src, dst, i, i + subLen - 1, LEN - 1);
	// less than one sub-array left
	} else {
		while (i < LEN) {
			dst[i] = src[i];
			i++;
		}
	}
}
void mergeSort (int src[]) {
	int temp[LEN];
	int subLen = 1;
	while (subLen < LEN) {
		mergePass(src, temp, subLen);
		subLen *= 2;
		// if subLen > LEN here
		// mergePass simply copy 
		mergePass(temp, src, subLen);
		subLen *= 2;
	}
}

main () {
	int a[LEN];
	init(a);
	traverse(a);
	mergeSort(a);
	traverse(a);
}

