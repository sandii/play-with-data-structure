/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 2, 2017
*
* kmp
* - invented by knuth-morris-pratt in 1977
* - key is to find common part of prefix and suffix of pattern string
* - and we can get an array next[]
*
*  A B A B A C D - pattern string
*  0 0 1 2 3 0 0 - length of common part of prefix and suffix
* -1 0 0 1 2 3 0 - move left one step to get next[] and next[0] = -1
*/

#include <stdio.h>
#include <string.h> // strlen

void getNext (char* p, int next[]) {
  int pLen = strlen(p);
  int k = -1;
  int j = 0;
  next[0] = -1;
  while (j < pLen - 1) {
    if (k == -1 || p[k] == p[j]) {
      k++;
      j++;
      next[j] = k;
    } else {
      k = next[k];
    }
  }
}

int kmp (char* s, char* p) {
  int sLen = strlen(s);
  int pLen = strlen(p);
  int i = 0;
  int j = 0;
  int next[pLen];
  getNext(p, next);
  while (i < sLen && j < pLen) {
    if (j == -1 || s[i] == p[j]) {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }
  if (j == pLen) {
    return i - j;
  } else {
    return -1;
  }
}

main () {
  printf("%d\n", kmp("hello", "ell"));
  printf("%d\n", kmp("hello", "all"));
  printf("%d\n", kmp("hello", "hel"));
  printf("%d\n", kmp("hello", "ababab"));
}

