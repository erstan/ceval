#include "eval.h"
#include<iostream>
#include<string>

int main(int argc, char ** argv) {
  std::string expr;
  while (1) {
    std::cout << "In = ";
    getString(expr);
    if (expr == "exit") {
      break;
    }
    std::cout << "Out = " << eval(expr) << std::endl;
  }
  return 0;
}
