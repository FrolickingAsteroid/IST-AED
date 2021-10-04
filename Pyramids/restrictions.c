#include "projectHeader.h"


bool is_out_bounds(int row, int col, int row_size, int col_size)
{
    if(row > row_size || col > col_size) return true;
    else return false;

}


/*bool is_breakable(...)*/