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
    int x, y; //ребро від .. до ..

    printf("number of nodes: ");
    scanf("%d", &(graph->nNodes));
    //graph->nNodes = 4;
    printf("number of edges: ");
    scanf("%d", &(graph->nEdges));
    //graph->nEdges = 4;
    fflush(stdin);

    for(int i = 1, n = graph->nEdges; i <= n; i++)
    {
        printf("x y: ");
        scanf("%d %d", &x, &y);
        fflush(stdin);
        insertEdge(graph, x, y, directed);
    }
    /*insertEdge(graph, 1, 2, directed);
    insertEdge(graph, 2, 3, directed);
    insertEdge(graph, 3, 4, directed);
    insertEdge(graph, 4, 1, directed);*/
}

void insertEdge(GRAPH* graph, int x, int y, _Bool directed)
{
    EDGENODE* edge;
    edge = malloc(sizeof(EDGENODE));
    if(edge == NULL)
        exit(400);

    edge->y = y;
    edge->next = graph->edges[x];//стає початком

    graph->edges[x] = edge;
    (graph->degree[x])++;//степінь вузла (кількість

    if(directed == 0)
        insertEdge(graph, y, x, 1);
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
            printf(" %d", edge->y);
            edge = edge->next;
        }

        printf("\n");
    }

}
void setGraph(GRAPH* graph)
{
    EDGENODE* edge;
    for(int i = 1; i <= graph->nNodes; i++)
    {
        printf("%d: ", i);
        edge = graph->edges[i];
        while(edge != NULL)
        {
            printf(" %d", edge->y);
            edge = edge->next;
        }

        printf("\n");
    }

}

void setSomeGraph(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed);

    graph->nNodes = 7;
    graph->nEdges = 7;

    insertEdge(graph, 1, 2, directed);
    insertEdge(graph, 1, 3, directed);
    insertEdge(graph, 3, 4, directed);
    insertEdge(graph, 2, 5, directed);
    insertEdge(graph, 5, 6, directed);
    insertEdge(graph, 4, 6, directed);
    insertEdge(graph, 6, 7, directed);
}