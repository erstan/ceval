#ifndef BET_PARSER
#define BET_PARSER
#include "./tokens.h"

#include "./functions.h"

#include<stdio.h>
#include<malloc.h>
#include<string.h>

void delete_node(ceval_node * node) {
  if (!node) return;
  delete_node(node -> left);
  delete_node(node -> right);
  free(node);
}
void ceval_delete_tree(void * tree) {
  delete_node((ceval_node * ) tree);
}
ceval_node * insert_node(ceval_node * current, ceval_node item, int isRightAssoc) {
  if (item.id != OPENPAR &&
    item.id != NEGSIGN &&
    item.id != POSSIGN) {
    if (isRightAssoc) {
      while (current -> pre > item.pre) {
        current = current -> parent;
      }
    } else {
      while (current -> pre >= item.pre) {
        current = current -> parent;
      }
    }
  }
  if (item.id == CLOSEPAR) { 
    ceval_node * parent_of_openpar = current -> parent;
    parent_of_openpar -> right = current -> right;
    if (current -> right) current -> right -> parent = parent_of_openpar;
    free(current);
    current = parent_of_openpar;

    if (current -> right -> id == COMMA && 
       (current -> id == POWFUN || current -> id == ATAN2 || 
        current -> id == GCD || current -> id == HCF || current -> id == LCM ||
        current -> id == LOG)) {
      ceval_node * address_of_comma = current -> right;
      parent_of_openpar -> left = address_of_comma -> left;
      address_of_comma -> left -> parent = parent_of_openpar;
      parent_of_openpar -> right = address_of_comma -> right;
      address_of_comma -> right -> parent = parent_of_openpar;
      free(address_of_comma);
    }
    return current;
  }
  ceval_node * newnode = (ceval_node * ) malloc(sizeof(ceval_node));
  * newnode = item;
  newnode -> right = NULL;

  newnode -> left = current -> right;
  if (current -> right) current -> right -> parent = newnode;
  current -> right = newnode;
  newnode -> parent = current;
  current = newnode;
  return current;
}

void * ceval_make_tree(char * expression) {
  if (expression == NULL) return NULL;
  strcpy(expression, ceval_shrink(expression));
  ceval_node root = {
    OPENPAR,
    ceval_precedence[OPENPAR],
    0,
    NULL,
    NULL,
    NULL
  };
  ceval_node_id previous_id = OPENPAR;
  ceval_node * current = & root;
  int isRightAssoc = 0;
  while (1) {
    ceval_node node;
    char c = * expression++; 
    isRightAssoc = (c == '^' || c == ')') ? 1 : 0; 
    if (c == '\0') break;
    else if (TOKEN_ID(c) == WHITESPACE) continue;
    else if (c == '(' || c == ')') {
      node.id = TOKEN_ID(c);
      node.pre = ceval_precedence[node.id];
    } else if (TOKEN_ID(c) == NUMBER) {
      node.pre = ceval_precedence[NUMBER];
      int i;
      char number[15];
      for (i = 0; i + 1 < sizeof(number);) {
        number[i++] = c;
        c = * expression;
        if (TOKEN_ID(c) == NUMBER || c == '.')
          expression++;
        else break;
      }
      number[i] = '\0';
      sscanf(number, "%lf", & node.number);
      node.id = NUMBER;
    } else if (c == '+' || c == '-' || 
      c == '*' || c == '/' || c == '%' || c == '\\' ||
      c == '^' ||
      (c == '!' && * (expression) != '=') || 
      (c == '!' && * (expression) == '=' && * (expression + 1) == '=') ||
      (c == '<' && * (expression) != '=') ||
      (c == '>' && * (expression) != '=') ||
      c == ',') {
      if (previous_id == NUMBER || previous_id == CLOSEPAR || previous_id == FACTORIAL) {
        node.id = TOKEN_ID(c);
        node.pre = ceval_precedence[node.id];
      } else {
        if (c == '-') {
          node.id = NEGSIGN;
          node.pre = ceval_precedence[node.id];
        } else if (c == '+') {
          node.id = POSSIGN;
          node.pre = ceval_precedence[node.id];
        } else {
          printf("[ceval]: Misplaced '%c' sign\n", c);
          return NULL;
        }
      }
    } else if (!memcmp(expression - 1, "pi", 2)) {
      expression = expression + (2 - 1);
      node.id = NUMBER;
      node.pre = ceval_precedence[node.id];
      node.number = CONST_PI;
    } else if (!memcmp(expression - 1, "exp", 3)) {
      expression = expression + (3 - 1);
      node.id = EXP;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "e", 1)) {
      expression = expression + (1 - 1);
      node.id = NUMBER;
      node.pre = ceval_precedence[node.id];
      node.number = CONST_E;
    } else if (!memcmp(expression - 1, "abs", 3)) {
      expression = expression + (3 - 1);
      node.id = ABS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sqrt", 4)) {
      expression = expression + (4 - 1);
      node.id = SQRT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cbrt", 4)) {
      expression = expression + (4 - 1);
      node.id = CBRT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "ceil", 4)) {
      expression = expression + (4 - 1);
      node.id = CEIL;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "floor", 5)) {
      expression = expression + (5 - 1);
      node.id = FLOOR;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "pow", 3)) {
      expression = expression + (3 - 1);
      node.id = POWFUN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "atan2", 5)) {
      expression = expression + (5 - 1);
      node.id = ATAN2;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "ln", 2)) {
      expression = expression + (2 - 1);
      node.id = LN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "log10", 5)) {
      expression = expression + (5 - 1);
      node.id = LOG10;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "log", 3)) {
      expression = expression + (3 - 1);
      node.id = LOG;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sinh", 4)) {
      expression = expression + (4 - 1);
      node.id = SINH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cosh", 4)) {
      expression = expression + (4 - 1);
      node.id = COSH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "tanh", 4)) {
      expression = expression + (4 - 1);
      node.id = TANH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sin", 3)) {
      expression = expression + (3 - 1);
      node.id = SIN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cos", 3)) {
      expression = expression + (3 - 1);
      node.id = COS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "tan", 3)) {
      expression = expression + (3 - 1);
      node.id = TAN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "asin", 4)) {
      expression = expression + (4 - 1);
      node.id = ARCSIN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "acos", 4)) {
      expression = expression + (4 - 1);
      node.id = ARCCOS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "atan", 4)) {
      expression = expression + (4 - 1);
      node.id = ARCTAN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "deg2rad", 7)) {
      expression = expression + (7 - 1);
      node.id = DEG2RAD;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "rad2deg", 7)) {
      expression = expression + (7 - 1);
      node.id = RAD2DEG;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "signum", 6)) {
      expression = expression + (6 - 1);
      node.id = SIGNUM;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "gcd", 3)) {
      expression = expression + (3 - 1);
      node.id = GCD;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "hcf", 3)) {
      expression = expression + (3 - 1);
      node.id = HCF;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "lcm", 3)) {
      expression = expression + (3 - 1);
      node.id = LCM;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "<=", 2)) {
      expression = expression + (2 - 1);
      node.id = LESSER;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, ">=", 2)) {
      expression = expression + (2 - 1);
      node.id = GREATER;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "==", 2)) {
      expression = expression + (2 - 1);
      node.id = EQUAL;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "!=", 2)) {
      expression = expression + (2 - 1);
      node.id = NOTEQUAL;
      node.pre = ceval_precedence[node.id];
    } else {
      printf("[ceval]: Unknown token '%c'.\n", c);
      ceval_delete_tree(root.right);
      root.right = NULL;
      break;
    }
    previous_id = node.id;
    current = insert_node(current, node, isRightAssoc);
  }
  if (root.right) root.right -> parent = NULL;
  return root.right;
}
void print_node(const ceval_node * node, int indent) {
  int i;
  char number[20];
  const char * str;
  if (!node) return;
  print_node(node -> right, indent + 4);
  if(node->id == NUMBER) {
    if ((long) node -> number == node -> number) //for integers, skip the trailing zeroes
      sprintf(number, "%.0f", node -> number);
    else sprintf(number, "%.2f", node -> number);
    str = number;
  }else{
    str = ceval_token_symbol[node->id];
  }
  for (i = 0; i < indent; i++) {
    putchar(' ');
    putchar(' ');
  }
  puts(str);
  print_node(node -> left, indent + 4);
}

void ceval_print_tree(const void * tree) {
  print_node((const ceval_node * ) tree, 0);
}

#endif
