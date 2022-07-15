#ifndef SRC_S21_MATRIX_INNER_H_
#define SRC_S21_MATRIX_INNER_H_

//  Left for type check functions
typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

//  ----------------------------------------------------------------------------
//  COMPARE COUNT OF ROWS AND COLUMNS
#define S21_MATRIX_SIZE_COMPARE_COLUMNS_TO_COLUMNS(A, B)    \
    ((A).columns == (B).columns)
#define S21_MATRIX_SIZE_COMPARE_ROWS_TO_ROWS(A, B)          \
    ((A).rows == (B).rows)
#define S21_MATRIX_SIZE_COMPARE_ROWS_TO_COLUMNS(A, B)       \
    ((A).rows == (B).columns)
#define S21_MATRIX_SIZE_COMPARE_COLUMNS_TO_ROWS(A, B)       \
    S21_MATRIX_SIZE_COMPARE_ROWS_TO_COLUMNS(B, A)

//  ----------------------------------------------------------------------------
//  CHECK MATRIX TYPE FOR INCORRECT
#define S21_MATRIX_CHECK_INCORRECT_SINGLE(A)    \
    (!((A).matrix))
//    ((A).matrix_type == INCORRECT_MATRIX)
#define S21_MATRIX_CHECK_CORRECT_SINGLE(A)      \
    (!S21_MATRIX_CHECK_INCORRECT_SINGLE(A))

#define S21_MATRIX_CHECK_INCORRECT(A, B)        \
    (S21_MATRIX_CHECK_INCORRECT_SINGLE(A) ||    \
     S21_MATRIX_CHECK_INCORRECT_SINGLE(B))
#define S21_MATRIX_CHECK_CORRECT(A, B)          \
    (!S21_MATRIX_CHECK_INCORRECT(A, B))

//  ----------------------------------------------------------------------------
// //  COMPARE MATRIX SIZE
#define S21_MATRIX_COMPARE_SIZE_SAFE(A, B)                  \
    (S21_MATRIX_CHECK_CORRECT(A, B) &&                      \
     S21_MATRIX_SIZE_COMPARE_COLUMNS_TO_COLUMNS(A, B) &&    \
     S21_MATRIX_SIZE_COMPARE_ROWS_TO_ROWS(A, B))
#define S21_MATRIX_COMPARE_SIZE_MUL_SAFE(A, B)              \
    (S21_MATRIX_CHECK_CORRECT(A, B) &&                      \
     S21_MATRIX_SIZE_COMPARE_COLUMNS_TO_ROWS(A, B))

//  ----------------------------------------------------------------------------
//  CHECK MATRIX SIZE
#define S21_MATRIX_CHECK_SIZE(A)                        \
    ((A).rows > 0 && (A).columns > 0)
#define S21_MATRIX_CHECK_SIZE_SAFE(A)                   \
    (S21_MATRIX_CHECK_CORRECT_SINGLE(A)  &&             \
     S21_MATRIX_CHECK_SIZE(A))
#define S21_MATRIX_CHECK_SQUARE(A)                      \
    (S21_MATRIX_SIZE_COMPARE_ROWS_TO_COLUMNS(A, A)  &&  \
     ((A).rows > 0))

#define S21_MATRIX_CHECK_SQUARE_SAFE(A)             \
    (S21_MATRIX_CHECK_CORRECT_SINGLE(A) &&          \
     S21_MATRIX_CHECK_SQUARE(A))
#define S21_MATRIX_CHECK_MINOR_SAFE(A, row, column) \
    (S21_MATRIX_CHECK_CORRECT_SINGLE(A) &&          \
     ((A).rows > 1 && (A).columns > 1)  &&          \
     (row < (A).rows) && (column < (A).columns))

//  ----------------------------------------------------------------------------
//  SET INCORRECT MATRIX
#define S21_MATRIX_SET_INCORRECT_NULL(A)    \
    (A).matrix  = NULL;                     \
    (A).rows    = 0;                        \
    (A).columns = 0
    /* (A).columns = 0;                        \
    (A).matrix_type = INCORRECT_MATRIX
    */
//  ----------------------------------------------------------------------------
//  DETERMINANT FOR SMALLER DIMENSIONS
#define S21_MATRIX_DETERMINANT_2DIM(A)          \
    (((A).matrix[0][0] * (A).matrix[1][1]) -    \
     ((A).matrix[1][0] * (A).matrix[0][1]))
#define S21_MATRIX_DETERMINANT_3DIM(A)                          \
    (((A).matrix[0][0] * (A).matrix[1][1] * (A).matrix[2][2]) - \
     ((A).matrix[2][2] * (A).matrix[1][0] * (A).matrix[0][1]) + \
     ((A).matrix[0][1] * (A).matrix[1][2] * (A).matrix[2][0]) - \
     ((A).matrix[2][0] * (A).matrix[1][1] * (A).matrix[0][2]) + \
     ((A).matrix[0][2] * (A).matrix[1][0] * (A).matrix[2][1]) - \
     ((A).matrix[2][1] * (A).matrix[1][2] * (A).matrix[0][0]))

#endif  // SRC_S21_MATRIX_INNER_H_
