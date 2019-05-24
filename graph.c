#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void initializeGraph(GRAPH* graph, _Bool direction)
{
    graph->nNodes = 0;
    graph->nEdges = 0;
    graph->isDirected = direction;
    for(int i = 1; i <= MAXV; i++) graph->degree[i] = 0;
    for(int i = 1; i <= MAXV; i++) graph->edges[i] = NULL;
}

void readGraph(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed);

    //кільеість ребер
    int x, y, weight; //ребро від .. до ..

    printf("number of nodes: ");
    scanf("%d", &(graph->nNodes));
    //graph->nNodes = 4;
    printf("number of edges: ");
    scanf("%d", &(graph->nEdges));
    //graph->nEdges = 4;
    fflush(stdin);

    for(int i = 1, n = graph->nEdges; i <= n; i++)
    {
        printf("x y <weight>: ");
        scanf("%d %d %d", &x, &y, &weight);
        fflush(stdin);
        insertEdge(graph, x, y, weight, directed);
    }
}

void insertEdge(GRAPH* graph, int x, int y, int weight, _Bool directed)
{
    EDGENODE* edge;
    edge = malloc(sizeof(EDGENODE));
    if(edge == NULL)
        exit(400);

    edge->y = y;
    edge->weigth = weight;
    edge->next = graph->edges[x];//стає початком

    graph->edges[x] = edge;
    (graph->degree[x])++;//степінь вузла (кількість

    if(directed == 0)
        insertEdge(graph, y, x, weight, 1);
    else
        graph->nEdges++;
}
void printGraph(GRAPH* graph)
{
    EDGENODE* edge;
    for(int i = 1; i <= graph->nNodes; i++)
    {
        printf("%d: ", i);
        edge = graph->edges[i];
        while(edge != NULL)
        {
            printf(" %d(%d)", edge->y, edge->weigth);
            edge = edge->next;
        }

        printf("\n");
    }

}

void setSomeGraph(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed);

    graph->nNodes = 5;
    graph->nEdges = 5;

    insertEdge(graph, 1, 2, 5, directed);
    insertEdge(graph, 1, 5, 10, directed);
    insertEdge(graph, 2, 3, 100, directed);
    insertEdge(graph, 3, 4, 5, directed);
    insertEdge(graph, 4, 5, 2, directed);
}