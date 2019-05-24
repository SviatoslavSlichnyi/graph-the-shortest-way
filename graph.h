#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#define MAXV 50

typedef struct edgenode {
    int y;
    struct edgenode *next;
} EDGENODE;

typedef struct graph {
    struct edgenode *edges[MAXV+1]; //ребра
    int degree[MAXV+1]; // степінь вершини
    int nNodes; //кількість вузлів
    int nEdges; //кількість ребер
    _Bool isDirected; //орієнтований
} GRAPH;

void initializeGraph(GRAPH*, _Bool);
void readGraph(GRAPH*, _Bool);
void insertEdge(GRAPH*, int, int, _Bool);
void printGraph(GRAPH*);
void setGraph(GRAPH* graph);

#endif //GRAPHS_GRAPH_H
