/*
* author: chenzhi <chenzhibupt@qq.com>
* date: June 18, 2017
*
* mininum cost spanning tree
* - connect every vertex with mininum cost
*
* 1. prim
* - start from 0
* - traverse all reachable vertexes, go to neareast one
* - update list of reachable vertexes
* 
* 2. kruskal
* - generate descendant list of all edges
* - traverse all edges
* - if edge will not cause a ring, obsorb it into tree
* 
* time comlexity : n^2  vs  eloge
* so : many edges, use prim; few edges, use kruskal.
*/

#include <stdio.h>
#include <string.h>  // strlen strcpy
#include <ctype.h>  // isdigit
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

void prim (MGraph* gp) {
  printf("Mininum Cost Spanning Tree - Prim:\n");
  printf("from - to - cost\n");

  int vertexNum = gp -> vertexNum; 
  int from[vertexNum];
  int cost[vertexNum];

  // start from 0
  for (int i = 0; i < vertexNum; i++) {
    from[i] = 0;
  }
  for (int i = 0; i < vertexNum; i++) {
    cost[i] = gp -> arc[0][i];
  }

  // main loop
  for (int k = 1; k < vertexNum; k++) {

    // look for best choice
    int minCost = INFINITY;
    int curr = 0;
    for (int i = 0; i < vertexNum; i++) {
      if (cost[i] == 0) continue;      // visited
      if (cost[i] >= minCost) continue;   // bad choice
      minCost = cost[i];
      curr = i;
    }
    printf("%4d - %2d - %2d\n", from[curr], curr, minCost);

    // prepare for next round
    cost[curr] = 0;  // mark it as visited
    for (int i = 0; i < vertexNum; i++) {
      int currCost = gp -> arc[curr][i];
      if (currCost == 0) continue;     //self
      if (currCost >= cost[i]) continue;   // bad choice
      cost[i] = currCost;
      from[i] = curr;
    }
  }
}


typedef struct {
  int sta;
  int end;
  int weight;  
} EdgeNode;

void initEdgeList (MGraph* gp, EdgeNode edgeList[]) {
  int k = 0;  // edgeList index
  for (int i = 0; i < gp -> vertexNum; i++) {
    for (int j = 0; j < gp -> vertexNum; j++) {
      int weight = gp -> arc[i][j];
      if (weight == 0 || weight == INFINITY) continue;
      edgeList[k].sta = i;
      edgeList[k].end = j;
      edgeList[k].weight = weight;
      k++;
    }
  }
}
void swapEdgeNode (EdgeNode edgeList[], int i, int j) {
  if (i == j) return;
  int sta       = edgeList[i].sta;
  int end       = edgeList[i].end;
  int weight       = edgeList[i].weight;
  edgeList[i].sta   = edgeList[j].sta;
  edgeList[i].end   = edgeList[j].end;
  edgeList[i].weight   = edgeList[j].weight;
  edgeList[j].sta   = sta;
  edgeList[j].end   = end;
  edgeList[j].weight   = weight;
}
void sortEdgeList (EdgeNode edgeList[], int l, int r) {
  if (l >= r) return;
  int pivot = (l + r) / 2;
  int pivotWeight = edgeList[pivot].weight;
  swapEdgeNode(edgeList, l, pivot);
  int reader = l + 1;
  int writer = l + 1;
  for ( ; reader <= r; reader++) {
    if (edgeList[reader].weight >= pivotWeight) continue;
    swapEdgeNode(edgeList, writer++, reader);
  }
  writer--;
  swapEdgeNode(edgeList, l, writer);

  sortEdgeList(edgeList, l, writer - 1);
  sortEdgeList(edgeList, writer + 1, r);
}
void printEdgeList (EdgeNode edgeList[], int len) {
  printf("Edge List:\n");
  printf("from - to - weight\n");
  for (int i = 0; i < len; i++) {
    int sta   = edgeList[i].sta;
    int end   = edgeList[i].end;
    int weight   = edgeList[i].weight;
    printf("%4d - %2d - %2d\n", sta, end, weight);
  }
  printf("\n\n");
}
int gotoEnd (int i, int parent[]) {
  while (parent[i] != -1) {
    i = parent[i];
  };
  return i;
}
void kruskal (MGraph* gp) {
  EdgeNode edgeList[gp -> arcNum];
  initEdgeList(gp, edgeList);
  sortEdgeList(edgeList, 0, gp -> arcNum - 1);
  printEdgeList(edgeList, gp -> arcNum);

  int parent[gp -> vertexNum];
  for (int i = 0; i < gp -> vertexNum; i++) {
    parent[i] = -1;
  }

  printf("Mininum Cost Spanning Tree - Kruskal:\n");
  printf("from - to - cost\n");
  for (int i = 0; i < gp -> arcNum; i++) {
    EdgeNode edge = edgeList[i];
    int sta = gotoEnd(edge.sta, parent);
    int end = gotoEnd(edge.end, parent);
    if (sta == end) continue;
    parent[sta] = end;
    printf("%4d - %2d - %2d\n", edge.sta, edge.end, edge.weight);
  }
}



main () {
  MGraph gragh;
  // see 7-3.jpg
  init(&gragh, (char*)("012345678"), (char*)("0-1-10,0-5-11,1-0-10,1-2-18,1-6-16,1-8-12,2-1-18,2-3-22,2-8-8,3-2-22,3-4-20,3-6-24,3-7-16,3-8-21,4-3-20,4-5-26,4-7-7,5-0-11,5-4-26,5-6-17,6-1-16,6-3-24,6-5-17,6-7-19,7-3-16,7-4-7,7-6-19,8-1-12,8-2-8,8-3-21"));
  printArc(&gragh);
  printMatrix(&gragh);
  
  printf("\n\n");
  
  prim(&gragh);  
  printf("\n\n");
  kruskal(&gragh);
}
