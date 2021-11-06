#include "projectHeader.h"

/**
 * @brief Verifica se a célula a analisar se encontra dentro do tabuleiro
 * 
 * @param row: abcissa da coordenada
 * @param col: ordenada da coordenada
 * @param row_size: número de linhas do tabuleiro
 * @param col_size: número de colunas do tabuleiro
 * @return true: está fora do tabuleiro
 * @return false: está dentro do tabuleiro
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
 * @param row_size 
 * @param col_size 
 * @return int 
 */
int is_breakable(int x, int y, int **nodes, int row_size, int col_size)
{
    int result = 0, z = x - 1, f = x + 1, w = y - 1, r = y + 1;

    if (is_out_bounds(z, y, row_size, col_size) == false && is_out_bounds(f, y, row_size, col_size) == false)
        if (nodes[x - 2][y - 1] <= -2 && nodes[x][y - 1] <= -2)
            result = 1; /*breakable vertically*/

    if (is_out_bounds(x, w, row_size, col_size) == false && is_out_bounds(x, r, row_size, col_size) == false)
        if (nodes[x - 1][y - 2] <= -2 && nodes[x - 1][y] <= -2)
        {
            if (result == 1)
                result = 3; /*breakable both sides*/
            else
                result = 2; /*breakable horizontally*/
        }

    return result;
}

/**
 * @brief conjunção de várias funções de restrição numa só para facilitar a função bfs
 * 
 * @param vis tabuleiro de vizinhos visitados
 * @param x abcissa da coordenada
 * @param y ordenada da coordenada
 * @param matrix: tabuleiro a ser analisado
 * @param row_size número de linhas do tabuleiro
 * @param col_size número de colunas do tabuleiro
 * @return true: o vizinho é válido
 * @return false; o vizinho não é válido
 */
bool isValid(int x, int y, int **matrix, int row_size, int col_size)
{
    /*If cell lies out of bounds*/
    if (is_out_bounds(x,y,row_size,col_size))
        return false;

    /* If cell is already visited*/
    if (matrix[x - 1][y - 1] != 0)
        return false;

    /*if cell isn't white*/
    if (is_color(matrix, x, y) != 0)
        return false;

    return true;
}

