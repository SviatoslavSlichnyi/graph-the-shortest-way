#include <stdio.h>
#include "graph.c"
#include "search_graph.c"



int main()
{
    GRAPH graph;
    //readGraph(&graph, 1);
    setSomeGraph(&graph, 1);

    printGraph(&graph);


    startSearch(&graph, 1, 6);


    puts("");
    //system("pause");
    return 0;
}