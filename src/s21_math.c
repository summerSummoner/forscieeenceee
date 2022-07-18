#include <stdlib.h>
#include <stdio.h>

#include "s21_math.h"

long double s21_asin_series(long double x, long int n);
long double s21_cos_series(long double x, long int n);
long double s21_sin_series(long double x, long int n);
long double s21_sqrt_series(long double x, long int n);
long double s21_log_series(long double x, long int n);
long double s21_exp_series(long double x, long int n);
long double s21_factorial(long int n);
long double s21_pow_n(long double x, long int n);
int s21_isnan(double x);

long int s21_abs(int x) {
    long int z = (long int)x;
    z = (z > 0) ? z : -z;
    return z;
}

long double s21_acos(double x) {
    long double z;
    if (s21_isnan(x) || x > 1 || x < -1) {
        z = S21_NAN;
    } else if (x == 1.0) {
        z = 0.0L;
    } else if (x == -1.0) {
        z = S21_PI;
    } else {
        z = S21_PI_2 - s21_asin(x);
    }
    return z;
}

long double s21_asin(double x) {
    long double z;
    if (s21_isnan(x) || x > 1 || x < -1) {
        z = S21_NAN;
    } else if (x == 1.0) {
        z = S21_PI_2;
    } else if (x == -1.0) {
        z = -S21_PI_2;
    } else if (x >= 0 && x <= 0.5L) {
        z = s21_asin_series((long double)x, 100);
    } else if (x > 0.5L) {
        z = S21_PI_2 - 2.0L * s21_asin_series(s21_sqrt(0.5L - 0.5L * (long double)x), 100);
    } else {
        z = -s21_asin((long double)(-x));
    }
    return z;
}

long double s21_atan(double x) {
    long double z;
    long double x_l = s21_fabs(x);
    if (s21_isnan(x)) {
        z = S21_NAN;
    } else if (x_l <= 7.0L/16) {
        z = s21_asin(x_l / s21_sqrt(1 + s21_pow_n(x_l, 2)));
    } else if (x_l < 11.0L/16) {
        z = S21_ATAN_1_2 + s21_atan((x_l - 0.5L) / (1 + x_l * 0.5L));
    } else if (x_l < 19.0L/16) {
        z = S21_PI_4 + s21_atan((x_l - 1.0L) / (1 + x_l));
    } else if (x_l < 39.0L/16) {
        z = S21_ATAN_3_2 + s21_atan((x_l - 1.5L) / (1 + x_l * 1.5L));
    } else {
        z = S21_PI_2 - s21_atan(1.0L / x_l);
    }
    if (x < 0)
        z = -z;
    return z;
}

long double s21_ceil(double x) {
    long double z = S21_NAN;
    if (!s21_isnan(x)) {
        if (x == S21_INFINITY || x == -S21_INFINITY || x == 0.0
            || !((long long int)x - (long double)x)) {
            z = (long double)x;
        } else {
            z = (x > 0) ? (long double)((long long int)x + 1) : (long double)(long long int)x;
        }
    }
    return z;
}

long double s21_cos(double x) {
    long double z = S21_NAN;
    if (!s21_isnan(x)) {
        long double x_0;
        x_0 = s21_fmod(x, S21_2PI);
        z = s21_cos_series((long double)x_0, 80);
    }
    return z;
}

long double s21_exp(double x) {
    long double z = S21_NAN;
    if (!s21_isnan(x)) {
        if (x == 0.0) {
            z = 1;
        } else if (x == 1.0) {
            z = S21_E;
        } else if (x == S21_INFINITY) {
            z = S21_INFINITY;
        } else if (x == -S21_INFINITY) {
            z = 0;
        } else {
            long int k = (long int)(x / S21_LN2);
            long double x_0 = (long double)x - (long double)((long int)(x / S21_LN2) * S21_LN2);
            z = s21_pow_n(2, k) * s21_exp_series(x_0, 80);
        }
    }
    return z;
}

long double s21_fabs(double x) {
    long double z;
    z = (long double)x;
    z = (z > 0) ? z : -z;
    if (z == -0.0)
        z = 0;
    return z;
}

long double s21_floor(double x) {
    long double z = S21_NAN;
    if (!s21_isnan(x)) {
        if (x == S21_INFINITY || x == -S21_INFINITY || x == 0.0
            || !((long long int)x - (long double)x)) {
            z = (long double)x;
        } else {
            z = (x < 0) ? (long double)((long long int)x - 1) : (long double)(long long int)x;
        }
    }
    return z;
}

long double s21_fmod(double x, double y) {
    long double z = (long double)S21_NAN;
    if (!s21_isnan(x) && !s21_isnan(y)) {
        if (x == 0.0) {
            if (y != 0.0)
                z = (long double)x;
        } else if (x != S21_INFINITY && x != -S21_INFINITY) {
            if (y == S21_INFINITY || y == -S21_INFINITY) {
                z = (long double)x;
            } else if (y != 0.0) {
                long long int int_part = (long long int)((long double)x / (long double)y);
                z = (long double)x - (long double)(int_part * (long double)y);
            }
        }
    }
    return z;
}

long double s21_log(double x) {
    long double z = 0;
    if (s21_isnan(x) || x < 0) {
        z = S21_NAN;
    } else if (x == S21_INFINITY) {
        z = S21_INFINITY;
    } else if (x == 0) {
        z = -S21_INFINITY;
    } else {
        long int k = 0;
        long int n = 0;
        long int j = 0;
        long double x_0 = (long double)x;
        if (x >= 1) {
            while (s21_fabs(x_0) > 10) {
                x_0 /= 10.0L;
                k++;
            }
        } else {
            while (s21_fabs(x_0) < 1) {
                x_0 *= 10.0L;
                k--;
            }
        }
        while (s21_fabs(x_0) > 2) {
            x_0 /= 2.0L;
            n++;
        }
        while (s21_fabs(x_0) >= 1.1) {
            x_0 /= 1.1L;
            j++;
        }
        z = s21_log_series(x_0 - 1.0L, 120);
        z += (long double)(k * S21_LN10 + n * S21_LN2 + j * S21_LN_1_1);
    }
    return z;
}

long double s21_pow(double base, double exp) {
    long double z = S21_NAN;
    if ((float)(int)exp == exp) {
        z = s21_pow_n(base, exp);
    } else if (base == 1 || exp == 0) {
        z = 1;
    } else if (s21_isnan(base) || s21_isnan(exp)) {
        z = S21_NAN;
    } else if ((base > -1 && base < 0) || (base > 0 && base < 1)) {
        if (exp == S21_INFINITY) {
            z = 0;
        } else if (exp == -S21_INFINITY) {
            z = S21_INFINITY;
        } else {
            z = s21_exp((long double)exp * s21_log(base));
        }
    } else if ((base > 1 || base < -1) && !(base == S21_INFINITY || base == -S21_INFINITY)) {
        if (exp == S21_INFINITY) {
            z = S21_INFINITY;
        } else if (exp == -S21_INFINITY) {
            z = 0;
        } else {
            if (base < 0) {
                z = S21_NAN;
            } else {
                z = s21_exp((long double)exp * s21_log(base));
            }
        }
    } else if (base == 0) {
        if (exp < 0) {
            z = S21_INFINITY;
        } else {
            z = 0;
        }
    } else if (base == -1) {
        if (exp == S21_INFINITY || exp == -S21_INFINITY) {
            z = 1;
        } else {
            z = S21_NAN;
        }
    } else if (base == -S21_INFINITY) {
        if (exp > 0)
            z = S21_INFINITY;
    } else {
        z = s21_exp((long double)exp * s21_log(base));
    }
    return z;
}

long double s21_sin(double x) {
    long double z = S21_NAN;
    if (x != S21_INFINITY && x != -S21_INFINITY) {
        long double x_0;
        x_0 = s21_fmod(x, S21_2PI);
        z = s21_sin_series((long double)x_0, 100);
    }
    return z;
}

long double s21_sqrt(double x) {
    long double z;
    if (!s21_isnan(x)) {
        if (x > 0) {
            z = s21_sqrt_series((long double)x, 80);
        } else if (x == 0) {
            z = 0.0;
        } else {
            z = - S21_NAN;
        }
    } else {
        z = S21_NAN;
        }
    return z;
}

long double s21_tan(double x) {
    long double z;
    z = s21_sin(x)/s21_cos(x);
    return z;
}

long double s21_sqrt_series(long double x, long int n) {
    long double z = x;
    long int i = 1;
    while (i < n) {
        z = 0.5L * (z + x / z);
        i++;
    }
    return z;
}

long double s21_exp_series(long double x, long int n) {
    long double z = 1.0L;
    long double x_i = 1.0L;
    long int i = 1;
    while (i < n) {
        x_i *= x / (long double)i;
        z += x_i;
        i++;
    }
    return z;
}

long double s21_cos_series(long double x, long int n) {
    long double z = 0;
    long int i = 0;
    int sign = 1;
    while (i < n + 1) {
        long double x_i = sign * s21_pow_n(x, i) / s21_factorial(i);
        z += x_i;
        i += 2;
        sign = -sign;
    }
    return z;
}

long double s21_asin_series(long double x, long int n) {
    long double z = 0;
    long int i = 0;
    while (i < n + 1) {
        long double x_i = s21_factorial(2 * i) * s21_pow_n(x, 2 * i + 1) /
        (s21_factorial(i) * s21_factorial(i) * (2 * i + 1) * s21_pow_n(4, i));
        z += x_i;
        i++;
    }
    return z;
}

long double s21_sin_series(long double x, long int n) {
    long double z = 0;
    long int i = 1;
    int sign = 1;
    while (i < n + 1) {
        long double x_i = sign * s21_pow_n(x, i) / s21_factorial(i);
        z += x_i;
        i += 2;
        sign = -sign;
    }
    return z;
}

long double s21_log_series(long double x, long int n) {
    long double z = 0;
    long int i = 1;
    int sign = 1;
    while (i < n + 1) {
        long double x_i = sign * s21_pow_n(x, i) / (long double)i;
        z += x_i;
        i++;
        sign = -sign;
    }
    return z;
}

long double s21_factorial(long int n) {
    long double z;
    if (n > 0) {
        z = (long double)n * s21_factorial(n - 1);
    } else if (!n) {
        z = 1.0L;
    } else {
        fprintf(stderr, "Был использован факториал отрицательного числа! (n = %ld)\n", n);
        z = -1;
    }
    return z;
}

long double s21_pow_n(long double x, long int n) {
    long double z = 1.0L;
    for (long int i = 0; i < s21_abs(n); i++) {
        z = (n > 0) ? z * x : z / x;
    }
    if (x == 1 || n == 0)
        z = 1.0L;
    return z;
}

int s21_isnan(double x) {
    int ind = 0;
    if (x != x)
        ind = 1;
    return ind;
}
