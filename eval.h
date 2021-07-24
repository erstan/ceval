/*
 *      - Addition(+), Subtraction(-), Multiplication(*), Division(/), Modulus(%), Quotient(\), Exponentiation(^) and Factorial(!)
 *        operations are supported for positive integers and floating point numbers
 *      - Relational operators are also supported: `==`, `!=`, `<`, `>`, `<=`, `>=`
 *      - Functions supported - `exp()`, `sqrt()`, `cbrt()`, `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`, `sinh()`, `cosh()`, `tanh()`, `abs()`, `ceil()`, `floor`, `log()`, `ln()`
 *      - Two argument functions like `pow()`, `atan2()` [atan2(y,x) == arg(x+iy)]
 *      - Pre-defined mathematical constants - `PI`, `E`
 *      - Parentheses can be used to override the operation precedences
 *      - evaluateCString(char * cString) returns the final result of a valid mathematical expression
 *        `cString` 
 *      - makeET(char * cString) returns the void pointer to the root node of the Expression Tree
 *        corresponding the mathematical expression `cString`
 *      - printET(void * tree) prints the ET with root node address `tree`
 *      - evaluateET(void * tree) returns the final result of the operations in the Expression Tree
 *        with root node address `tree`
 *      - deleteET(void * tree) frees the memory alloted to the program for storing the ET
 */
#ifndef EVAL
#define EVAL
#include "./core/parser.h"
#include "./core/bet-eval.h"

double eval(char * expr) {
  void * tree = makeET(expr);
  double result = evaluateET(tree);
  deleteET(tree);
  return result;
}
#ifdef CXX
  #include<iostream>
  #include<cstring>
  double eval(std::string expr){
    return eval((char *)expr.c_str());
  }
#endif
#endif
