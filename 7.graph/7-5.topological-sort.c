/*
* author: chenzhi <chenzhibupt@qq.com>
* data: June 21, 2017
*
* adjacency list
*
*/

#include <stdio.h>
#include <string.h>	// strlen strcpy
#include <ctype.h>	// isdigit
#include <stdlib.h> // malloc free

#define VMAX 20

typedef struct ArcNode {
	int adjacency;
	int weight;
	struct ArcNode* next;
} ArcNode;
typedef struct {
	int in;
	int data;
	ArcNode* firstEdge;
} VertexNode;
typedef struct {
	VertexNode vertex[VMAX];
	int vertexNum;
	int arcNum;
} LGraph;

void split (char* arr[], char* str, char gap) {
	int i = 0;
	int subLen = 0;
	int max = strlen(str);
	char temp[max + 1];
	for (int j = 0; j <= max; j++) {
		if (str[j] == gap || str[j] == '\0') {
			if (subLen == 0) continue;
			temp[subLen] = '\0';
			char* sp = (char*) malloc(sizeof(char) * subLen);
			strcpy(sp, temp);
			arr[i++] = sp;
			temp[0] = '\0';
			subLen = 0;
		} else {
			temp[subLen] = str[j];
			subLen++;
		}
	}
}
void freeArr (char* arr[], int len) {
	for (int i = 0; i < len; i++) {
		free(arr[i]);
	}
}
void init (LGraph* gp, char* vStr, char* aStr) {
	// get vertextNum
	int vertexNum = 0;
	for (char* cp = vStr; *cp != '\0'; cp++) {
		if (*cp == ',') vertexNum++;
	}
	vertexNum++;
	gp -> vertexNum = vertexNum;

	// init vertexes
	char* vArr[vertexNum];
	split(vArr, vStr, ',');
	for (int i = 0; i < vertexNum; i++) {
		gp -> vertex[i].in = 0;
		gp -> vertex[i].data = atoi(vArr[i]);
		gp -> vertex[i].firstEdge = NULL;
	}

	// get arcNum
	int arcNum = 0;
	for (char* cp = aStr; *cp != '\0'; cp++) {
		if (*cp == ',') arcNum++;
	}
	arcNum++;
	gp -> arcNum = arcNum;

	// fill arc list
	char* dotArr[arcNum];
	char* numArr[3];
	split(dotArr, aStr, ',');
	for (int k = 0; k < arcNum; k++) {
		split(numArr, dotArr[k], '-');
		int i = atoi(numArr[0]);
		int j = atoi(numArr[1]);
		ArcNode* temp = (ArcNode*) malloc(sizeof(ArcNode));
		temp -> adjacency = j;
		temp -> weight = atoi(numArr[2]);
		temp -> next = gp -> vertex[i].firstEdge;
		gp -> vertex[i].firstEdge = temp;
		(gp -> vertex[j].in)++;
	}
	freeArr(vArr, vertexNum);
	freeArr(dotArr, arcNum);
	freeArr(numArr, 3);
}
void printArc (LGraph* gp) {
	printf("Arc:\n");
	for (int i = 0; i < gp -> vertexNum; i++) {
		printf("%2d (%d in) - ", gp -> vertex[i].data, gp -> vertex[i].in);
		for (ArcNode* ap = gp -> vertex[i].firstEdge; ap != NULL; ap = ap -> next) {
			int j = ap -> adjacency;
			printf("%2d ", gp -> vertex[j].data);
		}
		printf("\n");
	}
	printf("\n");
}


typedef int boolean;
#define TRUE  1
#define FALSE 0

boolean topologicalSort (LGraph* gp) {
	ArcNode* np = NULL;
	int vNum = gp -> vertexNum;
	int count = 0;

	// stack
	int top = 0;
	int stack[vNum];

	// init
	for (int i = 0; i < vNum; i++) {
		if(gp -> vertex[i].in) continue;
		stack[top++] = i;
	}

	// main loop
	while (top) {
		int popped = stack[--top];
		printf("%2d ", gp -> vertex[popped].data);
		count++;

		for (np = gp -> vertex[popped].firstEdge; np; np = np -> next) {
			int i = np -> adjacency;
			(gp -> vertex[i].in)--;
			if (gp -> vertex[i].in) continue;
			stack[top++] = i;
		}
	}
	printf("\n\n");
	return count == vNum ? FALSE : TRUE;

}

main () {
	LGraph gragh;
	// see 7-5.jpg
	init(&gragh, (char*)("0,1,2,3,4,5,6,7,8,9,10,11,12,13"), (char*)("0-4-1,0-5-1,0-11-1,1-2-1,1-4-1,1-8-1,2-5-1,2-6-1,2-9-1,3-2-1,3-13-1,4-7-1,5-8-1,5-12-1,6-5-1,8-7-1,9-10-1,10-13-1,12-9-1"));
	printArc(&gragh);
	printf("\n\n");

	boolean rs = topologicalSort(&gragh);
	printf("Gragh has ring: %d\n", rs);
}
