#ifndef CEVAL_EVALUATOR
#define CEVAL_EVALUATOR
#include "./tokens.h"
#include "./functions.h"

double ceval_evaluate_tree_(const ceval_node *);
double ceval_evaluate_tree(const void *);

double ceval_evaluate_tree_(const ceval_node * node) {
  if (!node) return 0;
  double left, right;
  left = ceval_evaluate_tree_(node -> left);
  right = ceval_evaluate_tree_(node -> right);
  switch (node -> id) {
  
  //unary operators/functions
  case CEVAL_NEGSIGN: case CEVAL_POSSIGN:
  case CEVAL_EXP: case CEVAL_LN: case CEVAL_LOG10:
  case CEVAL_ABS: case CEVAL_CEIL: case CEVAL_FLOOR:
  case CEVAL_SQRT: case CEVAL_CBRT:
  case CEVAL_SIN: case CEVAL_COS: case CEVAL_TAN: 
  case CEVAL_ASIN: case CEVAL_ACOS: case CEVAL_ATAN:
  case CEVAL_SINH: case CEVAL_COSH: case CEVAL_TANH:
  case CEVAL_DEG2RAD: case CEVAL_RAD2DEG:
  case CEVAL_SIGNUM: case CEVAL_INT: case CEVAL_FRAC: case CEVAL_FACTORIAL:
    if(node->left == NULL) {
      //operate on right operand
      return (*single_arg_fun[node->id])(right);
    } else if(node->right == NULL) { 
      //operate on left operand(e.g; factorial())
      return (*single_arg_fun[node->id])(left);
    }
  
  //binary operators/functions
  case CEVAL_PLUS: case CEVAL_MINUS:
  case CEVAL_TIMES: case CEVAL_DIVIDE: case CEVAL_MODULO: case CEVAL_QUOTIENT:
  case CEVAL_POW: case CEVAL_POWFUN:
  case CEVAL_ATAN2: case CEVAL_GCD: case CEVAL_HCF: case CEVAL_LCM: case CEVAL_LOG:
  case CEVAL_LESSER: case CEVAL_LESSER_S: case CEVAL_GREATER: case CEVAL_GREATER_S:
  case CEVAL_EQUAL: case CEVAL_NOTEQUAL:
  case CEVAL_COMMA:
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
  return ceval_evaluate_tree_((ceval_node * ) node);
}
#endif
