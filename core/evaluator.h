#ifndef CEVAL_EVALUATOR
#define CEVAL_EVALUATOR

#include "./tokens.h"
#include "./functions.h"

double ceval_evaluate_tree_(const ceval_node * );
double ceval_evaluate_tree(const void * );

double ceval_evaluate_tree_(const ceval_node * node) {
    if (!node) 
        return 0;
    
    double left, right;
    left = ceval_evaluate_tree_(node -> left);
    right = ceval_evaluate_tree_(node -> right);
    switch (node -> id) {

        //unary-right operators/functions (operate on the expression to their right)
        case CEVAL_ABS: case CEVAL_EXP: case CEVAL_SQRT: case CEVAL_CBRT: 
        case CEVAL_LN: case CEVAL_LOG10: case CEVAL_CEIL: case CEVAL_FLOOR: 
        case CEVAL_SIGNUM: case CEVAL_FACTORIAL: case CEVAL_INT: case CEVAL_FRAC: 
        case CEVAL_DEG2RAD: case CEVAL_RAD2DEG: case CEVAL_SIN: case CEVAL_COS: 
        case CEVAL_TAN: case CEVAL_ASIN: case CEVAL_ACOS: case CEVAL_ATAN: 
        case CEVAL_SINH: case CEVAL_COSH: case CEVAL_TANH: case CEVAL_NOT: 
        case CEVAL_BIT_NOT: case CEVAL_POSSIGN: case CEVAL_NEGSIGN: 
            if (node -> right != NULL) {
                //operate on right operand
                return ( * single_arg_fun[node -> id])(right);
            } else {
                ceval_error("Missing operand(s)");
                return NAN;
            }
        //binary operators/functions
        case CEVAL_COMMA:  
        case CEVAL_OR:  case CEVAL_AND:  case CEVAL_BIT_OR:  case CEVAL_BIT_XOR: 
        case CEVAL_BIT_AND:  case CEVAL_EQUAL:  case CEVAL_NOTEQUAL: case CEVAL_LESSER: 
        case CEVAL_GREATER:  case CEVAL_LESSER_S:  case CEVAL_GREATER_S:  case CEVAL_BIT_LSHIFT:  
        case CEVAL_BIT_RSHIFT:  case CEVAL_PLUS:  case CEVAL_MINUS:  case CEVAL_TIMES:  
        case CEVAL_DIVIDE:  case CEVAL_MODULO:  case CEVAL_QUOTIENT:  case CEVAL_POW: 
        case CEVAL_GCD:  case CEVAL_HCF:  case CEVAL_LCM:  case CEVAL_LOG: 
        case CEVAL_ATAN2:  case CEVAL_SCI2DEC: case CEVAL_POWFUN:
            if (node -> left == NULL) {
                return ( * double_arg_fun[node -> id])(left, right, -1);
            } else if (node -> right == NULL) {
                return ( * double_arg_fun[node -> id])(left, right, 1);
            } else {
                return ( * double_arg_fun[node -> id])(left, right, 0);
            }
            default:
                return node -> number;
    }
}
double ceval_evaluate_tree(const void * node) {
    return (node == NULL)? NAN :
            ceval_evaluate_tree_((ceval_node * ) node);
}
#endif