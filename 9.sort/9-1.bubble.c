/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 25, 2017
*
* bubble sort
* 
*/

#include <stdio.h>
#include <stdlib.h> // rand

#define LEN 20
#define TRUE 1
#define FALSE 0
typedef int Status;

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

void bubbleSort (int a[]) {
  for (int i = 0; i < LEN; i++) {
    for (int j = LEN - 1; j > i; j--) {
      if(a[j] < a[j - 1]) swap(a, j, j - 1);
    }
  }
}
void bubbleSort2 (int a[]) {
  Status sorted = FALSE;
  for (int i = 0; i < LEN; i++) {
    if (sorted == TRUE) break;
    sorted = TRUE;
    for (int j = LEN - 1; j > i; j--) {
      if(a[j] < a[j - 1]) {
        swap(a, j, j - 1);
        sorted = FALSE;
      }
    }
  }
}


main () {
  int a[LEN];
  init(a);
  traverse(a);
  bubbleSort(a);
  traverse(a);

  init(a);
  traverse(a);
  bubbleSort2(a);
  traverse(a);
}

