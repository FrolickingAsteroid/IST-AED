#include "projectHeader.h"
#include "queue.h"

/**
 * @brief 
 * 
 * @param nodes 
 * @param priority_cell 
 * @param row_size 
 * @param col_size 
 * @return int 
 */
int check_neighbours(int **nodes, int priority_cell[2], int row_size, int col_size, int mod)
{
    int dx = 0, dy = 0, i = 0;
    int X[] = {0, 1, 0, -1}, Y[] = {-1, 0, 1, 0};
    int result = 0;

    for (i = 0; i < 4; i++)
    {

        dx = priority_cell[0] + X[i];
        dy = priority_cell[1] + Y[i];

        if (is_out_bounds(dx, dy, row_size, col_size))
        {
            continue;
            /*result = -2;
            return result;*/
        }
        else if ((is_color(nodes, dx, dy) == 0 && mod == 2) || (is_color(nodes, dx, dy) > 0 && mod == 3) 
                || (is_color(nodes, dx, dy) == -1 && mod == 4))
            result = 1;
    }

    return result; /*se nenhum dos modos se verificar a inicializaçao de result garante a passagem do resultado negativo*/
}

/**
 * @brief 
 * 
 * @param nodes 
 * @param priority_cell 
 * @return int 
 */
int is_color(int **nodes, int x, int y)
{
    int result = 0;

    result = nodes[x - 1][y - 1];

    return result;
}

/**
 * @brief 
 * 
 * @param matrix 
 * @param vis 
 * @param str 
 * @param fin 
 * @param numbcell 
 * @param row_size 
 * @param col_size 
 * @return int 
 */
int bfs_A6(int **matrix, int **vis, int str[2], int fin[2], int numbcell, int row_size, int col_size)
{
    int currentcell[2] = {0, 0}, xy = 0, i = 0;
    queue *q = createQueue(numbcell);
    int dRow[] = {-1, 0, 1, 0}, dCol[] = {0, 1, 0, -1};

    vis[str[0] - 1][str[1] - 1] = 1;
    enqueue(q, str[0], str[1], numbcell);

    while (!isEmpty(q))
    {

        currentcell[0] = dequeue(q, xy), xy = 1;
        currentcell[1] = dequeue(q, xy);

        if (currentcell[0] == fin[0] && currentcell[1] == fin[1]){
            free_queue(q);
            return 1;
        }

        for (i = 0; i < 4; i++)
        {

            int adjx = currentcell[0] + dRow[i];
            int adjy = currentcell[1] + dCol[i];

            if (isValid(vis, adjx, adjy, matrix, row_size, col_size))
            {
                enqueue(q, adjx, adjy, numbcell);
                vis[adjx - 1][adjy - 1] = 1;
            }
        } 
        xy = 0;
    }
    free_queue(q);
    return 0;
}
