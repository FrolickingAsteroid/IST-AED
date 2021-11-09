#include "projectHeader.h"
#include "queue.h"
#include "graph.h"

/**
 * @brief Controla a adição de novas ligações entre nós
 * 
 * @param breakable direção pela qual a parede é quebrável
 * @param matrix labirinto
 * @param x abcissa da parede
 * @param y ordenada da parede
 * @param w peso da parede
 */
void check_neighbours(graph *G, int breakable, int **matrix, int x, int y, int w)
{
    int node1 = 0, node2 = 0;

    /********************* análise de paredes quebŕaveis em duas direções ***************************************/
    if (breakable == 3)
    {
        node1 = matrix[x - 2][y - 1], node2 = matrix[x][y - 1];
        if (node1 == node2)
            return;

        /*o vértice será o módulo da sua cor com desfazamento de 2*/
        node1 = abs(node1 + 2);
        node2 = abs(node2 + 2);

        /*verifica se os nós já foram colocados e se a parede apresenta um custo mais vaixo*/
        if (checkNode(G, node1, node2, x, y, w) == 1)
            addEdge(G, x, y, w, node1, node2);

        node1 = matrix[x - 1][y - 2], node2 = matrix[x - 1][y];
        if (node1 == node2)
            return;

        node1 = abs(node1 + 2);
        node2 = abs(node2 + 2);

        if (checkNode(G, node1, node2, x, y, w) == 1)
            addEdge(G, x, y, w, node1, node2);

        return;
    }
    /************************************************************************************************************/

    if (breakable == 1)
        node1 = matrix[x - 2][y - 1], node2 = matrix[x][y - 1];

    if (breakable == 2)
        node1 = matrix[x - 1][y - 2], node2 = matrix[x - 1][y];

    if (node1 == node2)
        return;

    node1 = abs(node1 + 2);
    node2 = abs(node2 + 2);

    if (checkNode(G, node1, node2, x, y, w) == 1)
        addEdge(G, x, y, w, node1, node2);
}

/**
 * @brief verifica a cor de uma dada célula
 * 
 * @param nodes: nodes: maze, nome passado para nodes de forma a facilitar o pensamento do grafo
 * @param priority_cell: célula a avaliar
 * @return int result: retorna a cor da célula (cinzenta > 0; branca = 0; preta = -1)
 */
int is_color(int **nodes, int x, int y)
{
    int result = 0;

    result = nodes[x - 1][y - 1]; 

    return result;
}

/**
 * @brief aplicação do algoritmo bfs para pintura das salas do labirinto, entendemos por salas áreas compostas por células brancas (peso 0) 
 *        limitadas por paredes (células cinzentas e pretas)
 * 
 * @param matrix labirinto que contêm as salas
 * @param fin célula de destino
 * @param row_size número de linhas
 * @param col_size número de colunas
 * @param numbcell tamanho da fila a alocar
 * @param color cor da sala a pintar
 * @param i abcissa da célula de início
 * @param j ordenada da célula de início
 * @return int retorna -1 se não encontrou o nó de destino e a cor do nó para o contrário
 */
int bfs(int **matrix,int *fin, int row_size, int col_size, int numbcell, int color, int i, int j)
{
    int currentcell[2] = {0, 0};
    int adjx = 0, adjy = 0, xy = 0, destination = -1;

    /*vetores de movimentos*/
    int dRow[] = {-1, 0, 1, 0}, dCol[] = {0, 1, 0, -1};
    queue *q = createQueue(numbcell);

    matrix[i][j] = color;
    enqueue(q, i, j, numbcell);

    /*enquanto a fila não estiver vazia mantemos a procura*/

    while (!isEmpty(q)) 
    {
        /*atualização do caminho*/

        currentcell[0] = dequeue(q, xy), xy = 1; 
        currentcell[1] = dequeue(q, xy);

        if (currentcell[0] == (fin[0] - 1) && currentcell[1] == (fin[1] - 1))
            destination = color;

        for (int w = 0; w < 4; w++)
        {
            adjx = currentcell[0] + dRow[w];
            adjy = currentcell[1] + dCol[w];

            if (isValid((adjx + 1), (adjy + 1), matrix, row_size, col_size))
            {   /*vizinhos válidos são colocados na fila e marcados como visitados*/
            
                enqueue(q, adjx, adjy, numbcell); 
                matrix[adjx][adjy] = color;
            }
        }
        xy = 0;
    }
    free_queue(q);
    return destination;
}
