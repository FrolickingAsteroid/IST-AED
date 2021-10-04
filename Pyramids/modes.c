#include "projectHeader.h"

/**
 * @brief 
 * 
 * @param nodes 
 * @param priority_cell 
 * @param row_size 
 * @param col_size 
 * @return int 
 */
int check_neighbours(int **nodes, int priority_cell[2], int row_size, int col_size)
{
    int dirs[4][2] = {(1, 0),(0, 1),(-1, 0),(0, -1)};
    int result = 0, move_ud = 0, move_lr = 0;
    bool out_of_bounds = false;

    for(int i = 0; i < 4; i++){

        move_ud = (priority_cell[0] - 1) + dirs[i][0];
        move_lr = (priority_cell[1] - 1) + dirs[i][1];

        out_of_bounds = is_out_bounds(move_ud, move_lr, row_size, col_size);

        if(out_of_bounds){
            result = -2;
            return result;
        }
        else if(/*qualquer coisa do is_color = true  ===> Ines*/)
        {
            /*result = o a indicar da cor*/
            /*break;*/
        }
        move_lr = 0, move_ud = 0; /*reset position*/
    }

    return result;
}