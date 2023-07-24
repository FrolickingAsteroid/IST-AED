#include <math.h>

#include "projectHeader.h"
#include "graph.h"

/************* variáveis globais intrínsecas ao print ********************/

static bool name_is_made = false;  /*condição de overwrite, disponível em duas funções, o acesso torna-se mais fácil enquanto variável global*/

static bool printed = false; /*manipulação da impressão na função recursiva, sofrem reset após cada solução*/
static int walls = 0;
/*************************************************************************/

/**
 * @brief Cria o nome do ficheiro de saída
 * 
 * @return char*: nome do ficheiro de saída
 */
char *create_file_name(char *file_name)
{
    char *dot = NULL, extension[] = ".sol";

    /*encontra a última ocorrência do ponto*/
    dot = strrchr(file_name, '.');

    /*copia a extensão de saíd para o ponteiro*/
    strcpy(dot, extension);

    return file_name;
}

/**
 * @brief Abre o ficheiro de saída
 * 
 * @param file_name nome do ficheiro de saída
 * @return FILE* ponteiro para o ficheiro
 */
FILE * open_file(char *file_name)
{
    FILE *fptr = NULL;

    /* "a" permite continuar a escrita, sem overwrite*/
    if ((fptr = fopen(file_name, "a")) == NULL)
        exit(EXIT_FAILURE);
    
    return fptr;
}

/**
 * @brief Função de impressão de respostas longas dos caminhos encontrados
 * 
 * @param G ponteiro para o grafo
 * @param u vetor de pesos
 * @param parent vetor de caminhos
 * @param destination vértice de destino
 * @param file_name nome do ficheiro de entrada, a ser convertido para o de saída
 */
void print_to_file(graph *G, double *u, int *parent, int destination, char *file_name)
{
    FILE *fptr = NULL;
    char *file = create_file_name(file_name);

    if (!name_is_made)
    {
        /*se o ficheiro de saída já existir, dá overwrite ao anteriormente escrito, 
        impede que o append coloque resultados onde estes já existam*/

        fclose(fopen(file, "w"));
        name_is_made = true;
    }

    fptr = open_file(file);

    /*verifica se existe caminho*/

    if(u[destination] == INFINITY){

        /*se não imprime o resultado nulo*/

        int result = -1;
        fprintf(fptr, "%d\n\n", result);
        free(parent), free(u);
        fclose(fptr);
        return;

    }

    /*else continua a impressão de caminho*/

    fprintf(fptr, "%1.f\n", u[destination]);

    int curr = parent[destination];
    recursive_print(fptr, G, parent, curr, destination);

    fprintf(fptr, "\n\n");

    /*reset das variáveis globais adjacentes à função recursiva*/

    reset_print_var();

    free(parent);
    free(u);

    fclose(fptr);
}

/**
 * @brief Função de impressão recursiva de caminhos, coloca as paredes por ordem de passagem do vértice de partida até ao de chegada
 * 
 * @param G ponteiro para o grafo
 * @param parent vetor de caminhos
 * @param curr penultimo vertice de chegada
 * @param destination vertice de chegada
 */
void recursive_print(FILE *fptr, graph *G, int *parent, int curr, int destination)
{
    node *t = NULL;

    /*enquanto não se chegar à raiz do caminho*/

    if (curr == -1)
        return;
    /*incrementa o número de paredes partidas e procura o destino*/

    walls++;
    for (t = G->AdjList[curr]; t->vertex != destination; t = t->next)
        ;

    /*atualiza o destino e o vertice atual*/

    destination = curr;
    curr = parent[destination];

    recursive_print(fptr, G, parent, curr, destination);

    /*imprime o número de paredes uma vez*/

    if (printed == false){
        fprintf(fptr, "%d\n", walls);
        printed = true;
    }

    fprintf(fptr, "%d %d %d\n", t->edge->x, t->edge->y, t->edge->weigth);
}

/**
 * @brief Imprime resultados pequenos, casos específicos, ex.: a célula de partida é a de chegada
 * 
 * @param filename nome do ficheiro de entrada
 * @param result resultado a ser impresso, 0 ou -1
 */
void print_small(char *filename, int result)
{
    char *file_name = create_file_name(filename);

    /*abertura do ficheiro de saída*/
    FILE *fptr = open_file(file_name);

    if (!name_is_made)
    {
        fclose(fopen(file_name, "w"));
        name_is_made = true;
    }

    fprintf(fptr, "%d\n\n\n", result);
    name_is_made = true;

    fclose(fptr);
}

/**
 * @brief Função de reset das variaveis globais associadas à função recursiva
 * 
 */
void reset_print_var()
{
    printed = false;
    walls = 0;
}