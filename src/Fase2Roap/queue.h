/**
 * @file queue.h
 * 
 * @brief Header das funções responsáveis pela execução da fila circular auxiliar do algorítmo bfs
 * 
 */
#ifndef QUEUE_H_   
#define QUEUE_H_

typedef struct neighbours
{
    int x;                  /*abcissa da célula*/
    int y;                  /*ordenada da célula*/
} neighbours;

typedef struct queue
{
    neighbours *cell_array; /*array da fila*/
    int front;              /*apontador para o início da fila*/
    int rear;               /*apontador para o fim da fila*/
    int size;               /*tamanho da fila*/
} queue;

/*funções responsáveis pelo funcionamento da fila*/
int Full(queue *q);
int isEmpty(queue *q);
int dequeue(queue *q, int xy);
void enqueue(queue *q, int x, int y, int numbcell);
queue *createQueue(int numbcell);
void free_queue(queue *q);


#endif
