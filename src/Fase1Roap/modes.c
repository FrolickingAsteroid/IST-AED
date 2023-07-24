#include "projectHeader.h"
#include "queue.h"

/**
 * @brief função de verificação dos vizinhos de uma dada célula, verifica a sua cor (cinzenta > 0; branca = 0; preta = -1)
 * 
 * @param nodes: maze, nome passado para nodes de forma a facilitar o pensamento do grafo
 * @param priority_cell: célula a avaliar
 * @param row_size: número de linhas 
 * @param col_size: número de colunas
 * @return int result: 1 se a condição se verificar, o se não se verificar (A2, A3, A4)
 */
int check_neighbours(int **nodes, int priority_cell[2], int row_size, int col_size, int mod)
{
    int dx = 0, dy = 0, i = 0;
    int X[] = {0, 1, 0, -1}, Y[] = {-1, 0, 1, 0}; /*vetores de movimentos*/
    int result = 0;

    for (i = 0; i < 4; i++)
    {

        dx = priority_cell[0] + X[i];
        dy = priority_cell[1] + Y[i];

        if (is_out_bounds(dx, dy, row_size, col_size))
        {
            continue; /*se estiver fora do tabuleiro passamos à próxima coordenada*/
        }
        else if ((is_color(nodes, dx, dy) == 0 && mod == 2) || (is_color(nodes, dx, dy) > 0 && mod == 3) 
                || (is_color(nodes, dx, dy) == -1 && mod == 4))
            result = 1;
    }

    return result; /*se nenhum dos modos se verificar a inicializaçao de result garante a passagem do resultado negativo*/
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

    result = nodes[x - 1][y - 1]; /*as coordenada estão desfazadas por um valor*/

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
int bfs_A6(int **matrix, int **vis, int str[2], int fin[2], int numbcell, int row_size, int col_size)
{
    int currentcell[2] = {0, 0}, xy = 0, i = 0;
    queue *q = createQueue(numbcell);
    int dRow[] = {-1, 0, 1, 0}, dCol[] = {0, 1, 0, -1}; /*novos vetores de movimentos check_neighbours*/

    vis[str[0] - 1][str[1] - 1] = 1; /*a célula inicial é colocada como visitada e colocada na fila*/
    enqueue(q, str[0], str[1], numbcell);

    while (!isEmpty(q)) /*enquanto a fila não estiver vazia mantemos a procura*/
    {

        currentcell[0] = dequeue(q, xy), xy = 1; /*atualização do caminho*/
        currentcell[1] = dequeue(q, xy);

        if (currentcell[0] == fin[0] && currentcell[1] == fin[1]){
            free_queue(q);
            return 1;
        }

        for (i = 0; i < 4; i++)
        {

            int adjx = currentcell[0] + dRow[i]; /*posteriormente é esperado que estes movimentos sejam realizados pela função*/
            int adjy = currentcell[1] + dCol[i];

            if (isValid(vis, adjx, adjy, matrix, row_size, col_size))
            {
                enqueue(q, adjx, adjy, numbcell); /*vizinhos válidos são colocados na fila e marcados como visitados*/
                vis[adjx - 1][adjy - 1] = 1;
            }
        } 
        xy = 0;
    }
    free_queue(q);
    return 0;
}
