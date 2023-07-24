#include "heapPQ.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************* Funções de controlo do Acervo/Fila de Prioridade **************************************************/

/**
 * @brief Inicializa a Fila de prioridade
 * 
 * @param size tamanho do array do acervo
 * @return HeapQ* ponteiro para a fila de Prioridade
 */
HeapQ *PriQueueInit(int size)
{
    /*alocação da fila de prioridade*/

    HeapQ* Heap  = (HeapQ *)malloc(sizeof(HeapQ));
    Heap->HeapArr = (int *)calloc(size, sizeof(int));

    /*tamanho total da fila de prioridade*/

    Heap->front = size;

    /*apontador para o último elemento do array, primeiro da fila*/

    Heap->rear = 0;
    return Heap;
}

/**
 * @brief Insere um elemento na Fila de Prioridade de forma desorganizada
 * 
 * @param H ponteiro para a fila de prioridade
 * @param n nó a ser colocado na fila
 */
void insertHPQ(HeapQ *H, int n)
{
    /*enquanto não for excedida a capacidade da fila*/

    if ((H->rear - 1) < H->front)
    {
        /*coloca o nó na última posição do array/ posição currente*/

        H->HeapArr[H->rear] = n;

        /*incrementa o marcador de última posição (vazia)*/

        H->rear++;
    }
}

/**
 * @brief troca dois intens da fila de prioridade
 * 
 * @param a primeiro intem
 * @param b segundo intem
 */
void exch(int *a, int *b)
{
   int temp = *a; *a = *b; *b = temp;
}

/**
 * @brief função de fixup, chamada sempre que a key (peso) sofra um decréscimo,
 *        atualiza a prioridade.
 * 
 * @param H ponteiro para a fila
 * @param u vetor de pesos, transporta as keys
 * @param idx index a ser atualizado
 * @param less função de comparação
 */
void heapifyUP(HeapQ *H, double *u, int idx, int (*less)(double *u, int, int))
{
    /*enquanto não chegar à raiz ou enquanto o parente for maior do que o filho*/

    while (idx > 0 && less(u, H->HeapArr[idx], H->HeapArr[(idx - 1) / 2]))
    {
        /*troca o filho com o pai e sobe/atualiza o index*/

        exch(&(H->HeapArr[idx]), &(H->HeapArr[(idx - 1) / 2]));
        idx = (idx - 1) / 2;
    }
}

/**
 * @brief Função de pop do elemento de maior prioridade
 * 
 * @param H ponteiro para a fila de prioridade
 * @param u vetor de pesos
 * @return int elemento de maior prioridade
 */
int HPQdelmin(HeapQ *H, double *u)
{
    /*troca a raiz da min heap com o primeiro elemento do array*/

    exch(&(H->HeapArr[0]), &(H->HeapArr[H->rear - 1]));

    /*min heapify após remoção do elemento*/

    heapifyDOWN(H,u,0,(H->rear - 1), lessW);
    
    return (H->HeapArr[--H->rear]);
}

/**
 * @brief função de fixdown, restabelece a condição de min heap após remoção de um elemento
 * 
 * @param H ponteiro para a lista de prioridades
 * @param u vetor de pesos
 * @param idx index a ser atualizado
 * @param size tamanho da lista de prioridades
 * @param less função de comparação
 */
void heapifyDOWN(HeapQ *H, double *u, int idx, int size, int (*less)(double *u, int, int)) /*review*/
{
    /*enquanto não chegar às folhas da min heap */

    while (2 * idx < size - 1)
    {
        int child = 2 * idx + 1;

        /*seleciona o menor descendente*/

        if (child < (size - 1) && less(u, H->HeapArr[child + 1], H->HeapArr[child]))
            child++;
        
        /*condição de acervo, parente menor que o filho*/

        if (!less(u, H->HeapArr[child], H->HeapArr[idx])) 
            break;

        /*troca do parente pelo filho e atualização do parente*/

        exch(&(H->HeapArr[idx]), &(H->HeapArr[child]));
        idx = child;
    }
}

/**
 * @brief função de comparação, estabelece a condição de min heap
 * 
 * @param u vetor de pesos (keys)
 * @param i primeiro nó
 * @param j segundo nó
 * @return int 1 se nó1 < nó2, 0 se o inverso
 */
int lessW(double *u, int i, int j)
{
    if (u[i] < u[j])   
        return 1;
    else
        return 0;
}

/**
 * @brief Verifica se a lista de prioridades se encontra vazia
 * 
 * @param H ponteiro para a lista de prioridades
 * @return int 1 se estiver vazia, 0 se o inverso
 */
int HPQempty(HeapQ *H)
{
    /*se o apontador para o último elemento for coincidente com a posição de raiz*/

    if (H->rear == 0)
        return 1;
    else
        return 0;
}

/**
 * @brief função que retorna a raiz da min heap sem a remover da lista, faz peek (literalmente)
 * 
 * @param H ponteiro para a lista de prioridade
 * @return int raiz da min heap
 */
int Peek(HeapQ *H)
{
    return H->HeapArr[0];
}

/**
 * @brief Liberta a fila alocada
 * 
 * @param H ponteiro para a fila de prioridade
 */
void HPQfree(HeapQ *H)
{
    free(H->HeapArr);
    free(H);
}

