#ifndef PROJECTHEADER_H_   /* Include guard */
#define PROJECTHEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*functions responsible for matrix building*/
void free_matrix(int **matrix, int row);
void file_reader(char *file_name);
void advance_file(FILE *maze_in, int Colorcells);
int** allocate_matrix(int line, int col);
void cell_placer(int coord_L, int coord_C, int **matrix, int cost);

/*functions responsible for mode parcing*/
void mode_parcer(int priority_cell[2], int final_cell[2], char mode[2], int **maze, int row_size, int col_size,int colrcell, char* file_name);

/*functions responsible for modes*/
int bfs_A6(int **matrix, int **vis, int str[2], int fin[2], int numbcell, int row_size, int col_size);
int check_neighbours(int **nodes, int priority_cell[2], int row_size, int col_size, int mod);
int is_color(int **nodes, int x, int y);


/*functions responsible for restrictions*/
bool isValid(int **vis, int x, int y, int **matrix, int row_size, int col_size);
bool is_out_bounds(int row, int col, int row_size, int col_size);
int is_breakable(int x, int y, int **nodes, int row_size, int col_size);

/*functions responsible for printing*/
void print_to_file(int result, char* file_name);
char *create_file_name(char* file_name);

#endif