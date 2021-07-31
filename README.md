# ceval
A C/C++ header for parsing and evaluation of arithmetic expressions.

# Usage
* `ceval_result()` takes in an arithmetic expression as argument and returns the result as a `double`. The argument could be a character array terminated by `\0` or a CPP string. 
* `ceval_tree()` takes in the arithmetic expression as argument and prints out it's parse tree on the console. 

Following is an interactive console based interpreter that interactively takes in math expressions from stdin, and prints out their parse trees and results. 

```
//lang=c
#include<stdio.h>
#include<stdlib.h>

#include "ceval.h"

int main(int argc, char ** argv) {
  char expr[100];
  while (1) {
    printf("In = ");
    scanf("%s", expr);
    if (!strcmp(expr, "exit")) {
      break;
    } else if (!strcmp(expr, "clear")) {
      system("clear");
      continue;
    } else {
      ceval_tree(expr);
      printf("\nOut = %f\n\n", ceval_result(expr));
    }
  }
  return 0;
}
```
