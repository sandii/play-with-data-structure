/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 8, 2017
*
* hash list 
* 
*/

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define ARRSIZE 12
#define EMPTY -65535


typedef struct node{
  int data;
  struct node* next;
} Node;
typedef Node* NP; 

typedef int Status;

int hash (int n) { return abs(n % ARRSIZE); }

void init (Node list[]) {
  for (int i = 0; i < ARRSIZE; i++) {
    list[i].data = EMPTY;
    list[i].next = NULL;
  }
}
Status exist (Node list[], int n) {
  int addr = hash(n);
  NP curr = list[addr].next;
  while (curr != NULL) {
    if (curr -> data == n) return OK;
    curr = curr -> next;
  }
  return ERROR;
}
Status insert (Node list[], int n) {
  int addr = hash(n);
  NP* curr = &(list[addr].next);
  while (*curr != NULL) {
    if ((*curr) -> data == n) return ERROR;
    *curr = (*curr) -> next;
  }
  NP temp = (NP) malloc(sizeof(struct node));
  temp -> data = n;
  temp -> next = NULL;
  *curr = temp;
  return OK;
}
Status remove (Node list[], int n) {
  int addr = hash(n);
  NP* prev = NULL;
  NP* curr = &(list[addr].next);
  while (*curr != NULL) {
    if ((*curr) -> data == n) {
      if (prev == NULL) {
        list[addr].next = (*curr) -> next;
      } else {
        (*prev) -> next = (*curr) -> next;
      }
      free(*curr);
      return OK;
    }
    *prev = *curr;
    *curr = (*curr) -> next;
  }
  return ERROR;
}

main () {
  Node list[ARRSIZE];
  init(list);
  for (int i = 0; i < ARRSIZE; i++) {
    insert(list, i * 5);
  }
  printf("exist 5? %d\n",   exist(list, 5));
  printf("exist 10? %d\n",  exist(list, 10));
  printf("exist 55? %d\n",  exist(list, 55));
  printf("exist 14? %d\n",  exist(list, 14));
  printf("exist -10? %d\n", exist(list, -10));
  remove(list, 10);
  printf("remove 10..\n");
  printf("exist 10? %d\n",  exist(list, 10));
}
