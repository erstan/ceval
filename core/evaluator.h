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
  
  //unary operators/functions
  case NEGSIGN: case POSSIGN:
  case EXP: case LN: case LOG10:
  case ABS: case CEIL: case FLOOR:
  case SQRT: case CBRT:
  case SIN: case COS: case TAN: 
  case ARCSIN: case ARCCOS: case ARCTAN:
  case SINH: case COSH: case TANH:
  case DEG2RAD: case RAD2DEG:
  case SIGNUM: case INT: case FRAC: case FACTORIAL:
    if(node->left == NULL) {
      //operate on right operand
      return (*single_arg_fun[node->id])(right);
    } else if(node->right == NULL) { 
      //operate on left operand(e.g; factorial())
      return (*single_arg_fun[node->id])(left);
    }
  
  //binary operators/functions
  case PLUS: case MINUS:
  case TIMES: case DIVIDE: case MODULUS: case QUOTIENT:
  case POW: case POWFUN:
  case ATAN2: case GCD: case HCF: case LCM: case LOG:
  case LESSER: case LESSER_S: case GREATER: case GREATER_S:
  case EQUAL: case NOTEQUAL:
  case COMMA:
    if(node->left == NULL) {
      return (*double_arg_fun[node->id])(left, right, -1);
    } else if (node->right == NULL) {
      return (*double_arg_fun[node->id])(left, right, 1);
    } else {
      return (*double_arg_fun[node->id])(left, right, 0);
    }
  default:
    return node -> number;
  }
}
double ceval_evaluate_tree(const void * node) {
  return _ceval_evaluate_tree((ceval_node * ) node);
}
#endif
