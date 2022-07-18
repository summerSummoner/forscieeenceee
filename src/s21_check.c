#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "s21_math.h"

#define S21_EPS         0.0000009L     // eps

int check_funk(long double res_s21, double expectation) {
    int is_good = 0;
    if (isnan(expectation)) {
        is_good = (isnan(res_s21)) ? 1 : 0;
    } else if (isinf(expectation)) {
        if (expectation < 0)
            is_good = (isinf(res_s21) && (res_s21 < 0)) ? 1 : 0;
        else
            is_good = (isinf(res_s21) && (res_s21 > 0)) ? 1 : 0;
    } else {
        is_good = (s21_fabs(res_s21 - expectation) < S21_EPS) ? 1 : 0;
    }
    return is_good;
}

// Function 1
START_TEST(test_abs1) {
    long int res_s21;
    int expectation;
    res_s21 = s21_abs(1);
    expectation = abs(1);
    ck_assert_msg(res_s21 == expectation,
                    "\nTest_abs1 failed:\nres_s21:\n%ld\nexpected:\n%d\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_abs2) {
    long int res_s21;
    int expectation;
    res_s21 = s21_abs(-1);
    expectation = abs(-1);
    ck_assert_msg(res_s21 == expectation,
                    "\nTest_abs2 failed:\nres_s21:\n%ld\nexpected:\n%d\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_abs3) {
    long int res_s21;
    int expectation;
    res_s21 = s21_abs(0);
    expectation = abs(0);
    ck_assert_msg(res_s21 == expectation,
                    "\nTest_abs3 failed:\nres_s21:\n%ld\nexpected:\n%d\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_abs4) {
    long int res_s21;
    int expectation;
    res_s21 = s21_abs(-0);
    expectation = abs(-0);
    ck_assert_msg(res_s21 == expectation,
                    "\nTest_abs4 failed:\nres_s21:\n%ld\nexpected:\n%d\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_abs5) {
    long int res_s21;
    int expectation;
    res_s21 = s21_abs(1000000000);
    expectation = abs(1000000000);
    ck_assert_msg(res_s21 == expectation,
                    "\nTest_abs4 failed:\nres_s21:\n%ld\nexpected:\n%d\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_abs6) {
    long int res_s21;
    int expectation;
    res_s21 = s21_abs(-1000000000);
    expectation = abs(-1000000000);
    ck_assert_msg(res_s21 == expectation,
                    "\nTest_abs4 failed:\nres_s21:\n%ld\nexpected:\n%d\n",
                    res_s21, expectation);
}
END_TEST

// Function 2
START_TEST(test_acos1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(0);
    expectation = acos(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(-0);
    expectation = acos(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(1);
    expectation = acos(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(-1);
    expectation = acos(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(1000000000000000000.000001);
    expectation = acos(1000000000000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(-1000000000000000000.000001);
    expectation = acos(-1000000000000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(-1.0/0.0);
    expectation = acos(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(0.000001);
    expectation = acos(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_acos9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_acos(NAN);
    expectation = acos(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 3
START_TEST(test_asin1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(0);
    expectation = asin(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(-0);
    expectation = asin(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(1);
    expectation = asin(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(-1);
    expectation = asin(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(1000000000000000000);
    expectation = asin(1000000000000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(-1000000000000000000);
    expectation = asin(-1000000000000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(-1.0/0.0);
    expectation = asin(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(0.000001);
    expectation = asin(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(NAN);
    expectation = asin(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_asin10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_asin(0.5L);
    expectation = asin(0.5L);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 4
START_TEST(test_atan1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(0);
    expectation = atan(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(-0);
    expectation = atan(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(1);
    expectation = atan(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(-1);
    expectation = atan(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(1000000000000000000);
    expectation = atan(1000000000000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(-1000000000000000000);
    expectation = atan(-1000000000000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(-1.0/0.0);
    expectation = atan(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(0.000001);
    expectation = atan(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(NAN);
    expectation = atan(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(11.0L/16);
    expectation = atan(11.0L/16);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_atan11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_atan(39.0L/16);
    expectation = atan(39.0L/16);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 5
START_TEST(test_ceil1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(0);
    expectation = ceil(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(-0);
    expectation = ceil(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(3.000001);
    expectation = ceil(3.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(-3.000001);
    expectation = ceil(-3.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(999999999999999.1);
    expectation = ceil(999999999999999.1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(-999999999999999.1);
    expectation = ceil(-999999999999999.1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(1.0/0.0);
    expectation = ceil(1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(NAN);
    expectation = ceil(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_ceil9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_ceil(1.0);
    expectation = ceil(1.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 6
START_TEST(test_cos1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(0);
    expectation = cos(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(-0);
    expectation = cos(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(1);
    expectation = cos(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(-1);
    expectation = cos(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(10000000000);
    expectation = cos(10000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(-10000000000);
    expectation = cos(-10000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(-1.0/0.0);
    expectation = cos(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(0.000001);
    expectation = cos(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(NAN);
    expectation = cos(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(1.0/0.0);
    expectation = cos(1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(S21_PI);
    expectation = cos(S21_PI);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_cos12) {
    long double res_s21;
    double expectation;
    res_s21 = s21_cos(S21_PI_2);
    expectation = cos(S21_PI_2);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 7
START_TEST(test_exp1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(0);
    expectation = exp(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(-0);
    expectation = exp(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(1);
    expectation = exp(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(-1);
    expectation = exp(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(23);
    expectation = expl(23);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(-100);
    expectation = exp(-100);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(-1.0/0.0);
    expectation = exp(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(0.000001);
    expectation = exp(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(NAN);
    expectation = exp(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(-36.000001);
    expectation = exp(-36.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(S21_INFINITY);
    expectation = exp(S21_INFINITY);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_exp12) {
    long double res_s21;
    double expectation;
    res_s21 = s21_exp(-S21_INFINITY);
    expectation = exp(-S21_INFINITY);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 8
START_TEST(test_fabs1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(-1.0/0.0);
    expectation = fabs(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(-1.123456);
    expectation = fabs(-1.123456);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(0.000001);
    expectation = fabs(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(-0.000001);
    expectation = fabs(-0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(100000.123456);
    expectation = fabs(100000.123456);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(-100000.123456);
    expectation = fabs(-100000.123456);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(NAN);
    expectation = fabs(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fabs8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fabs(-NAN);
    expectation = fabs(-NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 9
START_TEST(test_floor1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(0);
    expectation = floor(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(-0);
    expectation = floor(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(0.000001);
    expectation = floor(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(-0.000001);
    expectation = floor(-0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(10000000000.000001);
    expectation = floor(10000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(-10000000000.000001);
    expectation = floor(-10000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(-1.0/0.0);
    expectation = floor(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_floor8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_floor(NAN);
    expectation = floor(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 10
START_TEST(test_fmod1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(0, 1);
    expectation = fmod(0, 1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(1, 0);
    expectation = fmod(1, 0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(1000, -0.000001);
    expectation = fmod(1000, -0.000001);
    ck_assert_msg(s21_fabs(res_s21 - expectation) < S21_EPS,
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(-100000, 0.00001);
    expectation = fmod(-100000, 0.00001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(0.000001, -100000);
    expectation = fmod(0.000001, -100000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(-0.000001, 100000);
    expectation = fmod(-0.000001, 100000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(0.000001, -1.0/0.0);
    expectation = fmod(0.000001, -1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(-1.0/0.0, 0.000001);
    expectation = fmod(-1.0/0.0, 0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(100000, -1.0/0.0);
    expectation = fmod(100000, -1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(-1.0/0.0, 100000);
    expectation = fmod(-1.0/0.0, 100000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(100000, NAN);
    expectation = fmod(100000, NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_fmod12) {
    long double res_s21;
    double expectation;
    res_s21 = s21_fmod(NAN, 100000);
    expectation = fmod(NAN, 100000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 11
START_TEST(test_log1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(0);
    expectation = log(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(0.000001);
    expectation = log(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(1);
    expectation = log(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(-1);
    expectation = log(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(1000000000000000.000001);
    expectation = log(1000000000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(-1000000000000000.000001);
    expectation = log(-1000000000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(1.0/0.0);
    expectation = log(1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(-0.000001);
    expectation = log(-0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(NAN);
    expectation = log(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(-NAN);
    expectation = log(-NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_log11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_log(-1.0/0.0);
    expectation = log(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 12
START_TEST(test_pow1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(0, 1);
    expectation = pow(0, 1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(1, 0);
    expectation = pow(1, 0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(1, -2.1);
    expectation = pow(1, -2.1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-1, 2);
    expectation = pow(-1, 2);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow5) {
    long double res_s21;
//    long double expectation2;
    double expectation;
    res_s21 = s21_pow(2, 53);
    expectation = pow(2, 53);
//    expectation2 = powl(2, 100);
//        printf("1234567890123456.\n%Lf\n%f\n%Lf\n", res_s21, expectation, expectation2);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(2, 0.00001);
    expectation = pow(2, 0.00001);
//    printf("%Lf\n%f\n", res_s21, expectation);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(1, -1.0/0.0);
    expectation = pow(1, -1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-1.0/0.0, 2);
    expectation = pow(-1.0/0.0, 2);
    // if (isnan(expectation))
    //     ck_assert_msg(isnan(res_s21),
    //                 "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
    //                 res_s21, expectation);
    // else if (isinf(expectation))
    //     ck_assert_msg(isinf(res_s21),
    //                 "\nTest failed:\nres_s2111111:\n%.16Lf\nexpected:\n%.16f\n",
    //                 res_s21, expectation);
    // else
    // ck_assert_msg(s21_fabs(res_s21 - expectation) < S21_EPS,
    //                 "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
    //                 res_s21, expectation);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-2, 0.00001);
    expectation = pow(-2, 0.00001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(0.00001, 1.0/0.0);
    expectation = pow(0.00001, 1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-2, NAN);
    expectation = pow(-2, NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow12) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(NAN, 1.0/0.0);
    expectation = pow(NAN, 1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow13) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-2.0, 1.5);
    expectation = pow(-2.0, 1.5);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow14) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-0.5, -S21_INFINITY);
    expectation = pow(-0.5, -S21_INFINITY);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_pow15) {
    long double res_s21;
    double expectation;
    res_s21 = s21_pow(-2.0, S21_INFINITY);
    expectation = pow(-2.0, S21_INFINITY);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 13
START_TEST(test_sin1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(NAN);
    expectation = sin(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(-0);
    expectation = sin(-0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(1);
    expectation = sin(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(-1);
    expectation = sin(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(10000000000);
    expectation = sin(10000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(-10000000000);
    expectation = sin(-10000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(-1.0/0.0);
    expectation = sin(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(0.000001);
    expectation = sin(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(S21_PI);
    expectation = sin(S21_PI);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sin10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sin(S21_PI_2);
    expectation = sin(S21_PI_2);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 14
START_TEST(test_sqrt1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(0.000001);
    expectation = sqrt(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(-0.000001);
    expectation = sqrt(-0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(-1);
    expectation = sqrt(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(1.000001);
    expectation = sqrt(1.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(0);
    expectation = sqrt(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(1000000000);
    expectation = sqrt(1000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(-1.0/0.0);
    expectation = sqrt(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(1000000000.000001);
    expectation = sqrt(1000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(NAN);
    expectation = sqrt(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_sqrt10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_sqrt(-1000000000.000001);
    expectation = sqrt(-1000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// Function 15
START_TEST(test_tan1) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(0);
    expectation = tan(0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan2) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(-0.000001);
    expectation = tan(-0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan3) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(1);
    expectation = tan(1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan4) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(-1);
    expectation = tan(-1);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan5) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(1000000000);
    expectation = tan(1000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan6) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(-1000000000);
    expectation = tan(-1000000000);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan7) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(-1.0/0.0);
    expectation = tan(-1.0/0.0);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan8) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(0.000001);
    expectation = tan(0.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan9) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(NAN);
    expectation = tan(NAN);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan10) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(1000000000.000001);
    expectation = tan(1000000000.000001);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan11) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(S21_PI);
    expectation = tan(S21_PI);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

START_TEST(test_tan12) {
    long double res_s21;
    double expectation;
    res_s21 = s21_tan(1.57);
    expectation = tan(1.57);
    ck_assert_msg(check_funk(res_s21, expectation),
                    "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
                    res_s21, expectation);
}
END_TEST

// START_TEST(test_tan12) {
//     long double res_s21;
//     double expectation;
//     res_s21 = s21_tan(S21_PI_2);
//     expectation = tan(S21_PI_2);
//     // printf("---===CONTROL POINT %Lf===---\n", s21_cos(S21_PI_2));
//     ck_assert_msg(check_funk(res_s21, expectation),
//                     "\nTest failed:\nres_s21:\n%.16Lf\nexpected:\n%.16f\n",
//                     res_s21, expectation);
// }
// END_TEST

Suite *s21_MathSuite(void) {
    Suite *s;
    TCase *tc_abs, *tc_acos, *tc_asin, *tc_atan, *tc_ceil, *tc_cos, *tc_exp;
    TCase *tc_fabs, *tc_floor, *tc_fmod, *tc_log, *tc_pow, *tc_sin, *tc_sqrt, *tc_tan;
    s = suite_create("s21_math");

    tc_abs = tcase_create("test_case_abs");
        tcase_add_test(tc_abs, test_abs1);
        tcase_add_test(tc_abs, test_abs2);
        tcase_add_test(tc_abs, test_abs3);
        tcase_add_test(tc_abs, test_abs4);
        tcase_add_test(tc_abs, test_abs5);
        tcase_add_test(tc_abs, test_abs6);
     suite_add_tcase(s, tc_abs);

    tc_acos = tcase_create("test_case_acos");
        tcase_add_test(tc_acos, test_acos1);
        tcase_add_test(tc_acos, test_acos2);
        tcase_add_test(tc_acos, test_acos3);
        tcase_add_test(tc_acos, test_acos4);
        tcase_add_test(tc_acos, test_acos5);
        tcase_add_test(tc_acos, test_acos6);
        tcase_add_test(tc_acos, test_acos7);
        tcase_add_test(tc_acos, test_acos8);
        tcase_add_test(tc_acos, test_acos9);
     suite_add_tcase(s, tc_acos);

    tc_asin = tcase_create("test_case_asin");
        tcase_add_test(tc_asin, test_asin1);
        tcase_add_test(tc_asin, test_asin2);
        tcase_add_test(tc_asin, test_asin3);
        tcase_add_test(tc_asin, test_asin4);
        tcase_add_test(tc_asin, test_asin5);
        tcase_add_test(tc_asin, test_asin6);
        tcase_add_test(tc_asin, test_asin7);
        tcase_add_test(tc_asin, test_asin8);
        tcase_add_test(tc_asin, test_asin9);
        tcase_add_test(tc_asin, test_asin10);
     suite_add_tcase(s, tc_asin);

    tc_atan = tcase_create("test_case_atan");
        tcase_add_test(tc_atan, test_atan1);
        tcase_add_test(tc_atan, test_atan2);
        tcase_add_test(tc_atan, test_atan3);
        tcase_add_test(tc_atan, test_atan4);
        tcase_add_test(tc_atan, test_atan5);
        tcase_add_test(tc_atan, test_atan6);
        tcase_add_test(tc_atan, test_atan7);
        tcase_add_test(tc_atan, test_atan8);
        tcase_add_test(tc_atan, test_atan9);
        tcase_add_test(tc_atan, test_atan10);
        tcase_add_test(tc_atan, test_atan11);
     suite_add_tcase(s, tc_atan);

    tc_ceil = tcase_create("test_case_ceil");
        tcase_add_test(tc_ceil, test_ceil1);
        tcase_add_test(tc_ceil, test_ceil2);
        tcase_add_test(tc_ceil, test_ceil3);
        tcase_add_test(tc_ceil, test_ceil4);
        tcase_add_test(tc_ceil, test_ceil5);
        tcase_add_test(tc_ceil, test_ceil6);
        tcase_add_test(tc_ceil, test_ceil7);
        tcase_add_test(tc_ceil, test_ceil8);
        tcase_add_test(tc_ceil, test_ceil9);
     suite_add_tcase(s, tc_ceil);

    tc_cos = tcase_create("test_case_cos");
        tcase_add_test(tc_cos, test_cos1);
        tcase_add_test(tc_cos, test_cos2);
        tcase_add_test(tc_cos, test_cos3);
        tcase_add_test(tc_cos, test_cos4);
        tcase_add_test(tc_cos, test_cos5);
        tcase_add_test(tc_cos, test_cos6);
        tcase_add_test(tc_cos, test_cos7);
        tcase_add_test(tc_cos, test_cos8);
        tcase_add_test(tc_cos, test_cos9);
        tcase_add_test(tc_cos, test_cos10);
        tcase_add_test(tc_cos, test_cos11);
        tcase_add_test(tc_cos, test_cos12);
    suite_add_tcase(s, tc_cos);

    tc_exp = tcase_create("test_case_exp");
        tcase_add_test(tc_exp, test_exp1);
        tcase_add_test(tc_exp, test_exp2);
        tcase_add_test(tc_exp, test_exp3);
        tcase_add_test(tc_exp, test_exp4);
        tcase_add_test(tc_exp, test_exp5);
        tcase_add_test(tc_exp, test_exp6);
        tcase_add_test(tc_exp, test_exp7);
        tcase_add_test(tc_exp, test_exp8);
        tcase_add_test(tc_exp, test_exp9);
        tcase_add_test(tc_exp, test_exp10);
        tcase_add_test(tc_exp, test_exp11);
        tcase_add_test(tc_exp, test_exp12);
    suite_add_tcase(s, tc_exp);

    tc_fabs = tcase_create("test_case_fabs");
        tcase_add_test(tc_fabs, test_fabs1);
        tcase_add_test(tc_fabs, test_fabs2);
        tcase_add_test(tc_fabs, test_fabs3);
        tcase_add_test(tc_fabs, test_fabs4);
        tcase_add_test(tc_fabs, test_fabs5);
        tcase_add_test(tc_fabs, test_fabs6);
        tcase_add_test(tc_fabs, test_fabs7);
        tcase_add_test(tc_fabs, test_fabs8);
    suite_add_tcase(s, tc_fabs);

    tc_floor = tcase_create("test_case_floor");
        tcase_add_test(tc_floor, test_floor1);
        tcase_add_test(tc_floor, test_floor2);
        tcase_add_test(tc_floor, test_floor3);
        tcase_add_test(tc_floor, test_floor4);
        tcase_add_test(tc_floor, test_floor5);
        tcase_add_test(tc_floor, test_floor6);
        tcase_add_test(tc_floor, test_floor7);
        tcase_add_test(tc_floor, test_floor8);
    suite_add_tcase(s, tc_floor);

    tc_fmod = tcase_create("test_case_fmod");
        tcase_add_test(tc_fmod, test_fmod1);
        tcase_add_test(tc_fmod, test_fmod2);
        tcase_add_test(tc_fmod, test_fmod3);
        tcase_add_test(tc_fmod, test_fmod4);
        tcase_add_test(tc_fmod, test_fmod5);
        tcase_add_test(tc_fmod, test_fmod6);
        tcase_add_test(tc_fmod, test_fmod7);
        tcase_add_test(tc_fmod, test_fmod8);
        tcase_add_test(tc_fmod, test_fmod9);
        tcase_add_test(tc_fmod, test_fmod10);
        tcase_add_test(tc_fmod, test_fmod11);
        tcase_add_test(tc_fmod, test_fmod12);
    suite_add_tcase(s, tc_fmod);

    tc_log = tcase_create("test_case_log");
        tcase_add_test(tc_log, test_log1);
        tcase_add_test(tc_log, test_log2);
        tcase_add_test(tc_log, test_log3);
        tcase_add_test(tc_log, test_log4);
        tcase_add_test(tc_log, test_log5);
        tcase_add_test(tc_log, test_log6);
        tcase_add_test(tc_log, test_log7);
        tcase_add_test(tc_log, test_log8);
        tcase_add_test(tc_log, test_log9);
        tcase_add_test(tc_log, test_log10);
        tcase_add_test(tc_log, test_log11);
    suite_add_tcase(s, tc_log);

    tc_pow = tcase_create("test_case_pow");
        tcase_add_test(tc_pow, test_pow1);
        tcase_add_test(tc_pow, test_pow2);
        tcase_add_test(tc_pow, test_pow3);
        tcase_add_test(tc_pow, test_pow4);
        tcase_add_test(tc_pow, test_pow5);
        tcase_add_test(tc_pow, test_pow6);
        tcase_add_test(tc_pow, test_pow7);
        tcase_add_test(tc_pow, test_pow8);
        tcase_add_test(tc_pow, test_pow9);
        tcase_add_test(tc_pow, test_pow10);
        tcase_add_test(tc_pow, test_pow11);
        tcase_add_test(tc_pow, test_pow12);
        tcase_add_test(tc_pow, test_pow13);
        tcase_add_test(tc_pow, test_pow14);
        tcase_add_test(tc_pow, test_pow15);
    suite_add_tcase(s, tc_pow);

    tc_sin = tcase_create("test_case_sin");
        tcase_add_test(tc_sin, test_sin1);
        tcase_add_test(tc_sin, test_sin2);
        tcase_add_test(tc_sin, test_sin3);
        tcase_add_test(tc_sin, test_sin4);
        tcase_add_test(tc_sin, test_sin5);
        tcase_add_test(tc_sin, test_sin6);
        tcase_add_test(tc_sin, test_sin7);
        tcase_add_test(tc_sin, test_sin8);
        tcase_add_test(tc_sin, test_sin9);
        tcase_add_test(tc_sin, test_sin10);
    suite_add_tcase(s, tc_sin);

    tc_sqrt = tcase_create("test_case_sqrt");
        tcase_add_test(tc_sqrt, test_sqrt1);
        tcase_add_test(tc_sqrt, test_sqrt2);
        tcase_add_test(tc_sqrt, test_sqrt3);
        tcase_add_test(tc_sqrt, test_sqrt4);
        tcase_add_test(tc_sqrt, test_sqrt5);
        tcase_add_test(tc_sqrt, test_sqrt6);
        tcase_add_test(tc_sqrt, test_sqrt7);
        tcase_add_test(tc_sqrt, test_sqrt8);
        tcase_add_test(tc_sqrt, test_sqrt9);
        tcase_add_test(tc_sqrt, test_sqrt10);
    suite_add_tcase(s, tc_sqrt);

    tc_tan = tcase_create("test_case_tan");
        tcase_add_test(tc_tan, test_tan1);
        tcase_add_test(tc_tan, test_tan2);
        tcase_add_test(tc_tan, test_tan3);
        tcase_add_test(tc_tan, test_tan4);
        tcase_add_test(tc_tan, test_tan5);
        tcase_add_test(tc_tan, test_tan6);
        tcase_add_test(tc_tan, test_tan7);
        tcase_add_test(tc_tan, test_tan8);
        tcase_add_test(tc_tan, test_tan9);
        tcase_add_test(tc_tan, test_tan10);
        tcase_add_test(tc_tan, test_tan11);
        tcase_add_test(tc_tan, test_tan12);
    suite_add_tcase(s, tc_tan);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = s21_MathSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
