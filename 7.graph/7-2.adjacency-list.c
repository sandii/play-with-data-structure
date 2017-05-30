/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 30, 2017
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
	char data;
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
	// init vertexes
	int vertexNum = 0;
	for (char* cp = vStr; *cp != '\0'; cp++) {
		gp -> vertex[vertexNum++].data = *cp;		
	}
	gp -> vertexNum = vertexNum;

	// init arc list
	for (int i = 0; i < vertexNum; i++) {
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
	}
	freeArr(dotArr, arcNum);
	freeArr(numArr, 3);
}
void clear (LGraph* gp) {
	for (int i = 0; i < gp -> vertexNum; i++) {
		while (gp -> vertex[i].firstEdge != NULL) {
			ArcNode* temp = gp -> vertex[i].firstEdge;
			gp -> vertex[i].firstEdge = temp -> next;
			free(temp);
		}
	}
	gp -> vertexNum = 0;
	gp -> arcNum = 0;
}
void printV (LGraph* gp) {
	printf("Vertex: ");
	for (int i = 0; i < gp -> vertexNum; i++) {
		printf("%c ", gp -> vertex[i].data);
	}
	printf("\n\n");
}
void printA (LGraph* gp) {
	printf("Arc:\n");
	for (int i = 0; i < gp -> vertexNum; i++) {
		printf("%c - ", gp -> vertex[i].data);
		for (ArcNode* ap = gp -> vertex[i].firstEdge; ap != NULL; ap = ap -> next) {
			int j = ap -> adjacency;
			printf("%c ", gp -> vertex[j].data);
		}
		printf("\n");
	}
	printf("\n");
}


typedef int boolean;
#define TRUE  1
#define FALSE 0

boolean visited[VMAX];
void visitDFS (LGraph* gp, int i) {
	printf("%c ", gp -> vertex[i].data);
	visited[i] = TRUE;

	for (ArcNode* ap = gp -> vertex[i].firstEdge; ap != NULL; ap = ap -> next) {
		int j = ap -> adjacency;
		if (visited[j] == TRUE) continue;
		visitDFS(gp, j);
	}
}
void traverseDFS (LGraph* gp) {
	// initiate visited array
	printf("Depth-first traverse: ");
	for (int i = 0; i < gp -> vertexNum; i++) {
		visited[i] = FALSE;
	}
	for (int i = 0; i < gp -> vertexNum; i++) {
		if (visited[i] == TRUE) continue;
		visitDFS(gp, i);
	}
	printf("\n\n");
}

// bfs needs a queue
typedef struct {
	int data[VMAX];
	int head;
	int tail;
	int len;
} Queue;
// set queue as a global variable
Queue queue;

void initQueue () {
	queue.head = 0;
	queue.tail = 0;
	queue.len = 0;
}
boolean fullQueue () { return queue.len == VMAX ? TRUE : FALSE; }
boolean emptyQueue () { return queue.len == 0 ? TRUE : FALSE; }
void enQueue (int n) {
	if (fullQueue()) return;
	queue.data[queue.tail] = n;
	queue.tail = (queue.tail == VMAX - 1) ? 0 : queue.tail + 1;
	(queue.len)++;
}
int deQueue () {
	if (emptyQueue()) return 0;
	int n = queue.data[queue.head];
	queue.head = (queue.head == VMAX - 1) ? 0 : queue.head + 1;
	(queue.len)--;
	return n;
}

// bfs begins
void visitBFS (LGraph* gp, int i) {
	printf("%c ", gp -> vertex[i].data);
	visited[i] = TRUE;

	enQueue(i);
}
void traverseBFS (LGraph* gp) {
	printf("Breadth-first traverse: ");
	for (int i = 0; i < gp -> vertexNum; i++) {
		visited[i] = FALSE;
	}
	for (int k = 0; k < gp -> vertexNum; k++) {
		if (visited[k] == TRUE) continue;
		visitBFS(gp, k);
		while (!emptyQueue()) {
			int i = deQueue();
			for (ArcNode* ap = gp -> vertex[i].firstEdge; ap != NULL; ap = ap -> next) {
				int j = ap -> adjacency;
				if (visited[j] == TRUE) continue;
				visitBFS(gp, j);
			}
		}
	}
	printf("\n\n");
}


main () {
	LGraph gragh;
	// a simple graph, see 7-1-1.jpg
	init(&gragh, (char*)("abcde"), (char*)("0-4-6,1-0-9,1-2-3,2-0-2,2-3-5,3-4-1"));
	printV(&gragh);
	printA(&gragh);
	traverseDFS(&gragh);
	initQueue();
	traverseBFS(&gragh);
	printf("\n\n");

	// a more complicated graph, see 7-1-2.jpg
	// ABCDEFGHI
	// 012345678
	clear(&gragh);
	init(&gragh, (char*)("ABCDEFGHI"), (char*)("0-1-1,0-5-1,1-0-1,1-2-1,1-6-1,1-8-1,2-1-1,2-3-1,2-8-1,3-2-1,3-4-1,3-6-1,3-7-1,3-8-1,4-3-1,4-5-1,4-7-1,5-0-1,5-4-1,5-6-1,6-1-1,6-3-1,6-5-1,7-3-1,7-4-1,7-6-1,8-1-1,8-2-1,8-3-1"));
	printV(&gragh);
	printA(&gragh);
	traverseDFS(&gragh);
	initQueue();
	traverseBFS(&gragh);
}

