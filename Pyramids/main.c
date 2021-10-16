#include "projectHeader.h"

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    char extention[] = ".in1", *dot = strrchr(argv[2], '.');

    if (argc != 3 || strcmp(argv[1], "-s"))
        exit(EXIT_FAILURE);

    if (dot == NULL)
        exit(EXIT_FAILURE);

    if (strcmp(dot, extention) != 0)
        exit(EXIT_FAILURE);

    file_reader(argv[2]);

    exit(0);
}

/**
 * @brief 
 * 
 * @param priority_cell 
 * @param mode 
 * @param maze 
 * @param row_size 
 * @param col_size 
 */
void mode_parcer(int priority_cell[2], int final_cell[2], char mode[2], int **maze, int row_size, int col_size, int colrcell, char *file_name)
{
    int mod = mode[1] - '0', result = 0, **vis, numbcell = (row_size * col_size) - colrcell;

    if (mod == 6){
        vis = allocate_matrix(row_size, col_size);
    }

    switch (mod)
    {
    case 1:
        result = is_color(maze, priority_cell[0], priority_cell[1]);
        break;

    case 2:
    case 3:
    case 4:
        result = check_neighbours(maze, priority_cell, row_size, col_size, mod);
        break;

    case 5:
        if (is_color(maze, priority_cell[0], priority_cell[1]) <= 0)
        {
            result = -1;
            break;
        }
        else
            result = is_breakable(priority_cell[0], priority_cell[1], maze, row_size, col_size);
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

    print_to_file(result, file_name);
}
