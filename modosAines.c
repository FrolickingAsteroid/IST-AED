#include "projectHeader.h"
#include <stdio.h>
#include <stdlib.h>


    int check_neighbours(int **nodes, int priority_cell[2], int row_size, int col_size)
{
    int dirs[4][2] = {(1, 0),(0, 1),(-1, 0),(0, -1)};
    int result = 0, move_ud = 0, move_lr = 0;
    bool out_of_bounds = false, A2= false, A3= false, A4= false, A5= false;


    for(int i = 0; i < 4; i++){

        move_ud = (priority_cell[0] - 1) + dirs[i][0];
        move_lr = (priority_cell[1] - 1) + dirs[i][1];


       out_of_bounds = is_out_bounds(move_ud, move_lr, row_size, col_size);


        if(out_of_bounds){
            result = -2;
            return result;
        }

      else if(A2=true )
        {
            if (priority_cell==0){
                result=1;
                return result;
            }

            else{
                result=0;
                return result;
            }

        }
        else if(A3=true )
        {
            if (priority_cell>=1)
                {
                result=1;
                return result;
            }
            else
                {
                result=0;
                return result;
            }

        }
        else if(A4=true )
        {
            if (priority_cell==-1)
                {
                result=1;
                return result;
            }
            else
                {
                result=0;
                return result;
            }

        }
         else if(A5=true )
        {
            if (priority_cell<1)
                {
                result=-1;
                return result;
            }
            else
                {
                if ((priority_cell[0]-1==0 && priority_cell[0]+1==0)||(priority_cell[1]-1==0 && priority_cell[1]+1==0))
                result=1;
                return result;
            }else if{
                 result=0;
                 return result;
              }


        move_lr = 0, move_ud = 0; /*reset position*/
    }

    return result;
}

int A1(int **nodes, int priority_cell[2], int row_size, int col_size){
    bool A1=false;
    int result=0;

    if (A1=true){
        result=priority_cell;
    }
 return result;
}
