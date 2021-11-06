#include <math.h>

#include "projectHeader.h"
#include "graph.h"
#include "heapPQ.h"

#define P (w[v] + t->edge->weigth)


/**
 * @brief 
 * 
 * @param final_cell 
 * @param maze 
 * @param row_size 
 * @param col_size 
 * @param colorcell 
 * @param file_name 
 * @param discard 
 */
void control(int final_cell[2], int **maze, int row_size, int col_size, int colorcell, char *file_name, edge *discard)
{
    int numbcell = (row_size * col_size) - colorcell, breakable = 0;
    int color = -2, v = 0, aux = 0, destination = 0;
    double *w = NULL;
    graph *G = NULL;

    /**/
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < col_size; j++)
        {
            printf(" %d  ", maze[i][j]);
        }
        printf("\n");
    }
    /**/

    for (int i = 0; i < row_size; i++)
        for (int j = 0; j < col_size; j++)
        {
            if (maze[i][j] == 0)
            {
                if ((aux = bfs(maze, final_cell, row_size, col_size, numbcell, color, i, j)) != -1){
                    destination = abs(aux + 2);
                    
                }
                color--;
                v++;
            }
        }

    /**/
    printf("\n");
    for (int i = 0; i < row_size; i++){
        for (int j = 0; j < col_size; j++)
        {
            printf(" %d ", maze[i][j]);
        }
    printf("\n");
    }
    /**/

    printf("%d\n", v);
    printf("%d\n", destination);
    G = makeGraph(v);

    w = (double *)malloc(sizeof(double) * G->numVertices);
    if (w == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < colorcell; i++)
    {
        if (is_color(maze, discard[i].x, discard[i].y ) == -1)
            continue;

        breakable = is_breakable(discard[i].x, discard[i].y, maze, row_size, col_size);
        if (breakable == 0 || breakable == 3)
            continue;
        else
        {
            check_neighbours(G, breakable, maze, discard[i].x, discard[i].y, discard[i].weigth);
        }
    }

    for(node* i = G->AdjList[0]; i != NULL; i = i->next) printf("%d", i->vertex);
    printf("\n");

    Dijktras(G,w);
    print_to_file(G, w, destination, file_name);

    for (int i = 0; i < G->numVertices; i++)
    {
        freeAdjList((G->AdjList[i]));
    }
    free(G->AdjList);
    free(G);
}

/**
 * @brief 
 * 
 * @param G 
 */
void Dijktras(graph *G, double *w)
{
    int v = 0, u = 0, parent[5];
    node *t = NULL;

    HeapQ *H = PriQueueInit(G->numVertices);
    for (v = 0; v < G->numVertices; v++)
    {
        parent[v] = -1;
        w[v] = INFINITY;
        insertHPQ(H, w, v, lessW);
    }
    /*insertHPQ(H, w, 0, lessW);*/
    w[0] = 0;
    for (v = 0; v < G->numVertices; v++)
        printf("%d ", H->HeapArr[v]);
    printf("\n\n");

    while (!HPQempty(H))
    {
        if (w[v = HPQdelmin(H, w)] != INFINITY)
        {
            for (v = 0; v < G->numVertices; v++)
                        printf("%d ", H->HeapArr[v]);
                    printf("\n");
            for (t = G->AdjList[v]; t != NULL; t = t->next)
                if (w[u = t->vertex] > P)
                {
                    /*printf("2 %d\n", t->vertex);
                    printf("3 %d\n", t->edge->weigth);*/
                    w[u] = P;
                    /*if (parent[u] == -1)
                        insertHPQ(H, w, u, lessW);*/
                    /*heapifyUP(H,w,u,lessW);*/
                    
                    parent[u] = v;
                    /*t->prev = G->AdjList[v]; /*make stack for print*/
                    /*heapifyDOWN(H, w, u, H->rear - 1, lessW);*/
                    /*for (v = 0; v < G->numVertices; v++)
                        printf("%d ", H->HeapArr[v]);
                    printf("\n");*/
                }
        }
    }

    for (int i = 0; i < 5; i++)
        printf("%d ", parent[i]);
}
