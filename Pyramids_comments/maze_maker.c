#include "projectHeader.h"
#include "graph.h"

/**
 * @brief Funçao de leitura dos ficheiros a analisar e alocaçao da matriz, funçao central, essencial ao funcionamento do programa
 * 
 * @param file_name FILE* nome do ficheiro a examinar
 */
void file_reader(char *file_name)
{
    FILE *maze_in;
    edge *discard;
    int final_cell[2] = {0, 0}, i = 0, numbcell;
    int coord_R = 0, coord_C = 0, colorCells = 0, cost = 0, size[2] = {0, 0};
    bool out_bounds = false;
                                                                                                        

    maze_in = fopen(file_name, "r");
    if (maze_in == NULL)
        exit(EXIT_FAILURE);

    while ((fscanf(maze_in, "%d %d %d %d %d", &size[0], &size[1], &final_cell[0], &final_cell[1], &colorCells)) == 5){

        if (is_out_bounds(final_cell[0], final_cell[1], size[0], size[1])){
            int result = -1;
            /*print_to_file(result, file_name);*/
            out_bounds = true;
        }
    
        if (out_bounds == true) /*salta para o fim da matriz*/
            advance_file(maze_in, colorCells);

        else if (out_bounds == false) {

            int **maze = allocate_matrix(size[0], size[1]);
            discard = (edge*)malloc(sizeof(edge)*colorCells);

            cell_placer(final_cell[0], final_cell[1], maze, cost); /*colocaçao da celula de partida*/

            for (i = 0; i < colorCells; i++)
            {
                if (fscanf(maze_in, "%d %d %d", &coord_R, &coord_C, &cost) != 3)
                    exit(EXIT_FAILURE);
                 cell_placer(coord_R, coord_C, maze, cost);

                 /**********************/
                 discard[i].x = coord_R;
                 discard[i].y = coord_C;
                 discard[i].weigth = cost;
                 /**********************/
            }

            control(final_cell,maze,size[0],size[1],colorCells,file_name, discard);
            free_matrix(maze, size[0]);
        }
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
