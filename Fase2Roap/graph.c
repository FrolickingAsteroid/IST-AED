#include "graph.h"
#include "projectHeader.h"

/**
 * @brief Função de inicialização do grafo
 * 
 * @param v número de vértices no grafo
 * @return graph* retorna ponteiro para o grafo
 */
graph *makeGraph(int v)
{
    graph *G;

    /*alocação do grafo*/

    if ((G = (graph *)malloc(sizeof(graph))) == NULL)
        exit(EXIT_FAILURE);

    G->numVertices = v;

    /*alocação da lista de adjacências*/

    if ((G->AdjList = (node **)malloc(G->numVertices * sizeof(node *))) == NULL)
        exit(EXIT_FAILURE);

    /*inicialização do array de ponteiros a NULL*/

    for (int i = 0; i < v; i++)
        G->AdjList[i] = NULL;

    return G;
}

/**
 * @brief Função que adiciona um novo nó à lista de adjacências, como o grafo não é direcionado ligamos o node1 ao node2 e vice versa
 * 
 * @param G Ponteiro para o grafo
 * @param x coordenada das abcissas da célula de link
 * @param y coordenada das ordenadas da célula de link
 * @param w peso da céluça de link
 * @param node1 e node2 nós a ser ligados
 */
void addEdge(graph *G, int x, int y, int w, int node1, int node2)
{
    /*alocação e inicialização dos nós a serem ligados*/

    node *newNode = createNode(node2, x, y, w);
    node *newNode2 = createNode(node1, x, y, w);

    /*colocação do novo nó no topo da lista e atualização do ponteiro head*/

    newNode->next = G->AdjList[node1];
    G->AdjList[node1] = newNode;

    newNode2->next = G->AdjList[node2];
    G->AdjList[node2] = newNode2;
}

/**
 * @brief Função de alocação e inicialização dos nós a serem ligados na função addEdge
 * 
 * @param v "cor" do vértice a ser ligado
* @param x coordenada das abcissas da célula de link
 * @param y coordenada das ordenadas da célula de link
 * @param w peso da céluça de link
 * @return node* novo nó
 */
node *createNode(int v, int x, int y, int w)
{
    node *newNode = NULL;

    /*alocação do novo nó e da componente edge, link*/

    if ((newNode = (node *)malloc(sizeof(node))) == NULL)
        exit(EXIT_FAILURE);

    if ((newNode->edge = (edge *)malloc(sizeof(edge))) == NULL)
        exit(EXIT_FAILURE);

    /*inicialização do nó*/

    placeNode(newNode, v, x, y, w);

    newNode->next = NULL;
    
    return newNode;
}

/**
 * @brief Função de inicialização dos nós
 * 
 * @param Node novo nó a ser inicializado
 * @param v "cor" do vértice a ser ligado
* @param x coordenada das abcissas da célula de link
 * @param y coordenada das ordenadas da célula de link
 * @param w peso da céluça de link
 */
void placeNode(node *Node, int v, int x, int y, int w)
{
    Node->vertex = v;
    Node->edge->x = x;
    Node->edge->y = y;
    Node->edge->weigth = w;
}
/**
 * @brief Verifica se um dado nó já existe na lista, se é necessária nova alocação ou somente substituição da célula de ligação
 * 
 * @param G ponteiro para o grafo
 * @param node1 
 * @param node2 
* @param x coordenada das abcissas da célula de link
 * @param y coordenada das ordenadas da célula de link
 * @param w peso da céluça de link
 * @return int  1 para alocação, 0 para ficar não alocação
 */
int checkNode(graph *G, int node1, int node2, int x, int y, int w)
{
    node *aux = NULL;

    /*percorre as ligações do primeiro nó*/

    for (aux = G->AdjList[node1]; aux != NULL; aux = aux->next)
    {
        /*se o nó já existir verificar se o peso atual é maior que o novo*/

        if (aux->vertex == node2)
        {
            if (aux->edge->weigth > w)
            {
                /*reinicializa o nó*/
                placeNode(aux, node2, x, y, w); 

                /*procura o outro nó na lista do segundo e procede à reinicialização*/

                for (aux = G->AdjList[node2]; aux->vertex != node1; aux = aux->next);
                placeNode(aux, node1, x, y, w);
            }

            /*Não há necessidade de alocação*/
            return 0; 
        }
    }

    /*é necessário alocar*/
    return 1; 
}

/**
  * @brief Liberta a lista de adjacências de cada um dos nós
  * 
  * @param adj ponteiro para a cabeça da lista de adjacências
  */
void freeAdjList(node *adj)
{
    node *aux, *next;

    for (aux = adj; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux->edge);
        free(aux);
    }
}

/**
 * @brief Liberta o grafo
 * 
 * @param G ponteiro para o grafo alocado
 */
void freeGraph(graph *G)
{
    for (int i = 0; i < G->numVertices; i++)
    {
        freeAdjList((G->AdjList[i]));
    }
    free(G->AdjList);
    free(G);
}
