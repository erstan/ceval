#ifndef FUNCTIONS
#define FUNCTIONS

#include<math.h>
//pre-defined mathematical constants
const float CONST_PI = M_PI;
const float CONST_E = M_E;

//user-defined math functions and wrappers on cmath library functions
double sum(double a, double b) {
    return a + b;
}
double diff(double a, double b) {
    return a - b;
}
double prod(double a, double b) {
    return a * b;
}
double div(double a, double b) {
    return a / b;
}
double factorial(double x) {
    return tgamma(x+1);
}
double modulus(double a, double b) {
  //modulus will be in the range [0, b)
  //it can be found by repeatedly subtracting `b` from `a` until we get a result in that range
  while (1) {
    if (a < b) {
      return a;
    }
    a = a - b;
  }
}
double quotient(double a, double b) {
  //a = b*q + r
  //q = (a - r)/b
  return (a - modulus(a, b)) / b;
}
int areEqual(double a, double b) {
    if(fabs(a-b)!=0.0001) {
        return 1;
    } else {
        return 0;
    }
}
#endif