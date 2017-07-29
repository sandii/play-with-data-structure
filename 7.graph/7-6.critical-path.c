/*
* author: chenzhi <chenzhibupt@qq.com>
* date: June 23, 2017
*
* critical path
* - from start point to end, longest path is critical path
* - shorten critical path can shorten total time
* 
* - crucial concept is earliest time & lasest time of vertex (etv & ltv) 
* - if one edge's sta-etv == end-ltv - cost
* - then the edge is a part of critical path
*
* - then how to get all etvs and ltvs?
* - initiate etvs to 0, end-etv = max(sta-etv + distance)
* - initiate ltvs to max(etvs), sta-ltv = min(end-ltv - distance)
* - 2 stacks from topological sort would be used in these processes
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
	int in;		// in-degree
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

// this version of topologicalSort return number of non-loop vertex
int topologicalSort (LGraph* gp, int stack[]) {
	int vNum = gp -> vertexNum;
	int count = 0;
	int top = 0;
	int _stack[vNum];

	for (int i = 0; i < vNum; i++) {
		if(gp -> vertex[i].in) continue;
		stack[count++] = _stack[top++] = i;	
	}
	// main loop
	while (top) {
		int sta = _stack[--top];

		for (ArcNode* np = gp -> vertex[sta].firstEdge; np; np = np -> next) {
			int end = np -> adjacency;
			(gp -> vertex[end].in)--;
			if (gp -> vertex[end].in) continue;
			stack[count++] = _stack[top++] = end;
		}
	}
	return count;
}
void getEtv (LGraph* gp, int etv[], int stack[], int len) {
	// init
	for (int i = 0; i < len; i++) {
		etv[i] = 0;
	}
	// main loop
	for (int i = 0; i < len; i++) {
		int sta = stack[i];
		for (ArcNode* np = gp -> vertex[sta].firstEdge; np; np = np -> next) {
			int end = np -> adjacency;
			if (etv[end] < etv[sta] + np -> weight) {
				etv[end] = etv[sta] + np -> weight;
			}
		}
	}

}
#define INFINITY 65535
int maxInArr (int arr[], int len) {
	int max = -INFINITY;
	for (int i = 0; i < len; i++) {
		if (max >= arr[i]) continue;
		max = arr[i];
	}
	return max;
}
void getLtv (LGraph* gp, int ltv[], int stack[], int len, int etv[]) {
	// init
	int max = maxInArr(etv, len);
	for (int i = 0; i < len; i++) {
		ltv[i] = max;
	}
	// main loop
	for (int i = len - 1; i >= 0; i--) {
		int sta = stack[i];
		for (ArcNode* np = gp -> vertex[sta].firstEdge; np; np = np -> next) {
			int end = np -> adjacency;
			// printf("%d - %d  %d : %d\n", sta, end, ltv[sta], ltv[end] - np -> weight);
			if (ltv[sta] > ltv[end] - np -> weight) {
				ltv[sta] = ltv[end] - np -> weight;
			}
		}
	}
}
void criticalPath (LGraph* gp, int etv[], int ltv[], int stack[], int len) {
	// print result
	printf("\nindex: ");
	for (int i = 0; i < len; i++) printf("%2d ", stack[i]);
	printf("\netv:   ");
	for (int i = 0; i < len; i++) printf("%2d ", etv[i]);
	printf("\nltv:   ");
	for (int i = 0; i < len; i++) printf("%2d ", ltv[i]);
	printf("\n\n");

	printf("Critical Path:\n");
	for (int i = 0; i < len; i++) {
		int sta = stack[i];
		for (ArcNode* np = gp -> vertex[sta].firstEdge; np; np = np -> next) {
			int end = np -> adjacency;
			if (etv[sta] != ltv[end] - np -> weight) continue;
			printf("<%d, %d> ", sta, end);
		}
	}
}

main () {
	LGraph gragh;
	// see 7-6.jpg
	// init(&gragh, (char*)("0,1,2,3"), (char*)("0-2-2,1-2-4,2-3-5"));
	init(&gragh, (char*)("0,1,2,3,4,5,6,7,8,9"), (char*)("0-1-3,0-2-4,1-3-5,1-4-6,2-3-8,2-5-7,3-4-3,4-6-9,4-7-4,5-7-6,6-9-2,7-8-5,8-9-3"));
	printArc(&gragh);
	printf("\n\n");

	int stack[gragh.vertexNum];
	int len = topologicalSort(&gragh, stack);
	int etv[len]; getEtv(&gragh, etv, stack, len);
	int ltv[len]; getLtv(&gragh, ltv, stack, len, etv);
	criticalPath(&gragh, etv, ltv, stack, len);	
}
