#include "projectHeader.h"

/**
 * @brief Funçao de leitura dos ficheiros a analisar e alocaçao da matriz, funçao central, essencial ao funcionamento do programa
 * 
 * @param file_name FILE* nome do ficheiro a examinar
 */
void file_reader(char *file_name)
{
    FILE *maze_in;
    bool out_bounds = false;
    int final_cell[2] = {0, 0}, i = 0, aux = 0;
    int coord_R = 0, coord_C = 0, colorCells = 0, cost = 0, size[2] = {0, 0}, priority_cell[2] = {0, 0}; /*por ordem: coord a colocar na matriz, num de celulas com cor,*/
    char mode[2];                                                                                        /*custo da cell, tamanho da matriz, cell a analisar*/

    maze_in = fopen(file_name, "r");
    if (maze_in == NULL)
        exit(EXIT_FAILURE);

    while ((aux = fscanf(maze_in, "%d %d %d %d %s", &size[0], &size[1], &priority_cell[0], &priority_cell[1], mode)) == 5)
    {
        out_bounds = false;

        if (is_out_bounds(priority_cell[0], priority_cell[1], size[0], size[1])) /*verificar se a celula inicial de facto pertence à matriz*/
        {                                                                        /*a alocaçao só ocorre de seguida, o mesmo para a celula final*/
            int result = -2;
            print_to_file(result, file_name);
            out_bounds = true;
        }

        if (strcmp(mode, "A6") == 0)
        {
            if (fscanf(maze_in, "%d %d", &final_cell[0], &final_cell[1]) != 2)
                exit(EXIT_FAILURE);

            if (is_out_bounds(final_cell[0], final_cell[1], size[0], size[1]) && out_bounds == false)
            {
                int result = -2;
                print_to_file(result, file_name);
                out_bounds = true;
            }
        }

        if (fscanf(maze_in, "%d", &colorCells) != 1)
            exit(EXIT_FAILURE);

        if (out_bounds == true) /*salta para o fim da matriz*/
            advance_file(maze_in, colorCells);

        else if (out_bounds == false) /*apenas iterar sobre as coordenadas se a célula inicial/final estiverem dentro da matriz*/
        {
            int **maze = allocate_matrix(size[0], size[1]);

            cell_placer(priority_cell[0], priority_cell[1], maze, cost); /*colocaçao da celula de partida*/

            if (strcmp(mode, "A6") == 0)
                cell_placer(final_cell[0], final_cell[1], maze, cost); /*colocaçao da celula de chegada, somente se A6 ativo*/

            for (i = 0; i < colorCells; i++)
            {
                if (fscanf(maze_in, "%d %d %d", &coord_R, &coord_C, &cost) != 3)
                    exit(EXIT_FAILURE);
                 cell_placer(coord_R, coord_C, maze, cost);
            }

            mode_parcer(priority_cell, final_cell, mode, maze, size[0], size[1], colorCells, file_name);
            free_matrix(maze, size[0]);
        }
        /*-----------------------------------reinicializaçao das variáveis-----------------------------------------------------*/
        coord_R = 0, coord_C = 0, colorCells = 0, cost = 0, size[0] = 0, size[1] = 0, priority_cell[0] = 0, priority_cell[1] = 0;
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
    int i = 0;
    int **matrix = (int **)calloc(row, sizeof(int *)); /*alocaçao com calloc para preservar as celulas de custo nulo*/
    for (i = 0; i < row; i++)
        matrix[i] = (int *)calloc(col, sizeof(int));

    return matrix;
}

/**
 * @brief funçao de colocaçao do custo das células
 * 
 * @param coord_R abcissa na matriz
 * @param coord_C ordenada na matriz
 * @param matrix matriz onde deverá ser realizada a colocaç\ao
 * @param cost valor a ser colocado
 */
void cell_placer(int coord_R, int coord_C, int **matrix, int cost)
{
    matrix[coord_R - 1][coord_C - 1] = cost; /*aplicamos a subtraçao já que as coordenadas vao de 1 -> line_size*/
}

/**
 * @brief funçao que liberta a memória alocada para a construçao da matriz
 * 
 * @param matrix matriz/memoria a ser libertada
 * @param row número de linhas, para a libertaçao das colunas
 */
void free_matrix(int **matrix, int row)
{
    int i;
    for (i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);
}

/**
 * @brief Funçao que "avança" o ficheiro até à próxima matriz
 * 
 * @param maze_in ficheiro de leitura
 * @param Colorcells número de células coloridas, para iteraçao
 */
void advance_file(FILE *maze_in, int Colorcells)
{
    int dummy = 0, i = 0;
    for (i = 0; i < Colorcells; i++)
        if (fscanf(maze_in, "%d %d %d", &dummy, &dummy, &dummy) != 3) /*os valores das coordenadas nao nos sao necessários*/
            exit(EXIT_FAILURE);                                       /*usamos uma variável dummy para iterar, até chegarmos à nova matriz*/
}
