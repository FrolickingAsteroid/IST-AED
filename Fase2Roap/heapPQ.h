/**
 * @file heapPQ.h
 * 
 * @brief Header das funções responsáveis pelo controlo da fila prioridade com heap
 * 
 */

#ifndef HEAPPQ_H_ 
#define HEAPPQ_H_

typedef struct HeapPqueue
{
    int *HeapArr;         /*fila onde será aplicado o minheap*/
    int front;            /*tamanho estático da fila*/
    int rear;             /*posição do último elemento da fila (vazio)*/
} HeapQ;

/*inicialização*/
HeapQ *PriQueueInit(int size);

/*funções da min heap*/
void exch(int *a, int *b);
void insertHPQ(HeapQ *H, int n);
void heapifyUP(HeapQ *H, double *u, int idx, int (*less)(double *u, int, int));
void heapifyDOWN(HeapQ *H, double *u, int idx, int size, int (*less)(double *u, int, int));


int HPQempty(HeapQ *H);
int HPQdelmin(HeapQ *H, double *u);
int Peek(HeapQ *H);

/*comparador*/
int lessW(double *u, int, int);

/*free*/
void HPQfree(HeapQ *H);

#endif