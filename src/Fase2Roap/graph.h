/**
 * @file graph.h
 * 
 * @brief funções responsáveis pela construção do grafo
 * 
 */

#ifndef GRAPH_H_ 
#define GRAPH_H_

typedef struct edge
{
    int x;              /*abcissa da ligação entre nós*/
    int y;              /*ordenada da ligação entre nós*/
    int weigth;         /*custo da ligação entre nós*/
} edge;

typedef struct node
{
    int vertex;         /*vértice do grafo*/
    edge *edge;         /*ligação entre nós*/
    struct node *next;  /*ponteiro para próximo nó*/
} node;

typedef struct graph
{
    int numVertices;    /*número de vértices no grafo*/
    node **AdjList;     /*array de ponteiros para lista de adjacências de cada nó*/
} graph;

/*inicialização*/
graph* makeGraph(int v);
node *createNode(int v, int x, int y, int w);

/*ligação*/
void addEdge(graph *G, int x, int y, int w, int node1, int node2);
void placeNode(node *Node, int v, int x, int y, int w);
int checkNode(graph *G, int node1, int node2, int x, int y, int w);

/*libertação*/
void freeGraph(graph *G);
void freeAdjList(node *adj);


#endif