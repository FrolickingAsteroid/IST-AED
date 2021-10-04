#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main()
{
    FILE *maze_in;
    int **maze, coord_L = 0, coord_C = 0, colorCells = 0, cost = 0, size[2] = {0, 0}, priority_cell[2] = {0, 0}; /*por ordem: coord a colocar na matriz, num de celulas com cor,*/
    char line_holder[3], mode[2];                                                                                /*tamanho da matriz, cell a analisar*/
    static bool maze_data = true;

    maze_in = fopen("/home/freud/Desktop/AED/New stuff/Pyramids/Enunciado_A1/enunciado101.in1", "r");
    if (maze_in == NULL)
        exit(EXIT_FAILURE);

    while (fscanf(maze_in, "%d %d %d %d %s %d", &size[0], &size[1], &priority_cell[0], &priority_cell[1], mode, &colorCells) == 6)
    {
        for (int i = 0; i < colorCells; i++)
        {
            fscanf(maze_in, "%d %d %d", &coord_L, &coord_C, &cost);
            /*cell_placer(coord_L, coord_C);*/
        }
    }
    return 0;
}