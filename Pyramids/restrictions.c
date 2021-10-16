#include "projectHeader.h"

/**
 * @brief 
 * 
 * @param row 
 * @param col 
 * @param row_size 
 * @param col_size 
 * @return true 
 * @return false 
 */
bool is_out_bounds(int row, int col, int row_size, int col_size)
{
    if ((row - 1) > (row_size - 1) || (col - 1) > (col_size - 1) || (col - 1) < 0 || (row -1) < 0)
        return true;
    else
        return false;
}

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param nodes 
 * @return int 
 */
int is_breakable(int x, int y, int **nodes, int row_size, int col_size)
{
    int result = 0, z = x - 1, f = x + 1, w = y - 1, r = y + 1;

    if (is_out_bounds(z, y, row_size, col_size) == false && is_out_bounds(f, y, row_size, col_size) == false)
        if (nodes[x - 2][y - 1] == 0 && nodes[x][y - 1] == 0)
            result = 1;

    if (is_out_bounds(x, w, row_size, col_size) == false && is_out_bounds(x, r, row_size, col_size) == false)
        if (nodes[x - 1][y - 2] == 0 && nodes[x - 1][y] == 0)
            result = 1;

    return result;
}

bool isValid(int **vis, int x, int y, int **matrix, int row_size, int col_size)
{
    /*If cell lies out of bounds*/
    if (is_out_bounds(x,y,row_size,col_size))
        return false;

    /* If cell is already visited*/
    if (vis[x-1][y-1] == 1)
        return false;

    /*if cell isn't white*/
    if (is_color(matrix, x, y) != 0)
        return false;

    /*Otherwise*/
    return true;
}
