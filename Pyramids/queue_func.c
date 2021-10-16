#include "projectHeader.h"
#include "queue.h"

/**
 * @brief Create a Queue object
 * 
 * @param numbcell 
 * @return queue* 
 */
queue *createQueue(int numbcell)
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->cell_array = (neighbours *)malloc(sizeof(neighbours) * numbcell);
    q->front = -1;
    q->rear = -1;
    return q;
}

/**
 * @brief 
 * 
 * @param q 
 * @return int 
 */
int isEmpty(queue *q)
{
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

/**
 * @brief 
 * 
 * @param q 
 * @param xy 
 * @return int 
 */
int dequeue(queue *q, int xy)
{
    int coord = 0;
    if (isEmpty(q))
        return -1;
    else
    {
        if (xy == 0)
            coord = q->cell_array[q->front].x;
        else
            coord = q->cell_array[q->front].y;
        if (xy != 0)
            q->front++;
        if (q->front > q->rear && xy != 0) /*last value--> reset*/
            q->front = -1, q->rear = -1;
    }
    return coord;
}

/**
 * @brief 
 * 
 * @param q 
 * @param x 
 * @param y 
 */
void enqueue(queue *q, int x, int y, int numcell)
{
    if (q->rear != (numcell - 1))
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->cell_array[q->rear].x = x;
        q->cell_array[q->rear].y = y;
    }
}

/**
 * @brief 
 * 
 */
void free_queue(queue *q)
{
    free(q->cell_array);
    free(q);
}