/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 22, 2017
*
* adjacent matrix
* - 
* - 0-4-6 means arc[0][4] = 6
*
*/

#include <stdio.h>
#include <string.h>	// strlen strcpy
#include <ctype.h>	// isdigit
#include <stdlib.h> // malloc

#define VOID -1
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
void init (MGraph* gp, char* vStr, char* aStr) {
	// init vertexes
	int vertexNum = 0;
	for (char* cp = vStr; *cp != '\0'; cp++) {
		gp -> vertex[vertexNum++] = *cp;		
	}
	gp -> vertexNum = vertexNum;

	// init arcs
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			gp -> arc[i][j] = i == j ? 0 : VOID;
		}
	}
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
		printf("%s\n", dotArr[k]);
		split(numArr, dotArr[k], '-');
		int i = atoi(numArr[0]);
		int j = atoi(numArr[1]);
		gp -> arc[i][j] = atoi(numArr[2]);
	}

}
void printV (MGraph* gp) {
	printf("Vertex: ");
	for (int i = 0; i < gp -> vertexNum; i++) {
		printf("%c ", gp -> vertex[i]);
	}
	printf("\n");
}
void printA (MGraph* gp) {
	printf("Arc:\n");
	for (int i = 0; i < gp -> vertexNum; i++) {
		for (int j = 0; j < gp -> vertexNum; j++) {
			printf("%2d ", gp -> arc[i][j]);
		}
		printf("\n");
	}
}
void traverse (int a[]) {
	// for (int i = 0; i < LEN; i++) {
	// 	printf("%2d ", a[i]);
	// }
	// printf("\n");
}


main () {
	MGraph* gp = (MGraph*) malloc(sizeof(MGraph));
	init(gp, "abcde", "0-4-6,1-0-9,1-2-3,2-0-2,2-3-5,3-4-1");
	printV(gp);
	printf("\n");
	printA(gp);
}

