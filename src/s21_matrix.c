#include <stdio.h>
#include <stdlib.h>
#include "s21_matrix.h"
#include "s21_matrix_inner.h"

//  ----------------------------------------------------------------------------
//                              INNER PREDEFINITIONS
//  ----------------------------------------------------------------------------

int s21_check_matrix_type_identity(matrix_t A);
int s21_check_matrix_type_zero(matrix_t A);
int s21_check_matrix_type(matrix_t A);

matrix_t s21_minor_matrix(matrix_t A, int row, int column);
int s21_A_to_B(matrix_t *A, matrix_t *B);

//  ----------------------------------------------------------------------------
//                                      MAIN
//  ----------------------------------------------------------------------------

//  OK
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    result_t exit_code = ERROR;
    if (result) {
        // if ((*result).matrix)
        //     s21_remove_matrix(result);
        (*result).rows = rows;
        (*result).columns = columns;
        if (rows > 0 && columns > 0) {
            (*result).matrix = (double **)malloc(rows * sizeof(double *));
            for (int i = 0; i < rows; i++) {
                (*result).matrix[i] = (double *)malloc(columns * sizeof(double));
                for (int j = 0; j < columns; j++)
                    (*result).matrix[i][j] = 0.0;
            }
            exit_code = OK;
        } else {
            (*result).matrix = NULL;
        }
    }
    return exit_code;
}

//  OK
void s21_remove_matrix(matrix_t *A) {
    if (A && (*A).matrix) {
        for (int i = 0; i < (*A).rows; i++) {
            if ((*A).matrix[i]) {
                free((*A).matrix[i]);
                (*A).matrix[i] = NULL;
            }
        }
        free((*A).matrix);
        (*A).matrix = NULL;
        (*A).rows = 0;
        (*A).columns = 0;
    }
    return;
}

//  OK
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = FAILURE;
    if (A && B && S21_MATRIX_COMPARE_SIZE_SAFE(*A, *B)) {
        // if ((*A).matrix_type == CORRECT_MATRIX &&
        //     (*B).matrix_type == CORRECT_MATRIX) {
        matrix_type_t A_type = s21_check_matrix_type(*A);
        matrix_type_t B_type = s21_check_matrix_type(*B);
        if (A_type == CORRECT_MATRIX &&
            B_type == CORRECT_MATRIX) {
            result = SUCCESS;
            for (int i = 0; i < (*A).rows; i++) {
                for (int j = 0; j < (*A).columns; j++) {
                    double temp = (*A).matrix[i][j] - (*B).matrix[i][j];
                    if ((temp > 1e-7) || (temp < -1e-7) || (temp != temp)) {
                        result = FAILURE;
                        break;
                    }
                }
            }
        //  } else if ((*A).matrix_type == (*B).matrix_type) {
        } else if (A_type == B_type) {
            result = SUCCESS;
        }
    }
    return result;
}

//  OK
//  C = A + B
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && B && result) {
        exit_code = OK;
        if (S21_MATRIX_COMPARE_SIZE_SAFE(*A, *B)) {
            matrix_t temp;
            s21_create_matrix((*A).rows, (*A).columns, &temp);
            for (int i = 0; i < temp.rows; i++) {
                for (int j = 0; j < temp.columns; j++)
                    temp.matrix[i][j] = (*A).matrix[i][j] + (*B).matrix[i][j];
            }
            s21_A_to_B(&temp, result);
            //  C.matrix_type = s21_check_matrix_type(C);
        } else {
            S21_MATRIX_SET_INCORRECT_NULL(*result);
            exit_code = BAD_CALC;
        }
    }
    return exit_code;
}

//  OK
//  C = A - B
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && B && result) {
        exit_code = OK;
        if (S21_MATRIX_COMPARE_SIZE_SAFE(*A, *B)) {
            matrix_t temp;
            s21_create_matrix((*A).rows, (*A).columns, &temp);
            for (int i = 0; i < temp.rows; i++) {
                for (int j = 0; j < temp.columns; j++)
                    temp.matrix[i][j] = (*A).matrix[i][j] - (*B).matrix[i][j];
            }
            s21_A_to_B(&temp, result);
            //  (*result).matrix_type = s21_check_matrix_type(C);
        } else {
            S21_MATRIX_SET_INCORRECT_NULL(*result);
            exit_code = BAD_CALC;
        }
    }
    return exit_code;
}

//  OK
//  B = nA
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && result) {
        exit_code = OK;
        if (S21_MATRIX_CHECK_SIZE_SAFE(*A)) {
            matrix_t temp;
            s21_create_matrix((*A).rows, (*A).columns, &temp);
            matrix_type_t A_type = s21_check_matrix_type(*A);
            if ((number != 0.0) && A_type != ZERO_MATRIX) {
                for (int i = 0; i < temp.rows; i++) {
                    for (int j = 0; j < temp.columns; j++) {
                        temp.matrix[i][j] = (*A).matrix[i][j] * number;
                    }
                }
            }
            s21_A_to_B(&temp, result);
        } else {
            S21_MATRIX_SET_INCORRECT_NULL(*result);
            exit_code = BAD_CALC;
        }
    }
    return exit_code;
}

//  OK
//  C = A * B
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && B && result) {
        exit_code = OK;
        if (S21_MATRIX_COMPARE_SIZE_MUL_SAFE(*A, *B)) {
            matrix_t temp;
            s21_create_matrix((*A).rows, (*B).columns, &temp);
            for (int i = 0; i < temp.rows; i++) {
                for (int k = 0; k < (*A).columns; k++) {
                    for (int j = 0; j < temp.columns; j++) {
                        temp.matrix[i][j] += (*A).matrix[i][k] * (*B).matrix[k][j];
                    }
                }
            }
            s21_A_to_B(&temp, result);
            //  C.matrix_type = s21_check_matrix_type(C);
        } else {
            S21_MATRIX_SET_INCORRECT_NULL(*result);
            exit_code = BAD_CALC;
        }
    }
    return exit_code;
}

//  OK
//  B = A ^ T
int s21_transpose(matrix_t *A, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && result) {
        if (S21_MATRIX_CHECK_SIZE_SAFE(*A)) {
            exit_code = OK;
            matrix_t temp;
            s21_create_matrix((*A).columns, (*A).rows, &temp);
            for (int i = 0; i < temp.rows; i++) {
                for (int j = 0; j < temp.columns; j++)
                    temp.matrix[i][j] = (*A).matrix[j][i];
            }
            s21_A_to_B(&temp, result);
            //  (B).matrix_type = s21_check_matrix_type(B);
        } else {
            exit_code = BAD_CALC;
            S21_MATRIX_SET_INCORRECT_NULL(*result);
        }
        //  printf("%p | Transpose\n", (*result).matrix);
    }
    return exit_code;
}

//  OK
//  det = |A|
int s21_determinant(matrix_t *A, double *result) {
    result_t exit_code = ERROR;
    if (A && result) {
        double det = 0.0;
        if (S21_MATRIX_CHECK_SQUARE_SAFE(*A)) {
            exit_code = OK;
            matrix_type_t A_type = s21_check_matrix_type(*A);
            if (A_type == ZERO_MATRIX) {
                //  NOTHING
            } else if (A_type == IDENTITY_MATRIX) {
                det = 1.0;
            } else if ((*A).rows == 1) {
                det = (*A).matrix[0][0];
            } else if ((*A).rows == 2) {
                det = S21_MATRIX_DETERMINANT_2DIM(*A);
            } else if ((*A).rows == 3) {
                det = S21_MATRIX_DETERMINANT_3DIM(*A);
            } else {
                for (int i = 0; i < (*A).columns; i++) {
                    matrix_t M = s21_minor_matrix(*A, 0, i);
                    //  double M_det = s21_determinant(&M);
                    double M_det;
                    s21_determinant(&M, &M_det);
                    if (i % 2) M_det = -M_det;
                    det += ((*A).matrix[0][i] * M_det);
                    s21_remove_matrix(&M);
                }
            }
        } else {
            det /= 0.0;
            exit_code = BAD_CALC;
        }
        *result = det;
    }
    return exit_code;
}

//  OK
//  a_ij * M
int s21_calc_complements(matrix_t *A, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && result) {
        if (S21_MATRIX_CHECK_SQUARE_SAFE(*A)) {
            matrix_t temp;
            s21_create_matrix((*A).rows, (*A).columns, &temp);
            if ((*A).rows == 1) {
                temp.matrix[0][0] = (*A).matrix[0][0];
            } else {
                for (int i = 0; i < (*A).rows; i++) {
                    for (int j = 0; j < (*A).columns; j++) {
                        matrix_t M = s21_minor_matrix(*A, i, j);
                        //  double M_det = s21_determinant(&M);
                        double M_det;
                        s21_determinant(&M, &M_det);
                        if ((i + j) % 2) M_det = -M_det;
                        temp.matrix[i][j] = M_det;
                        s21_remove_matrix(&M);
                    }
                }
            }
            s21_A_to_B(&temp, result);
            // matrix_type_t result_type = s21_check_matrix_type(*result);
            // if (result_type != INCORRECT_MATRIX)
            //     exit_code = OK;
            //  aM.matrix_type = s21_check_matrix_type(aM);
            exit_code = OK;
            //  printf("%p | Complements\n", (*result).matrix);
        } else {
            S21_MATRIX_SET_INCORRECT_NULL(*result);
            exit_code = BAD_CALC;
        }
    }
    return exit_code;
}

//  FIX
//  A^-1 = A^T / |A|
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    result_t exit_code = ERROR;
    if (A && result) {
        exit_code = BAD_CALC;
        if (S21_MATRIX_CHECK_SQUARE_SAFE(*A)) {
            matrix_type_t A_type = s21_check_matrix_type(*A);
            if (A_type != ZERO_MATRIX) {
                if (A_type == IDENTITY_MATRIX) {
                    s21_create_matrix((*A).rows, (*A).columns, result);
                    for (int i = 0; i < (*result).rows; i++)
                        (*result).matrix[i][i] = 1.0;
                    //  A_inv.matrix_type = IDENTITY_MATRIX;
                } else {
                    //  double det = s21_determinant(A);
                    double det;
                    s21_determinant(A, &det);
                    if ((det == det) && (det != 0.0)) {
                        matrix_t temp;
                        s21_calc_complements(A, result);
                        s21_transpose(result, &temp);
                        s21_remove_matrix(result);
                        s21_mult_number(&temp, (1.0/det), result);
                        s21_remove_matrix(&temp);
                        //  s21_check_matrix_type(A_inv);
                    } else {
                        S21_MATRIX_SET_INCORRECT_NULL(*result);
                    }
                }
                exit_code = OK;
            } else {
                S21_MATRIX_SET_INCORRECT_NULL(*result);
                //  exit_code = BAD_CALC;
            }
            //  printf("%p | Inverse\n", (*result).matrix);
        } else {
            S21_MATRIX_SET_INCORRECT_NULL(*result);
        }
    }
    return exit_code;
}

//  ----------------------------------------------------------------------------
//                                     INNER
//  ----------------------------------------------------------------------------
//  MATRIX TYPE CHECK
//  FIX
int s21_check_matrix_type_identity(matrix_t A) {
    int result = 0;
    if (S21_MATRIX_CHECK_SQUARE(A)) {
        result = 1;
        for (int i = 0; (i < A.rows) && result; i++) {
            for (int j = 0; j < A.columns; j++) {
                if (((A.matrix[i][j] != 0.0) && (i != j)) ||
                    ((i == j) && (A.matrix[i][j] != 1.0))) {
                    result = 0;
                    break;
                }
            }
        }
    }
    return result;
}
//  FIX
int s21_check_matrix_type_zero(matrix_t A) {
    int result = 0;
    if (S21_MATRIX_CHECK_SIZE(A)) {
        result = 1;
        for (int i = 0; (i < A.rows) && result; i++) {
            for (int j = 0; j < A.columns; j++) {
                if (A.matrix[i][j] != 0.0) {
                    result = 0;
                    break;
                }
            }
        }
    }
    return result;
}
//  FIX
int s21_check_matrix_type_incorrect(matrix_t A) {
    int result = 0;
    if (S21_MATRIX_CHECK_SIZE_SAFE(A)) {
        // for (int i = 0; (i < A.rows) && !result; i++) {
        //     for (int j = 0; j < A.columns; j++) {
        //         if (A.matrix[i][j] != A.matrix[i][j] ||
        //             A.matrix[i][j] ==  (1.0)/(0.0)   ||
        //             A.matrix[i][j] == -(1.0)/(0.0)) {
        //             result = 1;
        //             break;
        //         }
        //     }
        // }
    } else {
        result = 1;
    }
    return result;
}
//  FIX
int s21_check_matrix_type(matrix_t A) {
    matrix_type_t result = 0;
    if (s21_check_matrix_type_incorrect(A)) {
        result = INCORRECT_MATRIX;
    } else if (s21_check_matrix_type_identity(A)) {
        result = IDENTITY_MATRIX;
    } else if (s21_check_matrix_type_zero(A)) {
        result = ZERO_MATRIX;
    } else {
        result = CORRECT_MATRIX;
    }
    return result;
}
//  ----------------------------------------------------------------------------
//  MATRIX MINOR
//  FIX
matrix_t s21_minor_matrix(matrix_t A, int row, int column) {
    matrix_t M;
    if (S21_MATRIX_CHECK_MINOR_SAFE(A, row, column)) {
        s21_create_matrix(A.rows - 1, A.columns - 1, &M);
        for (int i = 0; i < A.rows - 1; i++) {
            for (int j = 0; j < A.columns - 1; j++)
                M.matrix[i][j] = A.matrix[(i < row) ? i : i + 1][(j < column) ? j : j + 1];
        }
    } else {
        S21_MATRIX_SET_INCORRECT_NULL(M);
    }
    return M;
}

int s21_A_to_B(matrix_t *A, matrix_t *B) {
    (*B).matrix  = (*A).matrix;
    (*B).rows    = (*A).rows;
    (*B).columns = (*A).columns;
    return 0;
}

//  ----------------------------------------------------------------------------
//                                     DEBUG
//  ----------------------------------------------------------------------------
//  FIX
// int s21_print_matrix(matrix_t A) {
//     if (A.matrix_type != INCORRECT_MATRIX) {
//         printf("%s\n", (A.matrix_type == CORRECT_MATRIX) ?
//                             ("CORRECT_MATRIX") : ((A.matrix_type == ZERO_MATRIX) ?
//                                 "ZERO_MATRIX" : "IDENTITY_MATRIX"));
//         for (int i = 0; i < A.rows; i++) {
//             for (int j = 0; j < A.columns; j++)
//                 printf("%+-16lf\t", A.matrix[i][j]);
//             printf("\n");
//         }
//     } else {
//         printf("%s\n", "INCORRECT MATRIX");
//     }
//     return 0;
// }
