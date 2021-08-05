#ifndef CEVAL_TOKENS
#define CEVAL_TOKENS
#include<string.h>
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
typedef struct ceval_token_info_ {
  ceval_node_id id;
  const char * symbol; 
  double prec;
} ceval_token_info_; 
ceval_token_info_ ceval_token_info[] = {
  { CEVAL_WHITESPACE, " ", 0 },
  { CEVAL_WHITESPACE, "\n", 0 },
  { CEVAL_WHITESPACE, "\t", 0 },
  { CEVAL_WHITESPACE, "\r", 0 },
  { CEVAL_WHITESPACE, "\b", 0 },
  { CEVAL_OPENPAR, "(", 1 },
  { CEVAL_CLOSEPAR, ")", 1 },
  { CEVAL_COMMA, ",", 1.5 },
  { CEVAL_POSSIGN, "+", 3 },
  { CEVAL_NEGSIGN, "-", 3 },
  { CEVAL_PLUS, "+", 2 },
  { CEVAL_MINUS, "-", 2 },
  { CEVAL_TIMES, "*", 4 },
  { CEVAL_DIVIDE, "/", 4 },
  { CEVAL_MODULO, "%", 4 },
  { CEVAL_QUOTIENT, "\\", 4 },
  { CEVAL_ABS, "abs", 5 },
  { CEVAL_POW, "^", 5 },
  { CEVAL_EXP, "exp", 5 },
  { CEVAL_SQRT, "sqrt", 5 },
  { CEVAL_CBRT, "cbrt", 5 },
  { CEVAL_LN, "ln", 5 },
  { CEVAL_LOG10, "log10", 5 },
  { CEVAL_CEIL, "ceil", 5 },
  { CEVAL_FLOOR, "floor", 5 },
  { CEVAL_POWFUN, "pow", 5 },
  { CEVAL_ATAN2, "atan2", 5 },
  { CEVAL_GCD, "gcd", 5 },
  { CEVAL_HCF, "hcf", 5 },
  { CEVAL_LCM, "lcm", 5 },
  { CEVAL_LOG, "log", 5 },
  { CEVAL_INT, "int", 5 },
  { CEVAL_FRAC, "frac", 5 },
  { CEVAL_FACTORIAL, "!", 6 },
  { CEVAL_SIN, "sin", 7 },
  { CEVAL_COS, "cos", 7 },
  { CEVAL_TAN, "tan", 7 }, 
  { CEVAL_ASIN, "asin", 7 }, 
  { CEVAL_ACOS, "acos", 7 },
  { CEVAL_ATAN, "atan", 7 },
  { CEVAL_SINH, "sinh", 7 },
  { CEVAL_COSH, "cosh", 7 },
  { CEVAL_TANH, "tanh", 7 },
  { CEVAL_DEG2RAD, "deg2rad", 7 },
  { CEVAL_RAD2DEG, "rad2deg", 7 },
  { CEVAL_SIGNUM, "signum", 7 },
  { CEVAL_SCI2DEC, "e", 9 },
  { CEVAL_LESSER, "<=", 1.2 },
  { CEVAL_GREATER, ">=", 1.2 },
  { CEVAL_LESSER_S, "<", 1.2 },
  { CEVAL_GREATER_S, ">", 1.2 },
  { CEVAL_EQUAL, "==", 1.1 },
  { CEVAL_NOTEQUAL, "!=", 1.1 },
  { CEVAL_NUMBER, "0", 10 },
  { CEVAL_NUMBER, "1", 10 },
  { CEVAL_NUMBER, "2", 10 },
  { CEVAL_NUMBER, "3", 10 },
  { CEVAL_NUMBER, "4", 10 },
  { CEVAL_NUMBER, "5", 10 },
  { CEVAL_NUMBER, "6", 10 },
  { CEVAL_NUMBER, "7", 10 },
  { CEVAL_NUMBER, "8", 10 },
  { CEVAL_NUMBER, "9", 10 },
}; 
const char * ceval_token_symbol(ceval_node_id id) {
  for(int i = 0; i < 63; i++) {
    if(id==ceval_token_info[i].id) {
      return ceval_token_info[i].symbol;
    }
  }
}
ceval_node_id ceval_token_id(char * symbol) {
  for(int i = 0; i < 63; i++) {
    if(!strcmp(ceval_token_info[i].symbol, symbol)) {
      return ceval_token_info[i].id;
    }
  }
}
double ceval_token_prec(ceval_node_id id) {
  for(int i = 0; i < 63; i++) {
    if(id==ceval_token_info[i].id) {
      return ceval_token_info[i].prec; 
    }
  }
}
ceval_node_id ceval_singlechar_token_id(char token) {
  char temp[2] = "\0";
  temp[0] = token;
  return ceval_token_id(temp);
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
