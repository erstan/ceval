#ifndef BET_EVAL
#define BET_EVAL
#include "./tokens.h"
#include "./functions.h"
double _ceval_evaluate_tree(const ceval_node * node) {
  if (!node) return 0;
  double left, right;
  left = _ceval_evaluate_tree(node -> left);
  right = _ceval_evaluate_tree(node -> right);
  switch (node -> id) {
  case PLUS:
    return ceval_sum(left, right);
  case MINUS:
    return ceval_diff(left, right);
  case NEGSIGN:
    return -right;
  case POSSIGN:
    return right;
  case TIMES:
    return ceval_prod(left, right);
  case DIVIDE:
    return ceval_div(left, right);
  case MODULUS:
    return ceval_modulus(left, right);
  case QUOTIENT:
    return ceval_quotient(left, right);
  case POW:
    return pow(left, right);
  case FACTORIAL:
    return ceval_factorial(left);
  case ABS:
    return fabs(right);
  case CEIL:
    return ceil(right);
  case FLOOR:
    return floor(right);
  case EXP:
    return pow(CONST_E, right);
  case POWFUN:
    return pow(left, right);
  case ATAN2:
    return atan2(left, right);
  case SQRT:
    return sqrt(right);
  case CBRT:
    return cbrt(right);
  case LN:
    return log(right);
  case LOG:
    return log10(right);
  case SINH:
    return sinh(right);
  case COSH:
    return cosh(right);
  case TANH:
    return tanh(right);
  case SIN:
    return sin(right);
  case COS:
    return cos(right);
  case TAN:
    return tan(right);
  case ARCSIN:
    return ceval_asin(right);
  case ARCCOS:
    return ceval_acos(right);
  case ARCTAN:
    return ceval_atan(right);
  case COMMA:
    return right;
  case LESSER:
    return left <= right;
  case GREATER:
    return left >= right;
  case LESSER_S:
    return left < right;
  case GREATER_S:
    return left > right;
  case EQUAL:
    return are_equal(left, right);
  case NOTEQUAL:
    return !are_equal(left, right);
  default:
    return node -> number;
  }
}
double ceval_evaluate_tree(const void * node) {
  return _ceval_evaluate_tree((ceval_node * ) node);
}
#endif
