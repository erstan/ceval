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
## Test Run
```
In = 3*7^2
                2
        ^
                7
*
        3

Out = 147.000000


In = (3.2+2.8)/2
        2
/
                2.80
        +
                3.20

Out = 3.000000


In = E^PI>PI^E
                2.72
        ^
                3.14
>
                3.14
        ^
                2.72

Out = 1.000000


In = 5.4%2
        2
%
        5.40

Out = 1.400000


In = 5.4\2
        2
\
        5.40

Out = 2.000000


In = 2*2.0+1.4
        1.40
+
                2
        *
                2

Out = 5.400000


In = (5/4+3*-5)+(sin(PI))^2+(cos(PI))^2
                2
        ^
                        3.14
                cos
+
                        2
                ^
                                3.14
                        sin
        +
                                        5
                                -
                        *
                                3
                +
                                4
                        /
                                5

Out = -12.750000


In = exit
... Program finished with exit code 0

```
