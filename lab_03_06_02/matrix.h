#ifndef INPUT_MATRIX_H
#define INPUT_MATRIX_H

#define N_MAX 10

typedef int matrix_t[N_MAX][N_MAX];

void make_matrix(matrix_t matrix, int row, int col);
void print_matrix(matrix_t matrix, int row, int col);

#endif