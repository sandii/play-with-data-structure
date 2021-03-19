/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 17, 2017
*
* sequence list
* - index from 0
*/

#include <stdio.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

#define MAXSIZE 20


typedef int Status;
typedef int ElemType;

typedef struct {
  ElemType data[MAXSIZE];
  int length;
} SqList;


Status init (SqList* lp) {
  lp -> length = 0;
  return OK;
}

int getLength (SqList* lp) {
  return lp -> length;
}

Status insert (SqList* lp, int i, ElemType n) {
  int len = getLength(lp);
  if (len >= MAXSIZE) return ERROR;  // full
  if (i < 0 || i > len) return ERROR;  // invalid position 
  lp -> length = len + 1;
  for (int j = len - 1; j > i; j--) {
    lp -> data[j] = lp -> data[j - 1];
  }
  lp -> data[i] = n;
  return OK;
}

Status del (SqList* lp, int i) {
  int last = getLength(lp) - 1;
  if (i < 0 || i > last) return ERROR;
  for (int j = i; j < last; j++) {
    lp -> data[j] = lp -> data[j + 1];
  }
  lp -> length = last;
  return OK;
}

int isEmpty (SqList* lp) {
  if (getLength(lp) == 0) return TRUE;
  return FALSE;
}

ElemType getElem (SqList* lp, int i) {
  if (isEmpty(lp)) return 0;
  int last = getLength(lp) - 1;
  i = i > last ? last : i;
  return lp -> data[i];
}

Status traverse (SqList* lp) {
  int len = getLength(lp);
  for (int i = 0; i < len; i++) {
    printf("%d ", lp -> data[i]);
  }
  printf("\n");
  return OK;
}

Status clear (SqList* lp) {
  lp -> length = 0;
  return OK;
}

int locateElem (SqList* lp, ElemType n) {
  int len = getLength(lp);
  for (int i = 0; i < len; i++) {
    ElemType d = lp -> data[i];
    if (d == n) return i;
  }
  return -1;
}


main () {
  SqList list;
  init(&list);
  for (int i = 0; i < 10; i++) {
    insert(&list, i, i * 2);
  }
  traverse(&list);
  printf("Length: %d\n", getLength(&list));
  printf("At position 6: %d\n", getElem(&list, 6));

  del(&list, 6);
  insert(&list, 6, 999);
  traverse(&list);

  printf("Position of 14 is: %d\n", locateElem(&list, 14));
  printf("Position of 88 is: %d\n", locateElem(&list, 88));

  clear(&list);
  printf("Is list empty: %d\n", isEmpty(&list));
}
