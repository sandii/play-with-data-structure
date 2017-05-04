/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 4, 2017
*
* fibonacci search 
* - O(logn)
* - Fibonacci Series helps to partition array as golden ratio
* - url below help me understand it
* http://stackoverflow.com/questions/7599479/fibonacci-search
*/

#include <stdio.h>

#define ARR_SIZE 40
#define FIB_SIZE 20

int fib[FIB_SIZE];

void initFib () {
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i < FIB_SIZE; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
}
int getFibIndex (int a[]) {
	int k = 0;
	while (fib[k] < ARR_SIZE) k++;
	return k;
}
void extendArray (int src[], int dst[], int len) {
	int last = src[ARR_SIZE - 1];
	for (int i = 0; i < len; i++) {
		dst[i] = i < ARR_SIZE ? src[i] : last;
	}
}

int fibonacciSearch (int src[], int key) {
	int k = getFibIndex(src);
	int a[fib[k]];
	extendArray(src, a, fib[k]);

	int low = 0;
	int high = fib[k] - 1;
	int mid;

	while (low <= high) {
		mid = low + fib[k - 1];
		if (key < a[mid]) {
			high = mid - 1;
			k = k - 1;			
		} else if (key > a[mid]) {
			low = mid + 1;
			k = k - 2;			
		} else {
			// result is probably extended part
			return mid <= ARR_SIZE - 1 ? mid : ARR_SIZE - 1;
		}			
	}

	return -1;
}

main () {
	int a[ARR_SIZE];
	for (int i = 0; i < ARR_SIZE; i++) {
		a[i] = i * 2;
	}
	initFib();
	printf("%d\n", fibonacciSearch(a, 12));
	printf("%d\n", fibonacciSearch(a, 0));
	printf("%d\n", fibonacciSearch(a, 100));
	printf("%d\n", fibonacciSearch(a, -1));
	printf("%d\n", fibonacciSearch(a, 3));
	printf("%d\n", fibonacciSearch(a, 14));
}
