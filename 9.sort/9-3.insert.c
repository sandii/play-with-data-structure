/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 25, 2017
*
* insert sort
* - insert next number to appropriate position of sorted list
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

void insertSort (int a[]) {
  for (int i = 1; i < LEN; i++) {
    int temp = a[i];
    int j;
    for (j = i - 1; a[j] > temp && j >= 0; j--) {
      a[j + 1] = a[j];
    }
    a[j + 1] = temp;
  }
}

main () {
  int a[LEN];
  init(a);
  traverse(a);
  insertSort(a);
  traverse(a);
}

