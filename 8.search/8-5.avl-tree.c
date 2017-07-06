/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 5, 2017
*
* AVL tree
* - invented by two former Soviet Union mathematicians in 1962
* - add int bf into node to record balance status of node
* - bf = (left tree height) - (right tree height)
* - when abs(bf) >= 2, we should do some rotations to rebalance it
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
	AVLTree r 		= (*tp) -> rchild;
	(*tp) -> rchild = r -> lchild;
	r -> lchild 	= *tp;
	*tp 			= r;
}
void rotateR (AVLTree* tp) {
	AVLTree l 		= (*tp) -> lchild;
	(*tp) -> lchild = l -> rchild;
	l -> rchild 	= *tp;
	*tp 			= l;
}

#define LH  1
#define EH  0
#define RH -1

void balanceL (AVLTree* tp) {
	AVLTree l = (*tp) -> lchild;

	// simplest situation:
	// left child's left tree is higher than right tree
	// it is same with *tp
	// so we only need to rotate *tp rightward
	if (l -> bf == LH) {
		(*tp) -> bf = l -> bf = EH;
		rotateR(tp);
		return;
	}

	// left child's right tree is higher than left tree
	// it is different from *tp
	// we need to rotate left child leftward
	// then rotate *tp rightward
	AVLTree lr = l -> rchild;
	// and we need to consider left child's right child
	if (lr -> bf == LH) {
		(*tp) -> bf = RH;
		l -> bf 	= EH;
	}
	if (lr -> bf == RH) {
		(*tp) -> bf = EH;
		l -> bf 	= LH;
	}
	if (lr -> bf == EH) {
		(*tp) -> bf = EH;
		l -> bf 	= EH;
	}
	lr -> bf = EH;
	rotateL(&(*tp) -> lchild);
	rotateR(tp);
}
void balanceR (AVLTree* tp) {
	AVLTree r = (*tp) -> rchild;
	if (r -> bf == RH) {
		(*tp) -> bf = r -> bf = EH;
		rotateL(tp);
		return;
	}
	AVLTree rl = r -> lchild;
	if (rl -> bf == RH) {
		(*tp) -> bf = LH;
		r -> bf 	= EH;
	}
	if (rl -> bf == LH) {
		(*tp) -> bf = EH;
		r -> bf 	= RH;
	}
	if (rl -> bf == EH) {
		(*tp) -> bf = EH;
		r -> bf 	= EH;
	}
	rl -> bf = EH;
	rotateR(&(*tp) -> rchild);
	rotateL(tp);
}

Status insert (AVLTree* tp, int e, Status* taller) {
	// find suitable place
	if (*tp == NULL) {
		*tp = (AVLTree) malloc(sizeof(struct node));
		(*tp) -> data = e;
		(*tp) -> lchild = (*tp) -> rchild = NULL;
		(*tp) -> bf = EH;
		*taller = TRUE;
		return TRUE;
	}

	// find node with same value, quit
	int data = (*tp) -> data;
	if (e == data) {
		*taller = FALSE;
		return FALSE;
	}

	// insert in lchild
	if (e < data) {
		// try to insert
		Status rs = insert(&(*tp) -> lchild, e, taller);
		// insert fail
		if (rs == FALSE) return FALSE;
		// inserted, but tree didn't grow taller, need no adjustment
		if (*taller == FALSE) return TRUE;
		// inserted, and tree grow taller, adjust it
		switch ((*tp) -> bf) {
			case LH:
				balanceL(tp);		// (*tp) -> bf == 2, balance it
				*taller = FALSE;	// after balancing, tree is short again
				break;
			case EH:
				(*tp) -> bf = LH;	// (*tp) -> bf == 1, record it
				*taller = TRUE;		// tree is taller
				break;
			case RH:
				(*tp) -> bf = EH;	// (*tp) -> bf == 0, record it
				*taller = FALSE;	// tree didn't grow taller
				break;
		}
	}

	// insert in rchild
	if (e > data) {
		Status rs = insert(&(*tp) -> rchild, e, taller);
		if (rs == FALSE) return FALSE;
		if (*taller == FALSE) return TRUE;
		switch ((*tp) -> bf) {
			case LH:
				(*tp) -> bf = EH;
				*taller = FALSE;				
				break;
			case EH:
				(*tp) -> bf = RH;
				*taller = TRUE;
				break;
			case RH:
				balanceR(tp);
				*taller = FALSE;
				break;
		}
	}
	return TRUE;
}
void traverse (AVLTree t) {
	if (t == NULL) return;
	traverse(t -> lchild);
	printf("%2d ", t -> data);
	traverse(t -> rchild);
}

main () {
	AVLTree t = NULL;

	int taller;
	for (int i = 0; i < 20; i++) {
		int n = rand() % 100;
		printf("%2d ", n);
		insert(&t, n, &taller);
	}
	printf("\n");
	traverse(t);
	printf("\n");
}
