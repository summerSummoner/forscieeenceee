#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

typedef enum {
    OK = 0,
    ERROR = 1,
    BAD_CALC = 2
} result_t;

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns,    matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B,    matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B,    matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B,   matrix_t *result);
int s21_transpose(matrix_t *A,                  matrix_t *result);
int s21_determinant(matrix_t *A,                double   *result);
int s21_calc_complements(matrix_t *A,           matrix_t *result);
int s21_inverse_matrix(matrix_t *A,             matrix_t *result);

//  DEBUG
//  int s21_print_matrix(matrix_t A);

#endif  //  SRC_S21_MATRIX_H_
