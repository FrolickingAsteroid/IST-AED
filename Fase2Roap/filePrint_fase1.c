#include "projectHeader.h"
#include "fase1.h"

/**
 * @brief Funçao de leitura dos ficheiros a analisar e alocaçao da matriz, funçao central, essencial ao funcionamento do programa na fase1
 * 
 * @param file_name FILE* nome do ficheiro a examinar
 */
void file_reader_fase1(char *file_name)
{
    FILE *maze_in;
    bool out_bounds = false;
    int final_cell[2] = {0, 0}, i = 0, aux = 0;
    int coord_R = 0, coord_C = 0, colorCells = 0, cost = 0, size[2] = {0, 0}, priority_cell[2] = {0, 0}; /*por ordem: coord a colocar na matriz, num de celulas com cor,*/
    char mode[2];                                                                                        /*custo da cell, tamanho da matriz, cell a analisar*/

    maze_in = fopen(file_name, "r");
    if (maze_in == NULL)
        exit(EXIT_FAILURE);

    /*enquanto for lido o cabeçalho de um novo labirinto*/
    
    while ((aux = fscanf(maze_in, "%d %d %d %d %s", &size[0], &size[1], &priority_cell[0], &priority_cell[1], mode)) == 5)
    {
        out_bounds = false;

        if (is_out_bounds(priority_cell[0], priority_cell[1], size[0], size[1])) /*verificar se a celula inicial de facto pertence à matriz*/
        {                                                                        /*a alocaçao só ocorre de seguida, o mesmo para a célula final*/
            int result = -2;
            print_to_file_fase1(result, file_name);
            out_bounds = true;
        }

        /*se o modo for A6 recolhe as coordenadas de chegada*/

        if (strcmp(mode, "A6") == 0)
        {
            if (fscanf(maze_in, "%d %d", &final_cell[0], &final_cell[1]) != 2)
                exit(EXIT_FAILURE);

            if (is_out_bounds(final_cell[0], final_cell[1], size[0], size[1]) && out_bounds == false)
            {
                int result = -2;
                print_to_file_fase1(result, file_name);
                out_bounds = true;
            }
        }

        if (fscanf(maze_in, "%d", &colorCells) != 1)
            exit(EXIT_FAILURE);

        /*salta para o fim da matriz*/

        if (out_bounds == true) 
            advance_file(maze_in, colorCells);

        /*apenas iterar sobre as coordenadas se a célula inicial/final estiverem dentro da matriz*/

        else if (out_bounds == false) 
        {
            int **maze = allocate_matrix(size[0], size[1]);

            /*colocaçao da celula de partida*/

            cell_placer(priority_cell[0], priority_cell[1], maze, cost); 

            /*colocaçao da celula de chegada, somente se A6 ativo*/

            if (strcmp(mode, "A6") == 0)
                cell_placer(final_cell[0], final_cell[1], maze, cost); 

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
 * @brief realiza a passagem dos resultados para ficheiro
 *
 * @param result 
 */
void print_to_file_fase1(int result, char *file_name)
{
    FILE *fptr = NULL;
    char *file = create_file_name_fase1(file_name);
    static bool name_is_made = false;

    if(!name_is_made){
        fclose(fopen(file, "w")); /*se o ficheiro de saída já sair, dá overwrite ao anteriormente escrito, impede que o append coloque resultados onde estes já existem*/
        name_is_made = true;
    }

    if ((fptr = fopen(file, "a")) == NULL) /* "a" permite continuar a escrita, sem overwrite*/
        exit(EXIT_FAILURE);

    fprintf(fptr, "%d\n\n", result);

    fclose(fptr);
}

/**
 * @brief Cria o nome do ficheiro de saída
 * 
 * @return char*: nome do ficheiro de saída
 */
char *create_file_name_fase1(char *file_name)
{
    char *dot = NULL, extension[] = ".sol1";

    /*encontra a última ocorrência do ponto*/
    dot = strrchr(file_name, '.');

    /*copia a extensão de saíd para o ponteiro*/
    strcpy(dot, extension);

    return file_name;
}


