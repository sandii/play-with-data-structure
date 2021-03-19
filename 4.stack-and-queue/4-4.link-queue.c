/*
* author: chenzhi <chenzhibupt@qq.com>
* date: Apr 24, 2017
*
* link queue
* - head always points to an empty leading node
* - if queue is not empty, tail points to last node
* - if queue is empty, tail points to the empty leading node
*
*/

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0


typedef int ElemType;
typedef int Status;

struct node {
  ElemType data;
  struct node* next;
};
typedef struct {
  struct node* head;
  struct node* tail;
  int len ;
} LinkQueue;


struct node* createNode () {
  return (struct node*) malloc(sizeof(struct node));
}
Status init (LinkQueue* qp) {
  qp -> head = createNode();
  qp -> tail = qp -> head;
  qp -> len = 0;
  return OK;
}
int getLength (LinkQueue* qp) { return qp -> len; }
int isEmpty (LinkQueue* qp) { return qp -> len == 0 ? TRUE : FALSE; }
Status clear (LinkQueue* qp) {
  qp -> tail = qp -> head;
  qp -> len = 0;

  struct node* curr = qp -> head -> next;
  while (curr != NULL) {
    struct node* next = curr -> next;
    free(curr);
    curr = next;
  }
  return OK;
}

Status enQueue (LinkQueue* qp, ElemType n) {
  qp -> tail -> next = createNode();
  qp -> tail = qp -> tail -> next;
  qp -> tail -> next = NULL;
  qp -> tail -> data = n;
  (qp -> len)++;
  return OK;
}
ElemType deQueue (LinkQueue* qp) {
  if (isEmpty(qp)) return 0;
  struct node* curr = qp -> head -> next;
  ElemType n = curr -> data;
  qp -> head -> next = curr -> next;
  free(curr);

  (qp -> len)--;
  if (isEmpty(qp)) qp -> tail = qp -> head;
  return n;
}
ElemType getHead (LinkQueue* qp) {
  if (isEmpty(qp)) return 0;
  return qp -> head -> next -> data;
}


main () {
  LinkQueue queue;
  init(&queue);

  for (int i = 0; i < 10; i++) {
    Status rs = enQueue(&queue, i * 10);
    if (rs == ERROR) continue;
    printf("enQueue: %d\n", i * 10);
  }
  printf("deQueue: %d\n", deQueue(&queue));
  printf("head: %d\n", getHead(&queue));
  printf("len: %d\n", getLength(&queue));
  printf("deQueue: %d\n", deQueue(&queue));
  printf("deQueue: %d\n", deQueue(&queue));
  printf("is empty: %d\n", isEmpty(&queue));
  clear(&queue); printf("clear..\n");
  printf("is empty: %d\n", isEmpty(&queue));
}
