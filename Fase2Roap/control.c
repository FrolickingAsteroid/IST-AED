#include <math.h>
#include <time.h>

#include "projectHeader.h"
#include "graph.h"
#include "heapPQ.h"

#define P (w[v] + t->edge->weigth)

/**
 * @brief Função de controlo de todo o programa da fase final, por fases, pinta as salas, aloca o grafo, 
 *        determina as paredes e procura o menor caminho através do algoritmo de Dijktras.
 * 
 * @param final_cell célula de chegada
 * @param maze       matriz labirinto
 * @param row_size   número de linhas do labirinto
 * @param col_size   número de coluna do labirinto
 * @param colorcell  número de células cinzentas/pretas
 * @param file_name  nome do ficheiro de entrada
 * @param discard    vetor de paredes a descartar
 */
void control(int final_cell[2], int **maze, int row_size, int col_size, int colorcell, char *file_name, edge *discard)
{
    int numbcell = 0, breakable = 0;
    int color = -2, v = 0, aux = 0, destination = 0;
    graph *G = NULL;

    /*verifica se a célula final é branca*/

    if (maze[final_cell[0] - 1][final_cell[1] - 1] != 0){
        int result = -1;
        print_small(file_name, result);
        free_matrix(maze, row_size);
        free(discard);
        return;
    }

    /*Majorar o tamanho da queue*/

    if (col_size > row_size)
        numbcell = 4 * row_size;
    else
        numbcell = col_size * 4;

    /*********************************** Pintar salas *************************************************/

    for (int i = 0; i < row_size; i++)
        for (int j = 0; j < col_size; j++)
        {
            if (maze[i][j] == 0){
                if ((aux = bfs(maze, final_cell, row_size, col_size, numbcell, color, i, j)) != -1){

                    /*recolha do vértice de destino*/
                    destination = abs(aux + 2);

                    /*verifica se o vértice de destino é o primeiro*/
                    if (destination == 0){
                        int result = 0;
                        print_small(file_name, result);
                        free_matrix(maze, row_size);
                        free(discard);
                        return;
                    }
                }
                /*mudança da cor de pintura e aumento do número de salas/vértices*/
                color--;
                v++;
            }
        }

/**************************************************************************************************/


    /*alocação do grafo*/

    G = makeGraph(v);


/************************ descarta paredes **************************************************************/

    for (int i = 0; i < colorcell; i++)
    {
        /*se a célula for preta descarta*/

        if (is_color(maze, discard[i].x, discard[i].y) == -1)
            continue;

        /*se a célula não for quebrábel descarta*/

        breakable = is_breakable(discard[i].x, discard[i].y, maze, row_size, col_size);
        if (breakable == 0)
            continue;
        else
        {
            /*verifica os nós vizinhos da parede*/

            check_neighbours(G, breakable, maze, discard[i].x, discard[i].y, discard[i].weigth);
        }
    }

    /*liberta as matrizes*/

    free_matrix(maze, row_size);
    free(discard);

    /*verifica se o labirinto tem resolução*/

    if(G->AdjList[destination] == NULL){
        int result = -1;
        print_small(file_name,result);
        freeGraph(G);
        return;
    }

/*************************** alocação do array de caminhos e pesos **********************************/
    /**array de pesos*/

    double *w = (double *)malloc(sizeof(double) * G->numVertices);
    if (w == NULL)
        exit(EXIT_FAILURE);

    /*array de caminhos*/

    int *parent = (int *)malloc(sizeof(int) * G->numVertices);
    if (w == NULL)
        exit(EXIT_FAILURE);

/***************************************************************************************************/

    /*invocação do Dijktras*/
    Dijktras(G, w, parent, destination);

    /*Imprimir para ficheiro*/
    print_to_file(G, w, parent, destination, file_name);

    /*libertação do grafo*/
    freeGraph(G);
}

/**
 * @brief Implementação do algorítmo de Dijktras para encontrar o caminho mais barato no labirinto de entrada
 * 
 * @param G ponteiro para o grafo
 * @param w array de pesos
 * @param parent array de caminhos
 * @param destination vértice de destino
 */
void Dijktras(graph *G, double *w, int *parent, int destination)
{
    int v = 0, u = 0;
    node *t = NULL;

    /*Inicialização da lista de prioridades*/

    HeapQ *H = PriQueueInit(G->numVertices);

    for (v = 0; v < G->numVertices; v++){
        parent[v] = -1;
        w[v] = INFINITY;
    }

    /*inserir primeiro vértice no grafo*/

    insertHPQ(H, 0);

    /*tornar vértice de partida com custo 0*/

    w[0] = 0;

    /*enquanto a fila não estiver vazia*/

    while (!HPQempty(H)){
        
        /*Se o destino for encontrado para*/

        if(Peek(H) == destination) break;

        /*retira valor de prioridade máxima da fila*/

        if (w[v = HPQdelmin(H, w)] != INFINITY){
            for (t = G->AdjList[v]; t != NULL; t = t->next)
            {
                if (w[u = t->vertex] > P)
                {
                    /***************procura index********************/
                    int k = -1;
                    for (int i = 0; i < (H->rear); i++)
                    {
                        if (H->HeapArr[i] == u)
                        {
                            k = i;
                            break;
                        }
                    }
                    /**********************************************/

                    /*atualiza peso*/

                    w[u] = P;

                    /*se o index não for encontrado*/

                    if (k == -1)
                    {
                        insertHPQ(H, u);
                        k = H->rear - 1;
                    }

                    /*atualiza a prioridade dos nós e o caminho*/

                    heapifyUP(H, w, k, lessW);
                    parent[u] = v;
                }
            }
        }
    }
    /*free fila de prioridade*/
    HPQfree(H);
}
