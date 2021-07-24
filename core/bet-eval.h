//BINARY EXPRESSION TREE EVALUATOR
//evaluateET(void *) returns the result of an expression from it's parse tree
#ifndef BET_EVAL
#define BET_EVAL
#include "./tokens.h"
#include "./functions.h"
double _evaluateET(const Node * node) {
  if (!node) return 0;
  double left, right;
  left = _evaluateET(node -> left);
  right = _evaluateET(node -> right);
  switch (node -> ID) {
  case PLUS:
    return sum(left, right);
  case MINUS:
    return diff(left, right);
  case NEGSIGN:
    return -right;
  case POSSIGN:
    return right;
  case TIMES:
    return prod(left, right);
  case DIVIDE:
    return div(left, right);
  case MODULUS:
    return modulus(left, right);
  case QUOTIENT:
    return quotient(left, right);
  case POW:
    return pow(left, right); //from math.h
  case FACTORIAL:
    return factorial(left); //true_gamma(x+1) == factorial(x)
  case ABS:
    return fabs(right);
  case CEIL:
    return ceil(right);
  case FLOOR:
    return floor(right);
  case EXP:
    return pow(CONST_E, right); //M_E == euler number
  case POWFUN:
    return pow(left, right);
    /*                                /  
                                     |   atan(y/x)   ; x>=0
                                     |   
                        atan2(y,x) = |   pi + atan(y/x)   ; x<0 && y>=0
                                     |   
                                     |   -pi + atan(y/x)   ; x<0 && y<0
                                      \
    */
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
    return asin(right);
  case ARCCOS:
    return acos(right);
  case ARCTAN:
    return atan(right);
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
    return areEqual(left, right);
  case NOTEQUAL:
    return !areEqual(left, right);
  default:
    return node -> number;
  }
}
//argument is of type `void`, so the main code doesn't depend on Node type
double evaluateET(const void * node) {
  return _evaluateET((Node * ) node);
}
#endif
