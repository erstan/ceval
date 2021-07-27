#ifndef TOKENS
#define TOKENS

//various types of tokens
typedef enum NodeID {
  WHITESPACE,
  OPENPAR,
  CLOSEPAR, //parentheses
  COMMA, //comma
  POSSIGN,
  NEGSIGN, //positive and negative signs
  PLUS,
  MINUS, //additive operators
  TIMES,
  DIVIDE,
  MODULUS,
  QUOTIENT, //multiplicative operators

  ABS, //absolute
  POW,
  EXP, //exponential operators
  SQRT,
  CBRT, //square and cube roots
  LN,
  LOG, //logarithms
  CEIL,
  FLOOR, //ceil and floor

  POWFUN, //power function
  ATAN2, //polar angle for point (x, y) in cartesian plane = atan2(y,x)

  FACTORIAL, //unary factorial operator
  SIN,
  COS,
  TAN,
  ARCSIN,
  ARCCOS,
  ARCTAN, //trig functions
  SINH,
  COSH,
  TANH, //hyperbolic functions

  LESSER,
  GREATER,
  LESSER_S,
  GREATER_S,
  EQUAL,
  NOTEQUAL, //less than, greater than, strictly less than, strictly greater than
  NUMBER //numbers
}
NodeID;
//their precedences
const double PREC[] = {
  0,
  1,
  1, //parentheses
  1.5, //comma operator
  3,
  3, //positive and negative signs
  2,
  2, //additive operators
  4,
  4,
  4,
  4, //multiplicative operators

  5, //absolute value
  5,
  5, //exponential operator
  5,
  5, //square and cube roots
  5,
  5, //logarithms
  5,
  5, //ceil and floor

  5, //power function
  5, //atan2()

  6, //factorial
  7,
  7,
  7,
  7,
  7,
  7, //trig functions
  7,
  7,
  7, //hyperbolic functions

  1.2,
  1.2,
  1.2,
  1.2,
  1.1,
  1.1, //relational operations are performed at the end
  10 //numbers
};
//only for single char tokens
NodeID TOKEN_ID(char token) {
  switch (token) {
  case '(':
    return OPENPAR;
  case ')':
    return CLOSEPAR;
  case '+':
    return PLUS;
  case '-':
    return MINUS;
  case '*':
    return TIMES;
  case '/':
    return DIVIDE;
  case '%':
    return MODULUS;
  case '\\':
    return QUOTIENT;
  case '^':
    return POW;
  case '!':
    return FACTORIAL;
  case ',':
    return COMMA;
  case '<':
    return LESSER_S;
  case '>':
    return GREATER_S;
  default:
    if ('0' <= token && token <= '9') return NUMBER;
    else if (token == ' ' || token == '\t' || token == '\r' || token == '\n') return WHITESPACE;
  }
  return OPENPAR;
}
typedef struct _Node {
  enum NodeID ID;
  double pre;
  double number; //only to be used if this.ID == NUMBER
  struct _Node * left, * right, * parent;
}
Node;
#ifdef __cplusplus
  #define CXX
  #include<iostream>
  #include<string>
#endif
#endif
