#include "graph.h"
#include "projectHeader.h"

/**
 * @brief 
 * 
 * @param G 
 * @param v 
 */
graph* makeGraph(int v)
{
    graph *G;
    if ((G = (graph *)malloc(sizeof(graph))) == NULL)
        exit(EXIT_FAILURE);

    G->numVertices = v;

    if ((G->AdjList = (node **)malloc(G->numVertices * sizeof(node *))) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < v; i++)
        G->AdjList[i] = NULL;
    
    return G;
}

/**
 * @brief 
 * 
 * @param G 
 * @param x 
 * @param y 
 * @param w 
 * @param node1 
 * @param node2 
 */
void addEdge(graph *G, int x, int y, int w, int node1, int node2)
{
    node *newNode = createNode(node2, x, y, w);
    node *newNode2 = createNode(node1, x, y, w);

    newNode->next = G->AdjList[node1];
    G->AdjList[node1] = newNode;

    newNode2->next = G->AdjList[node2];
    G->AdjList[node2] = newNode2;
}

/**
 * @brief Create a Node object
 * 
 * @param v 
 * @param x 
 * @param y 
 * @param w 
 * @return node* 
 */
node *createNode(int v, int x, int y, int w)
{
    node *newNode = NULL;
    if ((newNode = (node *)malloc(sizeof(node))) == NULL)
        exit(EXIT_FAILURE);

    if ((newNode->edge = (edge *)malloc(sizeof(edge))) == NULL)
        exit(EXIT_FAILURE);

    placeNode(newNode, v, x, y, w);

    return newNode;
}

/**
 * @brief 
 * 
 * @param Node 
 * @param v 
 * @param x 
 * @param y 
 * @param w 
 */
void placeNode(node *Node, int v, int x, int y, int w)
{
    Node->vertex = v;
    Node->edge->x = x;
    Node->edge->y = y;
    Node->edge->weigth = w;

    Node->next = NULL;
    Node->prev = NULL;
}
/**
 * @brief 
 * 
 * @param G 
 * @param node1 
 * @param node2 
 * @param x 
 * @param y 
 * @param w 
 * @return int 
 */
int checkNode(graph *G, int node1, int node2, int x, int y, int w)
{
    node *aux = NULL;

    for (aux = G->AdjList[node1]; aux != NULL; aux = aux->next)
    {
        if (aux->vertex == node2){
            if (aux->edge->weigth > w){
    
                placeNode(aux, node2, x, y, w);
                for (aux = G->AdjList[node2]; aux->vertex == node1; aux = aux->next)
                    ;
                placeNode(aux, node1, x, y, w);
            }
            return 0; /*there is no need for allocation*/
        }
    
    }
    return 1; /*there is need for allocation*/
}
 /**
  * @brief 
  * 
  * @param adj 
  */
void freeAdjList(node *adj)
{
    node *aux, *next;

    for (aux = adj; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux);
    }
}
