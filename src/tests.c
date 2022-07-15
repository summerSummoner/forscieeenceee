#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "s21_matrix.h"

//  ----------------------------------------------------------------
//                      TEST FUNCTIONS/MACRO:
//  ----------------------------------------------------------------

/* #define S21_TEST_CREATE_FAIL(TEST_NAME, ROWS, COLUMNS, TYPE, RESULT)    \
    "\n  Test %s Failed"                                                \
    "\n    Expected: rows: %-11d | columns: %-11d | type: %d"           \
    "\n    Result:   rows: %-11d | columns: %-11d | type: %d",          \
    (TEST_NAME),                                                        \
    (ROWS),        (COLUMNS),        (TYPE),                            \
    (RESULT).rows, (RESULT).columns, (RESULT).matrix_type
*/

#define S21_TEST_REMOVE_FAIL(TEST_NAME, POINTER)    \
    "\n  Test %s Failed"                            \
    "\n    Pointer left: %p",                       \
    (TEST_NAME), (POINTER)

/* #define S21_TEST_COMPARE_FAIL(TEST_NAME, MATRIX_A, MATRIX_B)                                \
    "\n  Test %s Failed"                                                                    \
    "\n    A type: %d, A size: %-11d %-11d"                                                 \
    "\n    B type: %d, B size: %-11d %-11d"                                                 \
    "\n    Reason: %s",                                                                     \
    (TEST_NAME),                                                                            \
    (MATRIX_A).matrix_type, (MATRIX_A).rows, (MATRIX_A).columns,                            \
    (MATRIX_B).matrix_type, (MATRIX_B).rows, (MATRIX_B).columns,                            \
    ((MATRIX_A).matrix_type != (MATRIX_B).matrix_type) ? "A.value_type != B.value_type" :   \
        (((MATRIX_A).rows != (MATRIX_B).rows) ? "A.rows != B.rows" :                        \
            (((MATRIX_A).columns != (MATRIX_B).columns) ? "A.columns != B.columns" :        \
                "A.matrix values != B.matrix values"))
*/

#define S21_TEST_DETERMINANT_FAIL(TEST_NAME, RESULT, EXPECTED)  \
    "\n  Test %s Failed"                                        \
    "\n    Expected: %lf"                                       \
    "\n    Result:   %lf",                                      \
    (TEST_NAME), (RESULT), (EXPECTED)

#define S21_TEST_EMPTY_FAIL(TEST_NAME)  \
    "\n  Test %s Failed"                \
    "\n    NULL pointer test",          \
    (TEST_NAME)

// int s21_check_create(matrix_t result,
//                      int rows, int columns, matrix_type_t matrix_type) {
//     int check = 0;
//     if (result.matrix_type == matrix_type &&
//         result.rows == rows && result.columns == columns) {
//         if (matrix_type == INCORRECT_MATRIX && !result.matrix) {
//             check = 1;
//         } else if (matrix_type == ZERO_MATRIX && result.matrix) {
//             check = 1;
//             for (int i = 0; (i < rows) && check; i++) {
//                 for (int j = 0; j < columns; j++) {
//                     if (result.matrix[i][j] != 0.0) {
//                         check = 0;
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     return check;
// }

#define S21_TEST_FAIL_NEW(TEST_NAME, RESULT, EXPECTED)                  \
    "\n  Test %s Failed"                                                \
    "\n    Expected: %s"                                                \
    "\n    Result:   %s",                                               \
    (TEST_NAME),                                                        \
    (EXPECTED) ? ((EXPECTED == 1) ? "ERROR" : "BAD_CALC") : "OK",  \
    (RESULT)   ? ((RESULT == 1)   ? "ERROR" : "BAD_CALC") : "OK"

#define S21_TEST_COMPARE_FAIL_NEW(TEST_NAME)    \
    "\n  Test %s Failed"                        \
    "\n    Different Matrixes",                 \
    (TEST_NAME)

#define S21_TEST_CREATE_FAIL_NEW(TEST_NAME, ROWS, COLUMNS, RESULT)  \
    "\n  Test %s Failed"                                            \
    "\n    Expected: rows: %-11d | columns: %-11d"                  \
    "\n    Result:   rows: %-11d | columns: %-11d",                 \
    (TEST_NAME),                                                    \
    (ROWS),        (COLUMNS),                                       \
    (RESULT).rows, (RESULT).columns

int s21_check_create_new(matrix_t result,
                         int rows, int columns) {
    int check = 0;
    if (result.matrix &&
        result.rows    == rows &&
        result.columns == columns)
        check = 1;
    return check;
}

int s21_check_remove(matrix_t result) {
    return (result.matrix) ? 0 : 1;
}
int s21_compare_double(double a, double b) {
    double temp = a - b;
    return ((temp > 1e-7) || (temp < -1e-7)) ? 0 : 1;
}
int s21_compare_matrices(matrix_t A, matrix_t B) {
    int check = 0;
    // if (A.matrix_type == B.matrix_type &&
    //     A.rows == B.rows && A.columns == B.columns) {
    if (A.rows == B.rows && A.columns == B.columns) {
        check = 1;
        for (int i = 0; (i < A.rows) && check; i++) {
            for (int j = 0; j < A.columns; j++) {
                if (!s21_compare_double(A.matrix[i][j], B.matrix[i][j])) {
                    check = 0;
                    break;
                }
            }
        }
    }
    return check;
}

//  ----------------------------------------------------------------
//                        TESTS DEFINITIONS:
//  ----------------------------------------------------------------
//                            01) CREATE
//  ----------------------------------------------------------------

START_TEST(test_create_01) {
    int rows    = 1;
    int columns = 1;
    //  matrix_type_t type = ZERO_MATRIX;
    matrix_t result;
    s21_create_matrix(rows, columns, &result);
    // ck_assert_msg(s21_check_create(result, rows, columns, type),
    //               S21_TEST_CREATE_FAIL("test_create_01",
    //                                    rows, columns, type,
    //                                    result));
    ck_assert_msg(s21_check_create_new(result, rows, columns),
                  S21_TEST_CREATE_FAIL_NEW("test_create_01",
                                            rows, columns,
                                            result));
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_02) {
    int rows    = 10;
    int columns = 10;
    matrix_t result;
    s21_create_matrix(rows, columns, &result);
    ck_assert_msg(s21_check_create_new(result, rows, columns),
                  S21_TEST_CREATE_FAIL_NEW("test_create_02",
                                            rows, columns,
                                            result));
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_03) {
    int rows    = 123;
    int columns = 456;
    matrix_t result;
    s21_create_matrix(rows, columns, &result);
    ck_assert_msg(s21_check_create_new(result, rows, columns),
                  S21_TEST_CREATE_FAIL_NEW("test_create_03",
                                            rows, columns,
                                            result));
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_04) {
    int rows    = 0;
    int columns = 0;
    matrix_t result;
    result_t expected = s21_create_matrix(rows, columns, &result);
    ck_assert_msg(expected == ERROR,
                  S21_TEST_CREATE_FAIL_NEW("test_create_04",
                                           rows, columns,
                                           result));
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_05) {
    int rows    = -123;
    int columns =  10;
    matrix_t result;
    result_t expected = s21_create_matrix(rows, columns, &result);
    ck_assert_msg(expected == ERROR,
                  S21_TEST_CREATE_FAIL_NEW("test_create_05",
                                           rows, columns,
                                           result));
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_06) {
    int rows    = 10;
    int columns = -123;
    matrix_t result;
    result_t expected = s21_create_matrix(rows, columns, &result);
    ck_assert_msg(expected == ERROR,
                  S21_TEST_CREATE_FAIL_NEW("test_create_06",
                                           rows, columns,
                                           result));
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_07) {
    int rows    = -123;
    int columns = -123;
    matrix_t result;
    result_t expected = s21_create_matrix(rows, columns, &result);
    ck_assert_msg(expected == ERROR,
                  S21_TEST_CREATE_FAIL_NEW("test_create_07",
                                           rows, columns,
                                           result));
    s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                           02) REMOVE
//  ----------------------------------------------------------------

START_TEST(test_remove_01) {
    int rows    = 10;
    int columns = 10;
    matrix_t result;
    s21_create_matrix(rows, columns, &result);
    s21_remove_matrix(&result);
    ck_assert_msg(s21_check_remove(result),
                  S21_TEST_REMOVE_FAIL("test_remove_01", result.matrix));
}
END_TEST

START_TEST(test_remove_02) {
    int rows    = 0;
    int columns = 0;
    matrix_t result;
    s21_create_matrix(rows, columns, &result);
    s21_remove_matrix(&result);
    ck_assert_msg(s21_check_remove(result),
                  S21_TEST_REMOVE_FAIL("test_remove_02", result.matrix));
}
END_TEST

START_TEST(test_remove_03) {
    int rows    = -10;
    int columns = -10;
    matrix_t result;
    s21_create_matrix(rows, columns, &result);
    s21_remove_matrix(&result);
    ck_assert_msg(s21_check_remove(result),
                  S21_TEST_REMOVE_FAIL("test_remove_03", result.matrix));
}
END_TEST

//  ----------------------------------------------------------------
//                           03) EQUAL
//  ----------------------------------------------------------------

START_TEST(test_equal_01) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    int result   = s21_eq_matrix(&A, &B);
    int expected = SUCCESS;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_02) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 12,
        B_columns = 12;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    int result   = s21_eq_matrix(&A, &B);
    int expected = FAILURE;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_03) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[0][1] = 10.0;
    B.matrix[0][1] = 10.0;
    int result   = s21_eq_matrix(&A, &B);
    int expected = SUCCESS;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_04) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[0][1] =  10.0;
    int result   = s21_eq_matrix(&A, &B);
    int expected = FAILURE;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_04"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_05) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[0][1] /= 0.0;
    B.matrix[0][1] /= 0.0;
    int result   = s21_eq_matrix(&A, &B);
    int expected = FAILURE;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_05"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_06) {
    int A_rows    = -10,
        A_columns = -10;
    int B_rows    =  10,
        B_columns =  10;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    int result   = s21_eq_matrix(&A, &B);
    int expected = FAILURE;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_06"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_07) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    int result   = s21_eq_matrix(&A, &B);
    int expected = SUCCESS;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_07"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_equal_08) {
    int result   = s21_eq_matrix(NULL, NULL);
    int expected = FAILURE;
    ck_assert_msg(result == expected,
                  S21_TEST_COMPARE_FAIL_NEW("test_equal_08"));
}
END_TEST

//  ----------------------------------------------------------------
//                            04) SUM
//  ----------------------------------------------------------------

START_TEST(test_sum_01) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    s21_sum_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sum_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_02) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[2][3] = 123.456;
    //  A.matrix_type = CORRECT_MATRIX;
    s21_sum_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    expected.matrix[2][3] = 123.456;
    //  expected.matrix_type = CORRECT_MATRIX;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sum_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_03) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[2][3] =  123.456;
    //  A.matrix_type = CORRECT_MATRIX;
    B.matrix[2][3] = -123.456;
    //  B.matrix_type = CORRECT_MATRIX;
    s21_sum_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sum_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_04) {
    int A_rows    = 12,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    result_t resint = s21_sum_matrix(&A, &B, &result);
    s21_create_matrix(0, 0, &expected);
    ck_assert_msg((resint != BAD_CALC) || s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sum_04"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

// START_TEST(test_sum_05) {
//     int A_rows    = 10,
//         A_columns = 10;
//     int B_rows    = 10,
//         B_columns = 10;
//     matrix_t A = s21_create_matrix(A_rows, A_columns);
//     matrix_t B = s21_create_matrix(B_rows, B_columns);
//     A.matrix_type = INCORRECT_MATRIX;
//     matrix_t result   = s21_sum_matrix(&A, &B);
//     matrix_t expected = s21_create_matrix(0, 0);
//     expected.matrix_type = INCORRECT_MATRIX;
//     ck_assert_msg(s21_compare_matrices(result, expected),
//                   S21_TEST_COMPARE_FAIL_NEW("test_sum_05"));
//     s21_remove_matrix(&A);
//     s21_remove_matrix(&B);
//     s21_remove_matrix(&result);
//     s21_remove_matrix(&expected);
// }
// END_TEST

// START_TEST(test_sum_06) {
//     int A_rows    = 10,
//         A_columns = 10;
//     int B_rows    = 10,
//         B_columns = 10;
//     matrix_t A = s21_create_matrix(A_rows, A_columns);
//     matrix_t B = s21_create_matrix(B_rows, B_columns);
//     matrix_t expected = s21_create_matrix(10, 10);
//     for (int i = 0; i < 10; i++) {
//         A.matrix[i][i] = 2.0;
//         B.matrix[i][i] = -1.0;
//         expected.matrix[i][i] = 1.0;
//     }
//     A.matrix_type        = CORRECT_MATRIX;
//     B.matrix_type        = CORRECT_MATRIX;
//     expected.matrix_type = IDENTITY_MATRIX;
//     matrix_t result   = s21_sum_matrix(&A, &B);
//     ck_assert_msg(s21_compare_matrices(result, expected),
//                   S21_TEST_COMPARE_FAIL_NEW("test_sum_06"));
//     s21_remove_matrix(&A);
//     s21_remove_matrix(&B);
//     s21_remove_matrix(&result);
//     s21_remove_matrix(&expected);
// }
// END_TEST

START_TEST(test_sum_05) {
    matrix_t result;
    result_t resint = s21_sum_matrix(NULL, NULL, &result);
    ck_assert_msg(resint == ERROR,
                  S21_TEST_EMPTY_FAIL("test_sum_05"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                            05) SUB
//  ----------------------------------------------------------------

START_TEST(test_sub_01) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    s21_sub_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sub_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sub_02) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[2][3] = 123.456;
    s21_sub_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    expected.matrix[2][3] = 123.456;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sub_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sub_03) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    A.matrix[2][3] = 123.456;
    B.matrix[2][3] = 123.456;
    s21_sub_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sub_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sub_04) {
    int A_rows    = 12,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    s21_sub_matrix(&A, &B, &result);
    s21_create_matrix(0, 0, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_sub_04"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

// START_TEST(test_sub_05) {
//     int A_rows    = 10,
//         A_columns = 10;
//     int B_rows    = 10,
//         B_columns = 10;
//     matrix_t A = s21_create_matrix(A_rows, A_columns);
//     matrix_t B = s21_create_matrix(B_rows, B_columns);
//     A.matrix_type = INCORRECT_MATRIX;
//     matrix_t result   = s21_sub_matrix(&A, &B);
//     matrix_t expected = s21_create_matrix(0, 0);
//     expected.matrix_type = INCORRECT_MATRIX;
//     ck_assert_msg(s21_compare_matrices(result, expected),
//                   S21_TEST_COMPARE_FAIL("test_sub_05", result, expected));
//     s21_remove_matrix(&A);
//     s21_remove_matrix(&B);
//     s21_remove_matrix(&result);
//     s21_remove_matrix(&expected);
// }
// END_TEST

// START_TEST(test_sub_06) {
//     int A_rows    = 10,
//         A_columns = 10;
//     int B_rows    = 10,
//         B_columns = 10;
//     matrix_t A = s21_create_matrix(A_rows, A_columns);
//     matrix_t B = s21_create_matrix(B_rows, B_columns);
//     matrix_t expected = s21_create_matrix(10, 10);
//     for (int i = 0; i < 10; i++) {
//         A.matrix[i][i] = 2.0;
//         B.matrix[i][i] = 1.0;
//         expected.matrix[i][i] = 1.0;
//     }
//     A.matrix_type        = CORRECT_MATRIX;
//     B.matrix_type        = CORRECT_MATRIX;
//     expected.matrix_type = IDENTITY_MATRIX;
//     matrix_t result   = s21_sub_matrix(&A, &B);
//     ck_assert_msg(s21_compare_matrices(result, expected),
//                   S21_TEST_COMPARE_FAIL("test_sub_06", result, expected));
//     s21_remove_matrix(&A);
//     s21_remove_matrix(&B);
//     s21_remove_matrix(&result);
//     s21_remove_matrix(&expected);
// }
// END_TEST

START_TEST(test_sub_05) {
    matrix_t result;
    // matrix_t result   = s21_sub_matrix(NULL, NULL);
    // matrix_t expected = s21_create_matrix(0, 0);
    result_t resint = s21_sub_matrix(NULL, NULL, &result);
    ck_assert_msg(resint == ERROR,
                  S21_TEST_EMPTY_FAIL("test_sub_05"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                       06) MUL BY NUMBER
//  ----------------------------------------------------------------

START_TEST(test_mul_by_number_01) {
    int A_rows    = 10,
        A_columns = 20;
    double number = 0;
    // matrix_t A = s21_create_matrix(A_rows, A_columns);
    // matrix_t result   = s21_mult_number(&A, number);
    // matrix_t expected = s21_create_matrix(A_rows, A_columns);
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_mult_number(&A, number, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_by_number_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_by_number_02) {
    int A_rows    = 10,
        A_columns = 20;
    double number = 10;
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_mult_number(&A, number, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_by_number_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_by_number_03) {
    int A_rows    = 10,
        A_columns = 20;
    double number = 0;
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[1][2] = 123.456;
    s21_mult_number(&A, number, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_by_number_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_by_number_04) {
    int A_rows    = 10,
        A_columns = 20;
    double number = 2;
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(A_rows, A_columns, &expected);
    A.matrix[1][2] = 123.456;
    expected.matrix[1][2] = 246.912;
    s21_mult_number(&A, number, &result);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_by_number_04"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_by_number_05) {
    int A_rows    = 10,
        A_columns = 10;
    double number = 0.5;
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(A_rows, A_columns, &expected);
    for (int i = 0; i < 10; i++) {
        A.matrix[i][i] = 2.0;
        expected.matrix[i][i] = 1.0;
    }
    s21_mult_number(&A, number, &result);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_by_number_05"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_by_number_06) {
    matrix_t result;
    result_t resint = s21_mult_number(NULL, 123, &result);
    ck_assert_msg(resint == ERROR,
                  S21_TEST_EMPTY_FAIL("test_mul_by_number_06"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                            07) MUL
//  ----------------------------------------------------------------

START_TEST(test_mul_01) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 10,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    s21_mult_matrix(&A, &B, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_02) {
    int A_rows    = 3,
        A_columns = 3;
    int B_rows    = 3,
        B_columns = 3;
    matrix_t A, B;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    s21_create_matrix(A_rows, A_columns, &expected);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A.matrix[i][j] = (double)3*i + j + 1;
            B.matrix[i][j] = 10.0 - A.matrix[i][j];
        }
    }
    expected.matrix[0][0] = 30.0;
    expected.matrix[0][1] = 24.0;
    expected.matrix[0][2] = 18.0;
    expected.matrix[1][0] = 84.0;
    expected.matrix[1][1] = 69.0;
    expected.matrix[1][2] = 54.0;
    expected.matrix[2][0] = 138.0;
    expected.matrix[2][1] = 114.0;
    expected.matrix[2][2] = 90.0;
    s21_mult_matrix(&A, &B, &result);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mul_03) {
    int A_rows    = 10,
        A_columns = 10;
    int B_rows    = 50,
        B_columns = 10;
    matrix_t A, B;
    matrix_t result;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_create_matrix(B_rows, B_columns, &B);
    result_t expected = s21_mult_matrix(&A, &B, &result);
    ck_assert_msg(expected == BAD_CALC,
                  S21_TEST_COMPARE_FAIL_NEW("test_mul_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mul_04) {
    matrix_t result;
    result_t resint = s21_mult_matrix(NULL, NULL, &result);
    ck_assert_msg(resint == ERROR,
                  S21_TEST_EMPTY_FAIL("test_mul_04"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                          08) TRANSPOSE
//  ----------------------------------------------------------------

START_TEST(test_transpose_01) {
    int A_rows    = 10,
        A_columns = 20;
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_transpose(&A, &result);
    s21_create_matrix(A_columns, A_rows, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_transpose_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_transpose_02) {
    int A_rows    = 2,
        A_columns = 4;
    matrix_t A;
    matrix_t result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[0][0] = 123.0;
    A.matrix[1][0] = 456.0;
    s21_transpose(&A, &result);
    s21_create_matrix(A_columns, A_rows, &expected);
    expected.matrix[0][0] = 123.0;
    expected.matrix[0][1] = 456.0;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_transpose_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_transpose_03) {
    matrix_t result;
    result_t resint = s21_transpose(NULL, &result);
    ck_assert_msg(resint == ERROR,
                  S21_TEST_COMPARE_FAIL_NEW("test_transpose_03"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                         09) DETERMINANT
//  ----------------------------------------------------------------

START_TEST(test_determinant_01) {
    int A_rows    = 10,
        A_columns = 20;
    matrix_t A;
    s21_create_matrix(A_rows, A_columns, &A);
    //  matrix_t A = s21_create_matrix(A_rows, A_columns);
    // double result   = s21_determinant(&A);
    double result;
    s21_determinant(&A, &result);
    double expected = 0.0;
    expected /= 0.0;
    ck_assert_msg(s21_compare_double(result, expected),
                  S21_TEST_DETERMINANT_FAIL("test_determinant_01", result, expected));
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_02) {
    int A_rows    = 5,
        A_columns = 5;
    matrix_t A;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[0][0] = 20.0;
    A.matrix[0][1] = 2.0;
    A.matrix[1][0] = 5.0;
    A.matrix[1][1] = 1.0;
    A.matrix[2][2] = 1.0;
    A.matrix[3][3] = 1.0;
    A.matrix[4][4] = 1.0;
    double result;
    s21_determinant(&A, &result);
    double expected = 10.0;
    ck_assert_msg(s21_compare_double(result, expected),
                  S21_TEST_DETERMINANT_FAIL("test_determinant_02", result, expected));
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_03) {
    double result;
    result_t resint = s21_determinant(NULL, &result);
    ck_assert_msg(resint == ERROR,
                  S21_TEST_EMPTY_FAIL("test_determinant_03"));
}
END_TEST

//  ----------------------------------------------------------------
//                          10) COMPLEMENTS
//  ----------------------------------------------------------------

START_TEST(test_complements_01) {
    int A_rows    = 10,
        A_columns = 20;
    matrix_t A, result;
    s21_create_matrix(A_rows, A_columns, &A);
    result_t expected = s21_calc_complements(&A, &result);
    ck_assert_msg(expected == BAD_CALC,
                  S21_TEST_COMPARE_FAIL_NEW("test_complements_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_complements_02) {
    int A_rows    = 10,
        A_columns = 10;
    matrix_t A, result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    s21_calc_complements(&A, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_complements_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_complements_03) {
    int A_rows    = 3,
        A_columns = 3;
    matrix_t A, result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[0][0] = 10.0;
    A.matrix[1][1] = 1.0;
    A.matrix[1][2] = 1.0;
    A.matrix[2][2] = 1.0;
    s21_calc_complements(&A, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    expected.matrix[0][0] =  1.0;
    expected.matrix[1][1] =  10.0;
    expected.matrix[2][1] = -10.0;
    expected.matrix[2][2] =  10.0;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_complements_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_complements_04) {
    int A_rows    = 5,
        A_columns = 5;
    matrix_t A, result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[0][0] = 20.0;
    A.matrix[0][1] = 2.0;
    A.matrix[1][0] = 5.0;
    A.matrix[1][1] = 1.0;
    A.matrix[2][2] = 1.0;
    A.matrix[3][3] = 1.0;
    A.matrix[4][4] = 1.0;
    s21_calc_complements(&A, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    expected.matrix[0][0] =  1.0;
    expected.matrix[0][1] = -5.0;
    expected.matrix[1][0] = -2.0;
    expected.matrix[1][1] =  20.0;
    expected.matrix[2][2] =  10.0;
    expected.matrix[3][3] =  10.0;
    expected.matrix[4][4] =  10.0;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_complements_04"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_complements_05) {
    matrix_t result;
    result_t expected = s21_calc_complements(NULL, &result);
    ck_assert_msg(expected == ERROR,
                  S21_TEST_EMPTY_FAIL("test_complements_05"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                          11) INVERSION
//  ----------------------------------------------------------------

START_TEST(test_inversion_01) {
    int A_rows    = 10,
        A_columns = 20;
    matrix_t A, result;
    s21_create_matrix(A_rows, A_columns, &A);
    result_t expected = s21_inverse_matrix(&A, &result);
    ck_assert_msg(expected == BAD_CALC,
                  S21_TEST_COMPARE_FAIL_NEW("test_inversion_01"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inversion_02) {
    int A_rows    = 3,
        A_columns = 3;
    matrix_t A, result;
    s21_create_matrix(A_rows, A_columns, &A);
    result_t expected = s21_inverse_matrix(&A, &result);
    ck_assert_msg(expected == BAD_CALC,
                  S21_TEST_COMPARE_FAIL_NEW("test_inversion_02"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inversion_03) {
    int A_rows    = 3,
        A_columns = 3;
    matrix_t A, result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[0][0] = 10.0;
    A.matrix[1][1] = 1.0;
    A.matrix[1][2] = 1.0;
    A.matrix[2][2] = 1.0;
    s21_inverse_matrix(&A, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    expected.matrix[0][0] =  0.1;
    expected.matrix[1][1] =  1.0;
    expected.matrix[1][2] = -1.0;
    expected.matrix[2][2] =  1.0;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_inversion_03"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inversion_04) {
    int A_rows    = 5,
        A_columns = 5;
    matrix_t A, result, expected;
    s21_create_matrix(A_rows, A_columns, &A);
    A.matrix[0][0] = 20.0;
    A.matrix[0][1] = 2.0;
    A.matrix[1][0] = 5.0;
    A.matrix[1][1] = 1.0;
    A.matrix[2][2] = 1.0;
    A.matrix[3][3] = 1.0;
    A.matrix[4][4] = 1.0;
    s21_inverse_matrix(&A, &result);
    s21_create_matrix(A_rows, A_columns, &expected);
    expected.matrix[0][0] =  0.1;
    expected.matrix[0][1] = -0.2;
    expected.matrix[1][0] = -0.5;
    expected.matrix[1][1] =  2.0;
    expected.matrix[2][2] =  1.0;
    expected.matrix[3][3] =  1.0;
    expected.matrix[4][4] =  1.0;
    ck_assert_msg(s21_compare_matrices(result, expected),
                  S21_TEST_COMPARE_FAIL_NEW("test_inversion_04"));
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inversion_05) {
    matrix_t result;
    result_t expected = s21_inverse_matrix(NULL, &result);
    ck_assert_msg(expected == ERROR,
                  S21_TEST_EMPTY_FAIL("test_inversion_05"));
    //  s21_remove_matrix(&result);
}
END_TEST

//  ----------------------------------------------------------------
//                          TESTS SUITE:
//  ----------------------------------------------------------------

Suite *s21_decimal_suite(void) {
    //  Definitons:
    Suite *s;
    s = suite_create("s21_matrix");

    TCase *tc_create,           *tc_remove;
    TCase *tc_equal;
    TCase *tc_sum,              *tc_sub;
    TCase *tc_mul_by_number,    *tc_mul;
    TCase *tc_transpose;
    TCase *tc_determinant;
    TCase *tc_complements,      *tc_inversion;

//  ----------------------------------------------------------------
//  CREATE
    tc_create = tcase_create("test_case_create");
    //  CASES
    tcase_add_test(tc_create, test_create_01);
    tcase_add_test(tc_create, test_create_02);
    tcase_add_test(tc_create, test_create_03);
    tcase_add_test(tc_create, test_create_04);
    tcase_add_test(tc_create, test_create_05);
    tcase_add_test(tc_create, test_create_06);
    tcase_add_test(tc_create, test_create_07);
    //  SUITE ADD
    suite_add_tcase(s, tc_create);

//  REMOVE
    tc_remove = tcase_create("test_case_remove");
    //  CASES
    tcase_add_test(tc_remove, test_remove_01);
    tcase_add_test(tc_remove, test_remove_02);
    tcase_add_test(tc_remove, test_remove_03);
    //  SUITE ADD
    suite_add_tcase(s, tc_remove);

//  ----------------------------------------------------------------
//  EQUAL
    tc_equal = tcase_create("test_case_equal");
    //  CASES
    tcase_add_test(tc_equal, test_equal_01);
    tcase_add_test(tc_equal, test_equal_02);
    tcase_add_test(tc_equal, test_equal_03);
    tcase_add_test(tc_equal, test_equal_04);
    tcase_add_test(tc_equal, test_equal_05);
    tcase_add_test(tc_equal, test_equal_06);
    tcase_add_test(tc_equal, test_equal_07);
    tcase_add_test(tc_equal, test_equal_08);
    //  SUITE ADD
    suite_add_tcase(s, tc_equal);

//  ----------------------------------------------------------------
//  SUM
    tc_sum = tcase_create("test_case_sum");
    //  CASES
    tcase_add_test(tc_sum, test_sum_01);
    tcase_add_test(tc_sum, test_sum_02);
    tcase_add_test(tc_sum, test_sum_03);
    tcase_add_test(tc_sum, test_sum_04);
    tcase_add_test(tc_sum, test_sum_05);
    //  SUITE ADD
    suite_add_tcase(s, tc_sum);

//  SUB
    tc_sub = tcase_create("test_case_sub");
    //  CASES
    tcase_add_test(tc_sub, test_sub_01);
    tcase_add_test(tc_sub, test_sub_02);
    tcase_add_test(tc_sub, test_sub_03);
    tcase_add_test(tc_sub, test_sub_04);
    tcase_add_test(tc_sub, test_sub_05);
    //  SUITE ADD
    suite_add_tcase(s, tc_sub);

//  ----------------------------------------------------------------
//  MUL BY NUMBER
    tc_mul_by_number = tcase_create("test_case_mul_by_number");
    //  CASES
    tcase_add_test(tc_mul_by_number, test_mul_by_number_01);
    tcase_add_test(tc_mul_by_number, test_mul_by_number_02);
    tcase_add_test(tc_mul_by_number, test_mul_by_number_03);
    tcase_add_test(tc_mul_by_number, test_mul_by_number_04);
    tcase_add_test(tc_mul_by_number, test_mul_by_number_05);
    tcase_add_test(tc_mul_by_number, test_mul_by_number_06);
    //  SUITE ADD
    suite_add_tcase(s, tc_mul_by_number);

//  MUL
    tc_mul = tcase_create("test_case_mul");
    //  CASES
    tcase_add_test(tc_mul, test_mul_01);
    tcase_add_test(tc_mul, test_mul_02);
    tcase_add_test(tc_mul, test_mul_03);
    tcase_add_test(tc_mul, test_mul_04);
    //  SUITE ADD
    suite_add_tcase(s, tc_mul);

//  ----------------------------------------------------------------
//  TRANSPOSE
    tc_transpose = tcase_create("test_case_transpose");
    //  CASES
    tcase_add_test(tc_transpose, test_transpose_01);
    tcase_add_test(tc_transpose, test_transpose_02);
    tcase_add_test(tc_transpose, test_transpose_03);
    //  SUITE ADD
    suite_add_tcase(s, tc_transpose);

//  ----------------------------------------------------------------
//  DETERMINANT
    tc_determinant = tcase_create("test_case_determinant");
    //  CASES
    tcase_add_test(tc_determinant, test_determinant_01);
    tcase_add_test(tc_determinant, test_determinant_02);
    tcase_add_test(tc_determinant, test_determinant_03);
    //  SUITE ADD
    suite_add_tcase(s, tc_determinant);

//  ----------------------------------------------------------------
//  COMPLEMENTS
    tc_complements = tcase_create("test_case_complements");
    //  CASES
    tcase_add_test(tc_complements, test_complements_01);
    tcase_add_test(tc_complements, test_complements_02);
    tcase_add_test(tc_complements, test_complements_03);
    tcase_add_test(tc_complements, test_complements_04);
    tcase_add_test(tc_complements, test_complements_05);
    //  SUITE ADD
    suite_add_tcase(s, tc_complements);

//  COMPLEMENTS
    tc_inversion = tcase_create("test_case_inversion");
    //  CASES
    tcase_add_test(tc_inversion, test_inversion_01);
    tcase_add_test(tc_inversion, test_inversion_02);
    tcase_add_test(tc_inversion, test_inversion_03);
    tcase_add_test(tc_inversion, test_inversion_04);
    tcase_add_test(tc_inversion, test_inversion_05);
    //  SUITE ADD
    suite_add_tcase(s, tc_inversion);

    return s;
}

int main(void) {
    int number_failed;

    Suite *s;
    SRunner *sr;

    s = s21_decimal_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
