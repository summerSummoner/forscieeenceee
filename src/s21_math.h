#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define S21_NAN         0.0/0.0
#define S21_INFINITY    1.0/0.0

#define S21_E           2.7182818284590452353602874713526624977572470936999595749669676277L     // exponent
#define S21_LN2         0.6931471805599453094172321214581765680755001343602552541206800094L     // ln(2)
#define S21_LN10        2.3025850929940456840179914546843642076011014886287729760333279009L     // ln(10)
#define S21_LN_1_1      0.0953101798043248600439521232807650922206053653086441991852398081L     // ln(1.1)
#define S21_2PI         6.2831853071795864769252867665590057683943387987502116419498891846L     // 2*pi
#define S21_PI          3.1415926535897932384626433832795028841971693993751058209749445923L     // pi
#define S21_PI_2        1.5707963267948966192313216916397514420985846996875529104874722961L     // pi/2
#define S21_PI_4        0.7853981633974483096156608458198757210492923498437764552437361480L     // pi/4
#define S21_ATAN_1_2    0.4636476090008061162142562314612144020285370542861202638109330887L     // atan(1/2)
#define S21_ATAN_3_2    0.9827937232473290679857106110146660144968774536316285567614250883L     // atan(3/2)

long int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif  // SRC_S21_MATH_H_
