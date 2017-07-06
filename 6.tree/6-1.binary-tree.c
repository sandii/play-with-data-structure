/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 2, 2017
*
* binary tree
*
*/

#include <stdio.h>
#include <stdlib.h> // malloc free


typedef int ElemType;
struct node {
	ElemType data;
	struct node* lchild;
	struct node* rchild;
};
typedef struct node* Tree;



char* pattern = "ABD##EH##I##CF##G##";
int i = 0;


void create (Tree* tp) {
	ElemType data = pattern[i];
	i++;
	if (data == '\0') return;
	if (data == '#') { *tp = NULL; return; }
	*tp = (Tree) malloc(sizeof(struct node));
	(*tp) -> data = data;
	create(&(*tp) -> lchild);
	create(&(*tp) -> rchild);
}
void preTraverse (Tree t) {
	if (t == NULL) return;
	printf("%c ", t -> data);
	preTraverse(t -> lchild);
	preTraverse(t -> rchild);
}
void midTraverse (Tree t) {
	if (t == NULL) return;
	midTraverse(t -> lchild);
	printf("%c ", t -> data);
	midTraverse(t -> rchild);
}
void aftTraverse (Tree t) {
	if (t == NULL) return;
	aftTraverse(t -> lchild);
	aftTraverse(t -> rchild);
	printf("%c ", t -> data);
}

main () {
	Tree t = NULL;
	create(&t);
	preTraverse(t); printf("\n");
	midTraverse(t); printf("\n");
	aftTraverse(t); printf("\n");
}

