/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 4, 2017
*
* binary sort tree 
* 
*/

#include <stdio.h>
#include <stdlib.h>	// malloc free

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
	if (t == NULL) {
		*curr = parent;
		return FALSE;
	}
	int data = t -> data;
	if (n == data) {
		*curr = t;
		return TRUE;
	}
	if (n < data) return search(t -> lchild, t, n, curr);
	if (n > data) return search(t -> rchild, t, n, curr);
}
Status insert (BSTree* t, int n) {
	BSTree parent;
	if (search(*t, NULL, n, &parent)) return FALSE;
	BSTree curr = (BSTree) malloc(sizeof(struct node));
	curr -> data = n;
	curr -> lchild = curr -> rchild = NULL;
	if (*t == NULL) {
		*t = curr;
		return TRUE;
	}
	int parentData = parent -> data;
	if (n < parentData) parent -> lchild = curr;
	if (n > parentData) parent -> rchild = curr;
	return TRUE;
}
Status remove (BSTree* t, int n) {
	if (*t == NULL) return FALSE;
	int data = (*t) -> data;
	if (n == data) {
		
	}
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

	// printf("14 in it? %d\n", search(t, NULL, 14, ));

	
	printf("remove all multiples of 5..\n");
	for (int i = 0; i < 20; i++) {
		remove(&t, i * 5);
	}
	traverse(t);
}
