#ifndef CEVAL_TOKENS
#define CEVAL_TOKENS

typedef enum ceval_node_id {
  CEVAL_WHITESPACE,
  CEVAL_OPENPAR, CEVAL_CLOSEPAR,
  CEVAL_COMMA,
  CEVAL_POSSIGN, CEVAL_NEGSIGN,
  CEVAL_PLUS, CEVAL_MINUS, 
  CEVAL_TIMES, CEVAL_DIVIDE, CEVAL_MODULO, CEVAL_QUOTIENT,
  CEVAL_ABS, CEVAL_POW, CEVAL_EXP, CEVAL_SQRT, CEVAL_CBRT, CEVAL_LN, CEVAL_LOG10, CEVAL_CEIL, CEVAL_FLOOR, CEVAL_POWFUN, CEVAL_ATAN2, CEVAL_GCD, CEVAL_HCF, CEVAL_LCM, CEVAL_LOG, CEVAL_INT, CEVAL_FRAC,
  CEVAL_FACTORIAL,
  CEVAL_SIN, CEVAL_COS, CEVAL_TAN, CEVAL_ASIN, CEVAL_ACOS, CEVAL_ATAN, CEVAL_SINH, CEVAL_COSH, CEVAL_TANH,
  CEVAL_DEG2RAD, CEVAL_RAD2DEG,
  CEVAL_SIGNUM,
  CEVAL_SCI2DEC,
  CEVAL_LESSER, CEVAL_GREATER, CEVAL_LESSER_S, CEVAL_GREATER_S,
  CEVAL_EQUAL, CEVAL_NOTEQUAL,
  CEVAL_NUMBER
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
  "signum",
  "e",
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
  9,
  1.2, 1.2, 1.2, 1.2,
  1.1, 1.1,
  10
};
ceval_node_id ceval_singlechar_token_id(char token) {
  switch (token) {
  case '(':
    return CEVAL_OPENPAR;
  case ')':
    return CEVAL_CLOSEPAR;
  case '+':
    return CEVAL_PLUS;
  case '-':
    return CEVAL_MINUS;
  case '*':
    return CEVAL_TIMES;
  case '/':
    return CEVAL_DIVIDE;
  case '%':
    return CEVAL_MODULO;
  case '\\':
    return CEVAL_QUOTIENT;
  case '^':
    return CEVAL_POW;
  case '!':
    return CEVAL_FACTORIAL;
  case ',':
    return CEVAL_COMMA;
  case '<':
    return CEVAL_LESSER_S;
  case '>':
    return CEVAL_GREATER_S;
  default:
    if ('0' <= token && token <= '9') return CEVAL_NUMBER;
    else if (token == ' ' || token == '\t' || token == '\r' || token == '\n') return CEVAL_WHITESPACE;
  }
  return CEVAL_OPENPAR;
}
typedef struct ceval_node {
  enum ceval_node_id id;
  double pre;
  double number;
  struct ceval_node * left, * right, * parent;
} ceval_node;
#ifdef __cplusplus
  #define CEVAL_CXX
  #include<iostream>
  #include<string>
#endif
#endif
