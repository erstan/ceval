#ifndef FUNCTIONS
#define FUNCTIONS

#include "./tokens.h"

#include<stdio.h>

#include<math.h>

const float CONST_PI = M_PI;
const float CONST_E = M_E;
#ifndef EPSILON
  #define EPSILON 1e-2
#endif
#ifndef DELTA
  #define DELTA 1e-6
#endif
//these can be defined by the user before the include directive depending the desired level of precision


double ceval_signum(double x) {
  return (x==0)?0:
          (x>0)?1:
          -1;
}
double ceval_sum(double a, double b) {
  return a + b;
}
double ceval_diff(double a, double b) {
  return a - b;
}
double ceval_prod(double a, double b) {
  return a * b;
}
double ceval_div(double a, double b) {
  if (b == 0 && a == 0) {
    printf("[PARSER]: 0/0 is indeterminate...\n");
    printf("[PARSER]: Continuing evaluation with the assumption 0/0 = 1\n");
    return 1;
  } else if (b == 0) {
    printf("[PARSER]: Division by 0 is not defined...\n");
    printf("[PARSER]: Continuing evaluation with the assumption 1/0 = inf\n");
    return a * INFINITY;
  }
  return a / b;
}
double ceval_factorial(double x) {
  return tgamma(x + 1);
}
double ceval_modulus(double a, double b) {
  if (b == 0) {
    printf("[PARSER]: Division by 0 is not defined...\n");
    printf("[PARSER]: Continuing evaluation with the assumption 1%0 = 0\n");
    return 0;
  }
  return fmod(a, b);
}
double ceval_quotient(double a, double b) {
  //a = b*q + r
  //q = (a - r)/b
  if (b == 0 && a == 0) {
    printf("[PARSER]: 0/0 is indeterminate...\n");
    printf("[PARSER]: Continuing evaluation with the assumption 0/0 = 1\n");
    return 1;

  } else if (b == 0) {
    printf("[PARSER]: Division by 0 is not defined...\n");
    printf("[PARSER]: Continuing evaluation with the assumption 1/0 = inf\n");
    return a * INFINITY;
  }
  return (a - ceval_modulus(a, b)) / b;
}
double ceval_asin(double x) {
  if (x > 1 || x < -1) {
    printf("[PARSER]: Numerical argument out of domain\n");
    return 0;
  }
  return asin(x);
}
double ceval_acos(double x) {
  if (x > 1 || x < -1) {
    printf("[PARSER]: Numerical argument out of domain\n");
    return 0;
  }
  return acos(x);
}
double ceval_atan(double x) {
  return atan(x);
}
double ceval_sin(double x) {
  double sin_val = sin(x);
  //sin(pi) == 0.000000, but sin(pi-EPSILON) == -0.00000* and sin(pi+EPSILON) == +0.00000*
  //since the precision of pi (approx) is limited, it often leads to -0.0000 printed out as a result
  //thus, we assumse 0.0000 value for all |sin(x)|<=EPSILON
  return (fabs(sin_val) <= EPSILON) ? 0 : sin_val;
}
double ceval_cos(double x) {
  double cos_val = cos(x);
  return (fabs(cos_val) <= EPSILON) ? 0 : cos_val;
}
double ceval_tan(double x) {
  double tan_val = tan(x);
  if(abs(ceval_modulus(x - CONST_PI/2, CONST_PI)) <= DELTA) {
    printf("tan() is not defined for odd-integral multiples of pi/2\n");
    return NAN;
  }
  return (fabs(tan_val) <= EPSILON) ? 0 : tan_val;
}
double ceval_rad2deg(double x) {
  return x / CONST_PI * 180;
}
double ceval_deg2rad(double x) {
  return x / 180 * CONST_PI;
}
int ceval_are_equal(double a, double b) {
  if (fabs(a - b) <= EPSILON) {
    return 1;
  } else {
    return 0;
  }
}
#include<string.h>
#include<ctype.h>
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
#endif