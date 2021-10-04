#include "projectHeader.h"
/**
 * @brief Funçao de leitura dos ficheiros a analisar
 * 
 * @param file_name FILE* nome do ficheiro a examinar
 */
void file_reader(char *file_name, int** maze)
{
    FILE *maze_in;
    int coord_R = 0, coord_C = 0, colorCells = 0, cost = 0, size[2] = {0, 0}, priority_cell[2] = {0, 0}; /*por ordem: coord a colocar na matriz, num de celulas com cor,*/
    char line_holder[3], mode[2];                                                                                /*custo da cell, tamanho da matriz, cell a analisar*/

    maze_in = fopen(file_name, "r");
    if (maze_in == NULL)
        exit(EXIT_FAILURE);

    while (fscanf(maze_in, "%d %d %d %d %s %d", &size[0], &size[1], &priority_cell[0], &priority_cell[1], mode, &colorCells) == 6)
    {
        maze = allocate_matrix(size[0], size[1]);
        
        for (int i = 0; i < colorCells; i++)
        {
            fscanf(maze_in, "%d %d %d", &coord_R, &coord_C, &cost);
            cell_placer(coord_R, coord_C, maze, cost);
        }

        mode_parcer(priority_cell, mode, maze, size[0], size[1]);
    }

    fclose(maze_in);
}

/**
 * @brief funçao de alocaçao da matriz/labirinto a ser avaliada, displays the nodes in a grid
 * 
 * @param row int, num. de linhas da matriz/labirinto
 * @param col int, num. de colunas da matriz/labirinto
 */
int **allocate_matrix(int row, int col) 
{
    int **matrix = (int **)calloc(row, sizeof(int *)); /*alocaçao com calloc para preservar as celulas de custo nulo*/
    for (int i = 0; i < row; i++)
        matrix[i] = (int *)calloc(col, sizeof(int));

    return matrix;
}

/**
 * @brief funç\ao de colocaçao do custo das células
 * 
 * @param coord_R 
 * @param coord_C 
 * @param matrix 
 * @param cost 
 */
void cell_placer(int coord_R, int coord_C, int **matrix, int cost)
{
    matrix[coord_R - 1][coord_C - 1] = cost; /*aplicamos a subtraçao já que as coordenadas vao de 1 - line_size*/
}
