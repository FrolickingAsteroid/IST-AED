/**
 * @file projectHeader.h
 * 
 * @brief funções gerais de auxílio à execução do projeto
 * 
 */

#ifndef PROJECTHEADER_H_   
#define PROJECTHEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "graph.h"

/*funções responsáveis pela construção da matriz*/
void free_matrix(int **matrix, int row);
void file_reader(char *file_name);
void advance_file(FILE *maze_in, int Colorcells);
int** allocate_matrix(int line, int col);
void cell_placer(int coord_L, int coord_C, int **matrix, int cost);

/*funções responsáveis pelo CONTROL*/
void control(int final_cell[2], int **maze, int row_size, int col_size, int colorcell, char *file_name, edge *discard);
void Dijktras(graph *G, double *w, int *parent, int destination);

/*funções auxiliares à criação do grafo*/
int bfs(int **matrix,int *fin, int row_size, int col_size, int numbcell, int color, int i, int j);
void check_neighbours(graph *G, int breakable, int **matrix, int x, int y, int w);
int is_color(int **nodes, int x, int y);


/*funções responsáveis pelas restrições*/
bool isValid(int x, int y, int **matrix, int row_size, int col_size);
bool is_out_bounds(int row, int col, int row_size, int col_size);
int is_breakable(int x, int y, int **nodes, int row_size, int col_size);

/*funções responsáveis pelo print*/
void print_to_file(graph *G, double *u, int* parent, int destiantion, char *file_name);
void print_small(char *filename, int result);
FILE* open_file(char *file_name);
char *create_file_name(char* file_name);
void recursive_print(FILE *fptr, graph *G, int *parent, int curr, int destination);
void reset_print_var();

#endif