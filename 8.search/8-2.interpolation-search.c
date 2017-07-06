/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 3, 2017
*
* interpolation search 
* - O(logn)
* - find a appropriate ratio in array
*/

#include <stdio.h>

#define MAX 20

int interpolationSearch (int a[], int key) {
	int low = 0;
	int high = MAX - 1;
	int ratio;
	int mid;

	while (low <= high) {
		ratio = (key - a[low]) / (a[high] - a[low]);
		mid = low + (high - low) * ratio;	// !!!
		if (key < a[mid])
			high = mid - 1;
		else if (key > a[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

main () {
	int a[MAX];
	for (int i = 0; i < MAX; i++) {
		a[i] = i * 2;
	}
	printf("%d\n", interpolationSearch(a, 12));
	printf("%d\n", interpolationSearch(a, 10));
	printf("%d\n", interpolationSearch(a, -1));
	printf("%d\n", interpolationSearch(a, 3));
	printf("%d\n", interpolationSearch(a, 14));
}
