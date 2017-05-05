/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 5, 2017
*
* avl tree
* 
*/

#include <stdio.h>
#include <stdlib.h>	// malloc free

#define TRUE  1
#define FALSE 0

typedef int Status;
struct node {
	int data;
	int bf;
	struct node* lchild;
	struct node* rchild;
};
typedef struct node* AVLTree;

void rotateL (AVLTree* tp) {
	AVLTree r = (*tp) -> rchild;
	(*tp) -> rchild = r -> lchild;
	r -> lchild = *tp;
	*tp = r;
}
void rotateR (AVLTree* tp) {
	AVLTree l = (*tp) -> lchild;
	(*tp) -> lchild = l -> rchild;
	l -> rchild = *tp;
	*tp = l;
}
void balanceL () {}
void balanceR () {}

Status insert (AVLTree* tp, int e, Status* taller) {
	
}

main () {
	AVLTree t = NULL;
	
	printf("insert 20 random numbers..\n");
	int taller;
	for (int i = 0; i < 20; i++) {
		int n = rand() % 100;
		printf("%d ", n, &taller);
		insert(&t, n);
	}
	printf("\n");
	traverse(t);
	printf("\n");
}
