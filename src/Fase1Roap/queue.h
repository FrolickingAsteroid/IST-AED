#ifndef QUEUE_H_   /* Include guard */
#define QUEUE_H_

typedef struct neighbours
{
    int x;
    int y;
} neighbours;

typedef struct queue
{
    neighbours *cell_array;
    int front;
    int rear;
} queue;

/*functions responsible for queue operations*/
int isEmpty(queue *q);
int dequeue(queue *q, int xy);
void enqueue(queue *q, int x, int y, int numbcell);
queue *createQueue(int numbcell);
void free_queue(queue *q);


#endif
