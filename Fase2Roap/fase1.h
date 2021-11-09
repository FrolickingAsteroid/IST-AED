/**
 * @file fase1.h
 * 
 * @brief Funções da fase 1 que sofreram alteração durante a realização da fase 2 ou que simplesmente não são comuns
 * 
 */

#ifndef FASE1_H_
#define FASE1_H_

#include "projectHeader.h"

/*funções de leitura e print*/
void fase1(int argc, char *argv[]);
void main_check(char *dot, char *extension);
void mode_parcer(int priority_cell[2], int final_cell[2], char mode[2], int **maze, int row_size, int col_size, int colrcell, char *file_name);
void file_reader_fase1(char *file_name);
void print_to_file_fase1(int result, char *file_name);
char *create_file_name_fase1(char *file_name);

/*funções responsáveis pelos modos*/
int bfs_A6(int **matrix, int **vis, int str[2], int fin[2], int numbcell, int row_size, int col_size);
int check_neighbours_fase1(int **nodes, int priority_cell[2], int row_size, int col_size, int mod);
bool isValid_fase1(int **vis, int x, int y, int **matrix, int row_size, int col_size);
int is_breakable_fase1(int x, int y, int **nodes, int row_size, int col_size);


#endif

