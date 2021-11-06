#include "projectHeader.h"
#include "queue.h"
#include "graph.h"

/**
 * @brief 
 * 
 * @param breakable 
 * @param matrix 
 * @param x 
 * @param y 
 * @return int 
 */
void check_neighbours(graph *G, int breakable, int **matrix, int x, int y, int w)
{
    int node1 = 0, node2 = 0;

    if (breakable == 1)
        node1 = matrix[x - 2][y - 1], node2 = matrix[x][y - 1];
    else if (breakable == 2)
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
 * @brief Implementação do algorítmo bfs com objetivo de cumprir o estipulado no modo A6, verifica se duas células se encontram na mesma sala
 * 
 * @param matrix: maze, matriz a ser avaliada
 * @param vis: matriz de visitados, garante que uma dada célula não seja visitada duas vezes
 * @param str: starting cell
 * @param fin: last cell
 * @param numbcell: número de células coloridas dentro do tabuleiro
 * @param row_size: número de linhas
 * @param col_size: número de colunas
 * @return int: 0 = não estão na mesma sala, 1 = estão na mesma sala
 */
int bfs(int **matrix,int *fin, int row_size, int col_size, int numbcell, int color, int i, int j)
{
    int currentcell[2] = {0, 0}, xy = 0, destination = -1;
    int adjx = 0, adjy = 0;
    int dRow[] = {-1, 0, 1, 0}, dCol[] = {0, 1, 0, -1}; /*vetores de movimentos*/
    queue *q = createQueue(numbcell);

    matrix[i][j] = color;
    enqueue(q, i, j, numbcell);

    while (!isEmpty(q)) /*enquanto a fila não estiver vazia mantemos a procura*/
    {

        currentcell[0] = dequeue(q, xy), xy = 1; /*atualização do caminho*/
        currentcell[1] = dequeue(q, xy);

        if (currentcell[0] == (fin[0] - 1) && currentcell[1] == (fin[1] - 1))
            destination = color;

        for (int w = 0; w < 4; w++)
        {
            adjx = currentcell[0] + dRow[w];
            adjy = currentcell[1] + dCol[w];

            if (isValid((adjx + 1), (adjy + 1), matrix, row_size, col_size))
            {
                enqueue(q, adjx, adjy, numbcell); /*vizinhos válidos são colocados na fila e marcados como visitados*/
                matrix[adjx][adjy] = color;
            }
        }
        xy = 0;
    }
    free_queue(q);
    return destination;
}
