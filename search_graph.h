#ifndef GRAPHS_SEARCH_EULER_H
#define GRAPHS_SEARCH_EULER_H

//saving edges which were discovered
typedef struct discoveredEdges {
    int y;
    struct discoveredEdges* next;
} DiscEdges;
//saving the path in graph
typedef struct path {
    int y;
    struct path* next;
}PATH;

typedef struct minpathlist {
    int v;
    struct minpathlist* next;
}MIN_PATH_LIST;
typedef struct minpath {
    int sumWeight;
    MIN_PATH_LIST* list;
}MIN_PATH;


//set edge label "discovered"
void edgeWasDiscovered(DiscEdges* discoveredEdges[], int x, int y);
//check where the edge discovered
_Bool wasDiscoverd(DiscEdges* discoveredEdges[], int x, int y);
//add to path node id
void addStepToPath(PATH** end, int y);
//set edge label "undiscovered"
void setEdgeUndiscovered(DiscEdges* discoveredEdges[], _Bool directed, int x, int y);
//delete the last step from path
void deleteStepFromPath(PATH* node, PATH** end);
//print into console found path
void printPath(PATH* node);
//print edges to see how program working
void printDiscEdges(int nNodes, DiscEdges* discoveredEdges[]);
//recursion function in order to find path

//initialize needable variables
void initializeSearch(GRAPH* graph, DiscEdges* discoveredEdges[], PATH** start, PATH** end, int firstPoint);

//the main function to call
void startSearch(GRAPH* graph, int v1, int v2);

#endif //GRAPHS_SEARCH_EULER_H
