#include "projectHeader.h"
#include "queue.h"

/**
 * @brief Cria um fila circular
 * 
 * @param numbcell majoração de 4min(L,C)
 * @return queue*: fila auxiliar de bfs
 */
queue *createQueue(int numbcell)
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->cell_array = (neighbours *)malloc(sizeof(neighbours) * numbcell);
    q->size = numbcell;
    q->front = -1;
    q->rear = -1;
    return q;
}

/**
 * @brief Verifica se a fila circular está cheia
 * 
 * @param q ponteiro para a fila
 * @return int 1 se estiver cheia, 0 se estiver vazia
 */
int Full(queue *q)
{
    if ((q->front == q->rear + 1) || (q->front == 0 && q->rear == q->size - 1))
        return 1;
    else
        return 0;
}

/**
 * @brief Verifica se a fila está vazia
 * 
 * @param q: fila a ser avaliada
 * @return int
 */
int isEmpty(queue *q)
{
    if (q->front == -1)
        return 1;
    else
        return 0;
}

/**
 * @brief retira elementos da fila
 * 
 * @param q fila a ser avaliada
 * @param xy coordenada a ser atribuída (ver estrutura neighbours)
 * @return int: coordenada a ser retornada (x ou y)
 */
int dequeue(queue *q, int xy)
{
    int coord = 0;
    if (isEmpty(q))
        return -1;
    else
    {
        /*xy = 0 -> abcissa e se xy = 1 -> ordenada*/
        if (xy == 0)
            coord = q->cell_array[q->front].x;
        else
            coord = q->cell_array[q->front].y;

        /*se a coordenada já deu dequeue*/
        if (xy != 0)
        {
            if (q->rear == q->front)
                q->front = -1, q->rear = -1;
            else
                q->front = (q->front + 1) % q->size;
        }
        return coord;
    }
}

/**
 * @brief coloca elementos na fila
 * 
 * @param q fila a receber elementos
 * @param x abcissa da coordenada
 * @param y ordenada da coordenada
 */
void enqueue(queue *q, int x, int y, int numcell)
{
    if (!Full(q))
    {
        if (q->front == -1)
            q->front = 0;
        q->rear = (q->rear + 1) % q->size;
        q->cell_array[q->rear].x = x;
        q->cell_array[q->rear].y = y;
    }
}

/**
 * @brief liberta a fila alocada
 * 
 */
void free_queue(queue *q)
{
    free(q->cell_array);
    free(q);
}