# ceval
A C/C++ library for evaluation of math expressions and breaking them down into parse trees

## Functions accessibe from main()
<table>
<thead><th>Function</th><th>Argument(s)</th><th>Return Value</th></thead>
<tbody>
<tr>
  <td><code>makeET()</code></td>
  <td>A mathematical expression in the form of a character array or a CPP string</td>
  <td>Returns a void pointer containing the root node address of the parse tree representing the expression</td>
</tr>
<tr>
  <td><code>printET()</code></td>
  <td>The pointer to the root node of the binary expression tree</td>
  <td>The function prints the parse tree with each node properly indented depending on it's location in the tree structure</td>
</tr>
<tr>
  <td><code>evaluateET()</code></td>
  <td>Void pointer to the root node of the parse tree</td>
  <td>The result of the math expression that is represented by the parse tree</td>
</tr>
<tr>
  <td><code>deleteET()</code></td>
  <td>The pointer containing the root node address of the expression tree</td>
  <td>Recursively frees the memory occupied by each node of the expression tree</td>
</tr>
</tbody>
</table>

## Supported expressions
Any valid combination of the following operators and functions, with floating point numbers as operands can be parsed by <b>ceval</b>. Parenthesis can be used to override the default operator precedences. 

* Arithematic operators

`+` (addition), `-` (subtraction), `*` (multiplication), `/` (division), `%` (modulo), `^` (exponentiation), `\` (quotient), `!` (factorial)
* Relational operators

`==`, `!=`, `<`, `>`, `<=`, `>=` to compare the results of two expressions

* Single-argument functions

`exp()`, `sqrt()`, `cbrt()`, `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`, `sinh()`, `cosh()`, `tanh()`, `abs()`, `ceil()`, `floor`, `log()`, `ln()`

* Two-argument functions

`pow()`, `atan2()`

* Pre-defined math constants

`PI`, `E`

* The `,` operator

The comma `,` operator is also implemented. It returns the value of it's right-most operand. 

e.g; `2,3` would give `3`; `4,3,0` would be equal to `0`; and `cos(PI/2,PI/3,PI)` would return `cos(PI)` i.e, `-1`



## Usage

Include the path to `eval.h`in your C/C++ file and you are good to go. No cross-compilation required. 

The code snippets given below offer a simple demo of how the `eval()` function can be used to evaluate the result of a math expression taken from stdin. 

```
//lang=c
#include<stdio.h>
#include "eval.h"
int main (int argc, char** argv) {
        char exp[100];
        printf("Enter the expression\n");
        scanf("%s", exp);
        printf("%f\n", eval(exp)); //exp is a char array
return 0;
}
```

```
//lang=cpp
#include "eval.h"
#include<iostream>
#include<string>

int main(int argc, char ** argv) {
  std::string expr;
  std::cout << "Enter the expression\n";
  std::cin >> expr;
  std::cout << "Result = " << eval(expr) << "\n"; //expr is cxx string
return 0;
}
  
```
