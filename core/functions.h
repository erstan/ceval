#ifndef FUNCTIONS
#define FUNCTIONS
#include "./tokens.h"
#include<stdio.h>
#include<math.h>
const float CONST_PI = M_PI;
const float CONST_E = M_E;
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
  while (1) {
    if (a < b) {
      return a;
    }
    a = a - b;
  }
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
int are_equal(double a, double b) {
  if (fabs(a - b) <= 0.0001) {
    return 1;
  } else {
    return 0;
  }
}
void ceval_input(char * x) {
  for (char ch = getchar(); ch != '\n'; ch = getchar()) {
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\b') {
      continue;
    }
    * x++ = ch;
  }
  * x = '\0';
}

#include<string.h>
#include<ctype.h>

char * ceval_shrink(char * x) {
  char * y = x;
  int len = 0;
  for (int i = 0; i < strlen(x); i++) {
    if (x[i] != ' ' || x[i] != '\t') {
      *(y + len) = x[i];
      len++;
    } else {
      continue;
    }
  }
  y[len] = '\0';
  return y;
}
#ifdef CXX
void ceval_input(std::string & x) {
  char char_array[100];
  ceval_input(char_array);
  x = char_array;
}
#endif

#endif
