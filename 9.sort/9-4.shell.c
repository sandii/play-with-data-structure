/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 25, 2017
*
* shell sort
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

void shellSort (int a[]) {
  for (int span = LEN / 3 + 1; span > 1; span = span / 3 + 1) {
    for (int i = span; i < LEN; i++) {
      int temp = a[i];
      int j;
      for (j = i - span; j >= 0 && a[j] > temp; j -= span) {
        a[j + span] = a[j];
      }
      a[j + span] = temp;
    }
  }
}

main () {
  int a[LEN];
  init(a);
  traverse(a);
  shellSort(a);
  traverse(a);
}

