#ifndef CEVAL_FUNCTIONS
#define CEVAL_FUNCTIONS

#include "./tokens.h"

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

//constant definitions
const float CEVAL_PI = M_PI;
const float CEVAL_E = M_E;
#ifndef CEVAL_EPSILON
#define CEVAL_EPSILON 1e-2
#endif
#ifndef CEVAL_DELTA
#define CEVAL_DELTA 1e-6
#endif
#ifndef CEVAL_MAX_DIGITS
#define CEVAL_MAX_DIGITS 15
#endif
//these can be defined by the user before the include directive depending the desired level of precision

//helper function prototypes
void ceval_error(const char * );
double ceval_gcd_binary(int, int);
char * ceval_shrink(char * );

//single argument funtion prototypes
double ceval_signum(double);
double ceval_asin(double);
double ceval_acos(double);
double ceval_atan(double);
double ceval_sin(double);
double ceval_cos(double);
double ceval_tan(double);
double ceval_sinh(double);
double ceval_cosh(double);
double ceval_tanh(double);
double ceval_rad2deg(double);
double ceval_deg2rad(double);
double ceval_int_part(double);
double ceval_frac_part(double);
double ceval_log10(double);
double ceval_ln(double);
double ceval_exp(double);
double ceval_factorial(double);
double ceval_positive_sign(double);
double ceval_negative_sign(double);
double ceval_abs(double);
double ceval_sqrt(double);
double ceval_sqrt(double);
double ceval_cbrt(double);
double ceval_ceil(double);
double ceval_floor(double);

//double argument function prototypes
double ceval_sum(double, double, int);
double ceval_diff(double, double, int);
double ceval_prod(double, double, int);
double ceval_div(double, double, int);
double ceval_quotient(double, double, int);
double ceval_modulus(double, double, int);
double ceval_gcd(double, double, int);
double ceval_hcf(double, double, int);
double ceval_lcm(double, double, int);
double ceval_log(double, double, int);
double ceval_are_equal(double, double, int);
double ceval_not_equal(double, double, int);
double ceval_lesser(double, double, int);
double ceval_greater(double, double, int);
double ceval_lesser_s(double, double, int);
double ceval_greater_s(double, double, int);
double ceval_comma(double, double, int);
double ceval_power(double, double, int);
double ceval_atan2(double, double, int);
double ceval_sci2dec(double, double, int);

//helper function definitions
void ceval_error(const char * error) {
    if (strcmp(error, "")) printf("\n[ceval]: %s\n", error);
}
double ceval_gcd_binary(int a, int b) {
    if (a == 0 && b == 0)
        return 0;
    while (b)
        b ^= a ^= b ^= a %= b;
    return a;
}
char * ceval_shrink(char * x) {
    char * y = x;
    int len = 0;
    for (int i = 0; i < strlen(x); i++) {
        if (x[i] != ' ' || x[i] != '\t') {
            *(y + len) = tolower(x[i]);
            len++;
        } else {
            continue;
        }
    }
    y[len] = '\0';
    return y;
}
//single argument function definitions
double( * single_arg_fun[])(double) = {
    NULL,
    NULL, NULL,
    NULL,
    ceval_positive_sign, ceval_negative_sign, 
    NULL, NULL,
    NULL, NULL, NULL, NULL,
    ceval_abs, NULL, ceval_exp, ceval_sqrt, ceval_cbrt, ceval_ln, ceval_log10, ceval_ceil, ceval_floor, NULL, NULL, NULL, NULL, NULL, NULL, ceval_int_part, ceval_frac_part,
    ceval_factorial,
    ceval_sin, ceval_cos, ceval_tan, ceval_asin, ceval_acos, ceval_atan, ceval_sinh, ceval_cosh, ceval_tanh,
    ceval_deg2rad, ceval_rad2deg, 
    ceval_signum,
    NULL, NULL, NULL, NULL,
    NULL, NULL,
    NULL
};
double ceval_signum(double x) {
    return (x == 0) ? 0 :
        (x > 0) ? 1 :
        -1;
}
double ceval_asin(double x) {
    if (x > 1 || x < -1) {
        ceval_error("Numerical argument out of domain");
        return NAN;
    }
    return asin(x);
}
double ceval_acos(double x) {
    if (x > 1 || x < -1) {
        ceval_error("Numerical argument out of domain");
        return NAN;
    }
    return acos(x);
}
double ceval_atan(double x) {
    return atan(x);
}
double ceval_sin(double x) {
    double sin_val = sin(x);
    //sin(pi) == 0.000000, but sin(pi-CEVAL_EPSILON) == -0.00000* and sin(pi+CEVAL_EPSILON) == +0.00000*
    //since the precision of pi (approx) is limited, it often leads to -0.0000 printed out as a result
    //thus, we assumse 0.0000 value for all |sin(x)|<=CEVAL_EPSILON
    return (fabs(sin_val) <= CEVAL_EPSILON) ? 0 : sin_val;
}
double ceval_cos(double x) {
    double cos_val = cos(x);
    return (fabs(cos_val) <= CEVAL_EPSILON) ? 0 : cos_val;
}
double ceval_tan(double x) {
    double tan_val = tan(x);
    if (fabs(ceval_modulus(x - CEVAL_PI / 2, CEVAL_PI, 0)) <= CEVAL_DELTA) {
        ceval_error("tan() is not defined for odd-integral multiples of pi/2");
        return NAN;
    }
    return (fabs(tan_val) <= CEVAL_EPSILON) ? 0 : tan_val;
}
double ceval_rad2deg(double x) {
    return x / CEVAL_PI * 180;
}
double ceval_deg2rad(double x) {
    return x / 180 * CEVAL_PI;
}
double ceval_int_part(double x) {
    double x_i, x_f;
    x_f = modf(x, & x_i);
    return x_i;
}
double ceval_frac_part(double x) {
    double x_i, x_f;
    x_f = modf(x, & x_i);
    return x_f;
}
double ceval_log10(double x) {
    return ceval_log(10, x, 0);
}
double ceval_ln(double x) {
    return ceval_log(CEVAL_E, x, 0);
}
double ceval_exp(double x) {
    return ceval_power(CEVAL_E, x, 0);
}
double ceval_factorial(double x) {
    if (x < 0) {
        ceval_error("Numerical argument out of domain");
        return NAN;
    }
    return tgamma(x + 1);
}
double ceval_positive_sign(double x) {
    return x;
}
double ceval_negative_sign(double x) {
    return -x;
}
double ceval_abs(double x) {
    return fabs(x);
}
double ceval_sqrt(double x) {
    if (x >= 0) return sqrt(x);
    ceval_error("sqrt(): can't operate on negative numbers");
    return NAN;
}
double ceval_cbrt(double x) {
    return cbrt(x);
}
double ceval_ceil(double x) {
    return ceil(x);
}
double ceval_floor(double x) {
    return floor(x);
}
double ceval_sinh(double x) {
    return sinh(x);
}
double ceval_cosh(double x) {
    return cosh(x);
}
double ceval_tanh(double x) {
    return tanh(x);
}

//double argument function definitions
double( * double_arg_fun[])(double, double, int) = {
    NULL,
    NULL, NULL,
    ceval_comma,
    NULL, NULL,
    ceval_sum, ceval_diff,
    ceval_prod, ceval_div, ceval_modulus, ceval_quotient,
    NULL, ceval_power, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ceval_power, ceval_atan2, ceval_gcd, ceval_hcf, ceval_lcm, ceval_log, NULL, NULL, 
    NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, 
    NULL, 
    ceval_sci2dec,
    ceval_lesser, ceval_greater, ceval_lesser_s, ceval_greater_s,
    ceval_are_equal, ceval_not_equal,
    NULL
};
double ceval_sum(double a, double b, int arg_check) {
    return a + b;
}
double ceval_diff(double a, double b, int arg_check) {
    return a - b;
}
double ceval_prod(double a, double b, int arg_check) {
    return a * b;
}
double ceval_div(double a, double b, int arg_check) {
    if (b == 0 && a == 0) {
        ceval_error("0/0 is indeterminate...");
        ceval_error("Continuing evaluation with the assumption 0/0 = 1");
        return 1;
    } else if (b == 0) {
        ceval_error("Division by 0 is not defined...");
        ceval_error("Continuing evaluation with the assumption 1/0 = inf");
        return a * INFINITY;
    }
    return a / b;
}
double ceval_modulus(double a, double b, int arg_check) {
    if (b == 0) {
        ceval_error("Division by 0 is not defined...");
        ceval_error("Continuing evaluation with the assumption 1%0 = 0");
        return 0;
    }
    return fmod(a, b);
}
double ceval_quotient(double a, double b, int arg_check) {
    //a = b*q + r
    //q = (a - r)/b
    if (b == 0 && a == 0) {
        ceval_error("0/0 is indeterminate...");
        ceval_error("Continuing evaluation with the assumption 0/0 = 1");
        return 1;

    } else if (b == 0) {
        ceval_error("Division by 0 is not defined...");
        ceval_error("Continuing evaluation with the assumption 1/0 = inf");
        return a * INFINITY;
    }
    return (a - ceval_modulus(a, b, 0)) / b;
}
double ceval_gcd(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("gcd(): too few arguments provided");
        return NAN;
    }
    double a_f = ceval_frac_part(a),
        b_f = ceval_frac_part(b);
    int a_i = ceval_int_part(a),
        b_i = ceval_int_part(b);
    if (a_f == 0 && b_f == 0) {
        return (double) ceval_gcd_binary(a_i, b_i);
    } else {
        ceval_error("gcd() takes only integral parameters");
        return NAN;
    }
}
double ceval_hcf(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("hcf(): too few arguments provided");
        return NAN;
    }
    return ceval_gcd(a, b, 0);
}
double ceval_lcm(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("lcm(): too few arguments provided");
        return NAN;
    }
    return a * b / ceval_gcd(a, b, 0);
}
double ceval_log(double b, double x, int arg_check) {
    if (arg_check) {
        ceval_error("log(): too few arguments provided");
        return NAN;
    }
    if (b == 0) {
        if (x == 0) {
            ceval_error("log(0,0) is indeterminate");
            return NAN;
        } else {
            return 0;
        }
    }
    return log(x) / log(b);
}
double ceval_are_equal(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("==: too few arguments provided");
        return NAN;
    }
    if (fabs(a - b) <= CEVAL_EPSILON) {
        return 1;
    } else {
        return 0;
    }
}
double ceval_not_equal(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("!=: too few arguments provided");
        return NAN;
    }
    return !ceval_are_equal(a, b, 0);
}
double ceval_lesser(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("<=: too few arguments provided");
        return NAN;
    }
    return (b - a) >= CEVAL_EPSILON;
}
double ceval_greater(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error(">=: too few arguments provided");
        return NAN;
    }
    return (a - b) >= CEVAL_EPSILON;
}
double ceval_lesser_s(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error("<: too few arguments provided");
        return NAN;
    }
    return !ceval_greater(a, b, 0);
}
double ceval_greater_s(double a, double b, int arg_check) {
    if (arg_check) {
        ceval_error(">: too few arguments provided");
        return NAN;
    }
    return !ceval_lesser(a, b, 0);
}
double ceval_comma(double x, double y, int arg_check) {
    if (arg_check) {
        ceval_error(",: too few arguments provided");
        return NAN;
    }
    return y;
}
double ceval_power(double x, double y, int arg_check) {
    if (arg_check) {
        ceval_error("pow(): too few arguments provided");
        return NAN;
    }
    return pow(x, y);
}
double ceval_atan2(double x, double y, int arg_check) {
    if (arg_check) {
        ceval_error("atan2(): too few arguments provided");
        return NAN;
    }
    return atan2(x, y);
}
double ceval_sci2dec(double m, double e, int arg_check) {
    return (double) m * ceval_power(10, e, 0);
}
#endif