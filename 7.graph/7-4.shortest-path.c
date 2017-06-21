/*
* author: chenzhi <chenzhibupt@qq.com>
* data: June 18, 2017
*
* shortest path
* - figure out cost of v0 to every vertex
*
* 1. dijkstra
* - similar to prim
* - traverse all reachable vertexes, go to neareast one
* - update list of reachable vertexes
* - from v0 to any vertex, time complexity is n^2
* - so from any to any, time complexity will be n^3
*
* 2. floyd
* - create two matrix, cost and path, traverse them
* - time complexity is n^3
*
*/

#include <stdio.h>
#include <string.h>	// strlen strcpy
#include <ctype.h>	// isdigit
#include <stdlib.h> // malloc

#define INFINITY 65536
#define VMAX 20

typedef struct {
	char vertex[VMAX];
	int arc[VMAX][VMAX];
	int vertexNum;
	int arcNum;
} MGraph;


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
void init (MGraph* gp, char* vStr, char* aStr) {
	// init vertexes
	int vertexNum = 0;
	for (char* cp = vStr; *cp != '\0'; cp++) {
		gp -> vertex[vertexNum++] = *cp;		
	}
	gp -> vertexNum = vertexNum;

	// init arc matrix
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			gp -> arc[i][j] = i == j ? 0 : INFINITY;
		}
	}

	// get arcNum
	int arcNum = 0;
	for (char* cp = aStr; *cp != '\0'; cp++) {
		if (*cp == ',') arcNum++;
	}
	arcNum++;
	gp -> arcNum = arcNum;

	// fill arc matrix
	char* dotArr[arcNum];
	char* numArr[3];
	split(dotArr, aStr, ',');
	for (int k = 0; k < arcNum; k++) {
		split(numArr, dotArr[k], '-');
		int i = atoi(numArr[0]);
		int j = atoi(numArr[1]);
		gp -> arc[i][j] = atoi(numArr[2]);
	}
	freeArr(dotArr, arcNum);
	freeArr(numArr, 3);
}
void printMatrix (MGraph* gp) {
	printf("Matrix:\n");
	for (int i = 0; i < gp -> vertexNum; i++) {
		for (int j = 0; j < gp -> vertexNum; j++) {
			int weight = gp -> arc[i][j];
			if (weight == INFINITY) {
				printf(" * ");
			} else {
				printf("%2d ", weight);				
			}
		}
		printf("\n");
	}
	printf("\n");
}
void printArc (MGraph* gp) {
	printf("Arc:\n");
	for (int i = 0; i < gp -> vertexNum; i++) {
		printf("%c - ", gp -> vertex[i]);
		for (int j = 0; j < gp -> vertexNum; j++) {
			int weight = gp -> arc[i][j];
			if(weight == INFINITY || weight == 0) continue;
			printf("%c ", gp -> vertex[j]);
		}
		printf("\n");
	}
	printf("\n");
}


typedef int boolean;
#define TRUE  1
#define FALSE 0

void dijkstra (MGraph* gp) {
	int vNum = gp -> vertexNum;
	int path[vNum];			// prev vertex index
	int cost[vNum];			// min cost from v0
	boolean visited[vNum];	// vertex was visited or not

	// init
	for (int i = 0; i < vNum; i++) {
		path[i] = 0;
	}
	cost[0] = 0;
	for (int i = 1; i < vNum; i++) {
		cost[i] = gp -> arc[0][i];
	}
	visited[0] = TRUE;
	for (int i = 1; i < vNum; i++) {
		visited[i] = FALSE;
	}

	// main loop
	for (int k = 0; k < vNum; k++) {
		int minCost = INFINITY;
		int minIndex = 0;
		// find min cost vertex
		for (int i = 1; i < vNum; i++) {
			if (visited[i]) continue;
			if (cost[i] >= minCost) continue;
			minCost = cost[i];
			minIndex = i;
		}
		visited[minIndex] = TRUE;
		// update cost array
		for (int i = 1; i < vNum; i++) {
			if (visited[i]) continue;
			int newCost = gp -> arc[minIndex][i] + cost[minIndex];
			if (newCost >= cost[i]) continue;
			cost[i] = newCost;
			path[i] = minIndex;
		}
	}

	// print result
	printf("Dijkstra - From v0:\n");
	printf("Index : ");
	for (int i = 0; i < vNum; i++) {
		printf("%3d", i);
	}
	printf("\n");
	printf("Cost  : ");
	for (int i = 0; i < vNum; i++) {
		printf("%3d", cost[i]);
	}
	printf("\n");
	printf("Path  : ");
	for (int i = 0; i < vNum; i++) {
		printf("%3d", path[i]);
	}
}

void floyd (MGraph* gp) {
	int vNum = gp -> vertexNum;
	int cost[vNum][vNum];
	int path[vNum][vNum];
	
	// init
	for (int i = 0; i < vNum; i++) {
		for (int j = 0; j < vNum; j++) {
			cost[i][j] = gp -> arc[i][j];
			path[i][j] = j;
		}
	}
	// main loop
	for (int k = 0; k < vNum; k++) {
		for (int i = 0; i < vNum; i++) {
			for (int j = 0; j < vNum; j++) {
				int newCost = cost[i][k] + cost[k][j];
				if (cost[i][j] <= newCost) continue;
				cost[i][j] = newCost;
				path[i][j] = path[i][k];
			}
		}
	}
	// print result
	printf("Floyd - Cost Matrix:\n");
	for (int i = 0; i < vNum; i++) {
		for (int j = 0; j < vNum; j++) {
			printf("%3d", cost[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("Floyd -  Path Matrix:\n");
	for (int i = 0; i < vNum; i++) {
		for (int j = 0; j < vNum; j++) {
			printf("%3d", path[i][j]);
		}
		printf("\n");
	}
}


main () {
	MGraph gragh;
	// see 7-4.jpg
	init(&gragh, (char*)("012345678"), (char*)("0-1-1,0-2-5,1-0-1,1-2-3,1-3-7,1-4-5,2-0-5,2-1-3,2-4-1,2-5-7,3-1-7,3-4-2,3-6-3,4-1-5,4-2-1,4-3-2,4-5-3,4-6-6,4-7-9,5-2-7,5-4-3,5-7-5,6-3-3,6-4-6,6-7-2,6-8-7,7-4-9,7-5-5,7-6-2,7-8-4,8-6-7,8-7-4"));
	printArc(&gragh);
	printMatrix(&gragh);
	
	printf("\n\n");
	
	dijkstra(&gragh);
	printf("\n\n");
	floyd(&gragh);
}
