#ifndef GRAPH_H_ /* Include guard */
#define GRAPH_H_

typedef struct edge
{
    int x;
    int y;
    int weigth;
} edge;

typedef struct node
{
    int vertex;
    edge *edge;
    struct node *next;
    struct node *prev;
} node;

typedef struct graph
{
    int numVertices;
    node **AdjList;
} graph;

graph* makeGraph(int v);
void addEdge(graph *G, int x, int y, int w, int node1, int node2);
node *createNode(int v, int x, int y, int w);
void placeNode(node *Node, int v, int x, int y, int w);
int checkNode(graph *G, int node1, int node2, int x, int y, int w);
void freeAdjList(node *adj);

#endif