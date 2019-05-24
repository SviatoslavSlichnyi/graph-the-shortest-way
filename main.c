#include <stdio.h>
#include "graph.c"
#include "search_graph.c"



int main()
{
    GRAPH graph;
    readGraph(&graph, 1);
    //setSomeGraph(&graph, 1);

    printGraph(&graph);


    startSearch(&graph, 1, 4);


    puts("");
    //system("pause");
    return 0;
}
/*
5
5
1 2 5
1 5 10
2 3 100
3 4 5
5 4 2
 */