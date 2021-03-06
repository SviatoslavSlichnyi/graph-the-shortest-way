#include "search_graph.h"


void addVertexMinPath(MIN_PATH_LIST** list, int v)
{
    MIN_PATH_LIST* node = malloc(sizeof(MIN_PATH_LIST));
    node->v = v;
    node->next = NULL;

    if((*list) == NULL)
    {
        *list = node;
        return;
    }

    MIN_PATH_LIST* iterator = *list;
    while( iterator->next != NULL) iterator = iterator->next;
    iterator->next = node;

}




void edgeWasDiscovered(DiscEdges* discoveredEdges[], int x, int y)
{
    DiscEdges* node = malloc(sizeof(DiscEdges));
    node->y = y;
    node->next = discoveredEdges[x];
    discoveredEdges[x] = node;

    node = malloc(sizeof(DiscEdges));
    node->y = x;
    node->next = discoveredEdges[y];
    discoveredEdges[y] = node;
}
_Bool wasDiscoverd(DiscEdges* discoveredEdges[], int x, int y)
{
    for(DiscEdges* node = discoveredEdges[x]; node != NULL; node = node->next)
        if(node->y == y) return 1;

    return 0;
}
void addStepToPath(PATH** end, int y)
{
    PATH* node = malloc(sizeof(PATH));
    node->y = y;
    node->next = NULL;
    (*end)->next = node;
    *end = node;
}
void setEdgeUndiscovered(DiscEdges* discoveredEdges[], _Bool directed, int x, int y)
{
    DiscEdges* prev = discoveredEdges[x];
    if(prev == NULL) return;
    DiscEdges* node = prev->next;

    if(prev->y == y)
    {
        discoveredEdges[x] = prev->next;
        free(prev);
    }
    else {
        while(node != NULL)
        {
            if(node->y == y)
            {
                prev->next = node->next;
                free(node);
                break;
            }

            prev = prev->next;
            node = node->next;
        }
    }

    if(directed == 0)
        setEdgeUndiscovered(discoveredEdges, 1, y, x);
}
void deleteStepFromPath(PATH* node, PATH** end)
{
    if(node == NULL)
        puts("start == NULL");
    while(node != NULL && node != *end)
    {
        if(node->next == *end)
        {
            node->next = NULL;
            free(*end);
            *end = node;
            return;
        }

        node = node->next;
    }

    puts("Error: can't delete the last node in path");
}
void printPath(PATH* node)
{
    printf("The way: ");
    for(; node != NULL; node = node->next)
        printf(" %d", node->y);
    puts("");
}
void printDiscEdges(int nNodes, DiscEdges* discoveredEdges[])
{
    DiscEdges* edge;
    for(int i = 1; i <= nNodes; i++)
    {
        printf("Edge %d to: ", i);
        edge = discoveredEdges[i];
        while(edge != NULL)
        {
            printf(" %d", edge->y);
            edge = edge->next;
        }

        printf("\n");
    }
}

void saveMinPath(PATH* path, MIN_PATH* minPath, int sumOfWeitgh)
{
    minPath->sumWeight = sumOfWeitgh;

    while(path != NULL)
    {
        addVertexMinPath(&minPath->list, path->y);

        path = path->next;
    }
}

void searchPath(GRAPH* graph, DiscEdges* discoveredEdges[], PATH* start, PATH* end, int x, int v2, int* counter, MIN_PATH* minPath, int* sumWeight, int *numOfPaths)
{

    if(x == v2)
    {
        printf("\nsum of weight: %d\n", *sumWeight);
        printPath(start);
        (*numOfPaths)++;
    }

    if(x == v2 && *sumWeight < minPath->sumWeight)
    {
        saveMinPath(start, minPath, *sumWeight);
        return;
    }

    //list of adjacent vertices
    EDGENODE* aroundVertexes = graph->edges[x];//get a list of neighbors of x vertex


    //go through each neighbor y node
    for (int y;aroundVertexes != NULL; aroundVertexes = aroundVertexes->next)
    {
        //get another neighbor y  for x
        y = aroundVertexes->y;

        //if it face into undiscovered edge
        if (wasDiscoverd(discoveredEdges, x, y) == 0)
        {
            //set edge label "discovered"
            edgeWasDiscovered(discoveredEdges, x, y);
            //note this node to path
            addStepToPath(&end, y);
            //add one step to path counter
            *counter += 1;

            *sumWeight += aroundVertexes->weigth;

            //go next
            searchPath(graph, discoveredEdges, start, end, y, v2, counter, minPath, sumWeight, numOfPaths);

            *sumWeight -= aroundVertexes->weigth;

            //set edge label "undiscovered"
            setEdgeUndiscovered(discoveredEdges, graph->isDirected, x, y);
            //delete one step from path
            deleteStepFromPath(start, &end);
            //decrease counter of path
            *counter -= 1;
        }

    }


}
void initializeSearch(GRAPH* graph, DiscEdges* discoveredEdges[], PATH** start, PATH** end, int firstPoint)
{
    for(int i = 1; i <= graph->nNodes; i++)
        discoveredEdges[i] = NULL;


    PATH* firstNode = malloc(sizeof(PATH));
    firstNode->y = firstPoint;
    firstNode->next = NULL;
    *end = firstNode;
    *start = *end;
}

void print(MIN_PATH* minPath)
{
    printf("Sum of weight: %d\n", minPath->sumWeight);
    MIN_PATH_LIST* node = minPath->list;

    printf("The way: ");
    while(node != NULL)
    {
        printf(" %d", node->v);

        node = node->next;
    }
}
void deleteMinPath(MIN_PATH* minPath)
{
    MIN_PATH_LIST* node = minPath->list;

    while (node != NULL)
    {
        MIN_PATH_LIST* del = node;
        node = node->next;
        free(del);
    }
}

void startSearch(GRAPH* graph, int v1, int v2)
{
    DiscEdges** discoveredEdges = malloc(sizeof(DiscEdges*) * (graph->nNodes+1) );//відкрита// побували чи ні
    PATH *start, *end;//шлях який пройшов алгоритм
    int numOfPaths = 0;
    int counter = 0;
    int startWeight = 0;
    MIN_PATH minPath;
    minPath.sumWeight = INT_MAX;
    minPath.list = NULL;

    puts("\tpaths:");

    initializeSearch(graph, discoveredEdges, &start, &end, v1);
    searchPath(graph, discoveredEdges, start, end, v1, v2, &counter, &minPath, &startWeight, &numOfPaths);

    printf("\n\tFound way:\n");
    print(&minPath);
    deleteMinPath(&minPath);

    printf("\n%d paths were found\n", numOfPaths);
    free(discoveredEdges);
}