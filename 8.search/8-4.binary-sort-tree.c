/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 4, 2017
*
* binary sort tree 
* 
*/

#include <stdio.h>
#include <stdlib.h>  // malloc free

#define TRUE  1
#define FALSE 0

typedef int Status;
struct node {
  int data;
  struct node* lchild;
  struct node* rchild;
};
typedef struct node* BSTree;

Status search (BSTree t, BSTree parent, int n, BSTree* curr) {
  if (t == NULL) { *curr = parent; return FALSE; }
  int data = t -> data;
  if (n == data) { *curr = t; return TRUE; }
  if (n < data) return search(t -> lchild, t, n, curr);
  if (n > data) return search(t -> rchild, t, n, curr);
}
Status insert (BSTree* tp, int n) {
  BSTree parent;
  if (search(*tp, NULL, n, &parent)) return FALSE;
  BSTree curr = (BSTree) malloc(sizeof(struct node));
  curr -> data = n;
  curr -> lchild = curr -> rchild = NULL;
  if (*tp == NULL) { *tp = curr; return TRUE; }
  int parentData = parent -> data;
  if (n < parentData) parent -> lchild = curr;
  if (n > parentData) parent -> rchild = curr;
  return TRUE;
}
void doRemove (BSTree* tp) {
  BSTree l = (*tp) -> lchild;
  BSTree r = (*tp) -> rchild;
  if (l == NULL) { *tp = r; return; }
  if (r == NULL) { *tp = l; return; }

  // if lchild and rchild both exit
  // find rightest (biggest) offspring of lchild to replace *tp
  BSTree parent = *tp;
  BSTree offspring = l;
  while (offspring -> rchild) {
    parent = offspring;
    offspring = offspring -> rchild;
  }
  if (offspring == l) {
    (*tp) -> lchild = offspring -> lchild;
  } else {
    parent -> rchild = offspring -> lchild;
  }
  (*tp) -> data = offspring -> data;
  free(offspring);
}
Status remove (BSTree* tp, int n) {
  if (*tp == NULL) return FALSE;
  int data = (*tp) -> data;
  if (n < data) return remove(&(*tp) -> lchild, n);
  if (n > data) return remove(&(*tp) -> rchild, n);
  if (n == data) { doRemove(tp); return TRUE; }
}
void traverse (BSTree t) {
  if (t == NULL) return;
  traverse(t -> lchild);
  printf("%d ", t -> data);
  traverse(t -> rchild);
}

main () {
  BSTree t = NULL;
  
  printf("insert 20 random numbers..\n");
  for (int i = 0; i < 20; i++) {
    int n = rand() % 100;
    printf("%d ", n);
    insert(&t, n);
  }
  printf("\n");
  traverse(t);
  printf("\n");

  BSTree temp;
  printf("14 in it? %d\n", search(t, NULL, 14, &temp));
  printf("15 in it? %d\n", search(t, NULL, 15, &temp));
  printf("24 in it? %d\n", search(t, NULL, 24, &temp));
  
  printf("remove all multiples of 5..\n");
  for (int i = 0; i < 20; i++) {
    remove(&t, i * 5);
  }
  traverse(t);
  printf("\n");
}
