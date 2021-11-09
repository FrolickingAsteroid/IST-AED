#include "projectHeader.h"
#include "fase1.h"

/**
 * @brief main
 */
int main(int argc, char *argv[])
{
    if (argc == 3)
        fase1(argc, argv);
    else if (argc < 1)
        exit(EXIT_FAILURE);
    else
    {
        /*prossegue para a implementação final*/
        char extension[] = ".in", *dot = strrchr(argv[1], '.');
        main_check(dot, extension);

        file_reader(argv[1]);
    }

    exit(0);
}

/**
 * @brief controlo dos argumentos de entrada para a fase 1
 */
void fase1(int argc, char *argv[])
{
    char extension[] = ".in1", *dot = strrchr(argv[2], '.');

    if (strcmp(argv[1], "-s"))
        exit(EXIT_FAILURE);
    
    main_check(dot, extension);

    file_reader_fase1(argv[2]);
}

/**
 * @brief Verifica se a invocação do programa é a correta
 * 
 * @param dot ponteiro para o último ponto no nome do enunciado de entrada
 * @param extension extensão correta do enunciado de entrada
 */
void main_check(char *dot, char *extension)
{
    /*o ficheiro não possui ponto*/
    if (dot == NULL)
        exit(EXIT_FAILURE);

    /*o ficheiro não possui a extensão correta*/
    if (strcmp(dot, extension) != 0)
        exit(EXIT_FAILURE);
}

/**
 * @brief A função está no nome, recebe toda a informação obtida no ficheiro maze_maker e realiza o seu "parcing" de acordo com a necessidade
 * 
 * @param priority_cell: célula inicial
 * @param mode: modo a ser realizado (A1, A2, A3, A4, A5, A6)
 * @param maze: tabuleiro a ser avaliado
 * @param row_size: número de linhas do tabuleiro
 * @param col_size: número de colunas do tabuleiro
 */
void mode_parcer(int priority_cell[2], int final_cell[2], char mode[2], int **maze, int row_size, int col_size, int colrcell, char *file_name)
{
    int mod = mode[1] - '0', result = 0, **vis, numbcell = 0;
    
    /*Majorar o tamanho da queue*/

    if (col_size > row_size)
        numbcell = 4 * row_size;
    else
        numbcell = col_size * 4;
    
    /*se o modo for o A6 aloca uma matriz de visitados*/
    if (mod == 6){
        vis = allocate_matrix(row_size, col_size);
    }

    switch (mod)
    {
    case 1:
        result = is_color(maze, priority_cell[0], priority_cell[1]);
        break;
    /*os 3 modos são comuns*/
    case 2:
    case 3:
    case 4:
        result = check_neighbours_fase1(maze, priority_cell, row_size, col_size, mod);
        break;

    case 5:
        if (is_color(maze, priority_cell[0], priority_cell[1]) <= 0)
        {
            result = -1;
            break;
        }
        else
            result = is_breakable_fase1(priority_cell[0], priority_cell[1], maze, row_size, col_size);
        break;
    case 6:
        if (is_color(maze, priority_cell[0], priority_cell[1]) != 0 || is_color(maze, final_cell[0], final_cell[1]) != 0)
            result = 0;
        else
        {
            result = bfs_A6(maze, vis, priority_cell, final_cell, numbcell, row_size, col_size);
        }
        free_matrix(vis, row_size);
        break;
    }

    print_to_file_fase1(result, file_name);
}