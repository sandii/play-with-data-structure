/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 12, 2017
*
* merge sort
* - detach array into small parts, sort small arrays, and merge them
* - stable but occupy some storage space
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
void doMerge (int src[], int dst[], int sta, int end) {
  int mid = (sta + end) / 2;
  int reader1 = sta;
  int reader2 = mid + 1;
  int writer  = sta;
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
void mergeSort (int src[], int dst[], int sta, int end) {
  // if only one element in array, just copy it
  if (sta == end) {
    dst[sta] = src[sta];
    return;
  }

  // split array into two, sort and merge
  int temp[LEN];
  int mid = (sta + end) / 2;
  mergeSort(src, temp, sta, mid);
  mergeSort(src, temp, mid + 1, end);
  doMerge(temp, dst, sta, end);
}

main () {
  int a[LEN];
  int temp[LEN];
  init(a);
  traverse(a);
  mergeSort(a, a, 0, LEN - 1);
  traverse(a);
}

