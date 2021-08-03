#ifndef TOKENS
#define TOKENS

typedef enum ceval_node_id {
  WHITESPACE,
  OPENPAR, CLOSEPAR,
  COMMA,
  POSSIGN, NEGSIGN,
  PLUS, MINUS, 
  TIMES, DIVIDE, MODULUS, QUOTIENT,
  ABS, POW, EXP, SQRT, CBRT, LN, LOG10, CEIL, FLOOR, POWFUN, ATAN2, GCD, HCF, LCM, LOG, INT, FRAC,
  FACTORIAL,
  SIN, COS, TAN, ARCSIN, ARCCOS, ARCTAN, SINH, COSH, TANH,
  DEG2RAD, RAD2DEG,
  SIGNUM,
  LESSER, GREATER, LESSER_S, GREATER_S,
  EQUAL, NOTEQUAL,
  NUMBER
}ceval_node_id;
const char * ceval_token_symbol[] = {
  " ",
  "(", ")",
  ",",
  "+", "-",
  "+", "-",
  "*", "/", "%", "\\",
  "abs", "^", "exp", "sqrt", "cbrt", "ln", "log10", "ceil", "floor", "pow", "atan2", "gcd", "hcf", "lcm", "log", "int", "frac",
  "!",
  "sin", "cos", "tan", "asin", "acos", "atan", "sinh", "cosh", "tanh",
  "deg2rad", "rad2deg", 
  "SIGNUM",
  "<=", ">=", "<", ">", 
  "==", "!=",
  " "
};
const double ceval_precedence[] = {
  0,
  1, 1,
  1.5,
  3, 3, 
  2, 2, 
  4, 4, 4, 4, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6,
  7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7,
  7,
  1.2, 1.2, 1.2, 1.2,
  1.1, 1.1,
  10
};
ceval_node_id TOKEN_ID(char token) {
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
typedef struct _ceval_node {
  enum ceval_node_id id;
  double pre;
  double number;
  struct _ceval_node * left, * right, * parent;
}
ceval_node;
#ifdef __cplusplus
  #define CXX
  #include<iostream>
  #include<string>
#endif
#endif
