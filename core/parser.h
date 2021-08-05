#ifndef CEVAL_PARSER
#define CEVAL_PARSER
#include "./tokens.h"

#include "./functions.h"

#include<stdio.h>
#include<malloc.h>
#include<string.h>

void * ceval_make_tree(char *);
ceval_node * ceval_insert_node(ceval_node *, ceval_node, int);
void ceval_print_tree(const void *);
void ceval_print_node(const ceval_node *, int);
void ceval_delete_node(ceval_node *);
void ceval_delete_tree(void *);

void ceval_delete_node(ceval_node * node) {
  if (!node) return;
  ceval_delete_node(node -> left);
  ceval_delete_node(node -> right);
  free(node);
}
void ceval_delete_tree(void * tree) {
  ceval_delete_node((ceval_node * ) tree);
}
ceval_node * ceval_insert_node(ceval_node * current, ceval_node item, int isRightAssoc) {
  if (item.id != CEVAL_OPENPAR &&
    item.id != CEVAL_NEGSIGN &&
    item.id != CEVAL_POSSIGN) {
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
  if (item.id == CEVAL_CLOSEPAR) { 
    ceval_node * parent_of_openpar = current -> parent;
    parent_of_openpar -> right = current -> right;
    if (current -> right) current -> right -> parent = parent_of_openpar;
    free(current);
    current = parent_of_openpar;

    if (current -> right -> id == CEVAL_COMMA && 
       (current -> id == CEVAL_POWFUN || current -> id == CEVAL_ATAN2 || 
        current -> id == CEVAL_GCD || current -> id == CEVAL_HCF || current -> id == CEVAL_LCM ||
        current -> id == CEVAL_LOG)) {
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
    CEVAL_OPENPAR,
    ceval_precedence[CEVAL_OPENPAR],
    0,
    NULL,
    NULL,
    NULL
  };
  ceval_node_id previous_id = CEVAL_OPENPAR;
  ceval_node * current = & root;
  int isRightAssoc = 0;
  while (1) {
    ceval_node node;
    char c = * expression++; 
    isRightAssoc = (c == '^' || c == ')') ? 1 : 0; 
    if (c == '\0') break;
    else if (ceval_singlechar_token_id(c) == CEVAL_WHITESPACE) continue;
    else if (c == '(' || c == ')') {
      node.id = ceval_singlechar_token_id(c);
      node.pre = ceval_precedence[node.id];
    } else if (ceval_singlechar_token_id(c) == CEVAL_NUMBER) {
      node.pre = ceval_precedence[CEVAL_NUMBER];
      int i;
      char number[15];
      for (i = 0; i + 1 < sizeof(number);) {
        number[i++] = c;
        c = * expression;
        if (ceval_singlechar_token_id(c) == CEVAL_NUMBER || c == '.')
          expression++;
        else break;
      }
      number[i] = '\0';
      sscanf(number, "%lf", & node.number);
      node.id = CEVAL_NUMBER;
    } else if (c == '+' || c == '-' || 
      c == '*' || c == '/' || c == '%' || c == '\\' ||
      c == '^' ||
      (c == '!' && * (expression) != '=') || 
      (c == '!' && * (expression) == '=' && * (expression + 1) == '=') ||
      (c == '<' && * (expression) != '=') ||
      (c == '>' && * (expression) != '=') ||
      c == ',') {
      if (previous_id == CEVAL_NUMBER || previous_id == CEVAL_CLOSEPAR || previous_id == CEVAL_FACTORIAL) {
        node.id = ceval_singlechar_token_id(c);
        node.pre = ceval_precedence[node.id];
      } else {
        if (c == '-') {
          node.id = CEVAL_NEGSIGN;
          node.pre = ceval_precedence[node.id];
        } else if (c == '+') {
          node.id = CEVAL_POSSIGN;
          node.pre = ceval_precedence[node.id];
        } else {
          printf("[ceval]: Misplaced '%c' sign\n", c);
          return NULL;
        }
      }
    } else if (!memcmp(expression - 1, "_pi", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_NUMBER;
      node.pre = ceval_precedence[node.id];
      node.number = CEVAL_CONST_PI;
    } else if (!memcmp(expression - 1, "exp", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_EXP;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "_e", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_NUMBER;
      node.pre = ceval_precedence[node.id];
      node.number = CEVAL_CONST_E;
    } else if (!memcmp(expression - 1, "e", 1)) {
      expression = expression + (1 - 1);
      node.id = CEVAL_SCI2DEC;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "abs", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_ABS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sqrt", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_SQRT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cbrt", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_CBRT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "ceil", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_CEIL;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "floor", 5)) {
      expression = expression + (5 - 1);
      node.id = CEVAL_FLOOR;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "pow", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_POWFUN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "atan2", 5)) {
      expression = expression + (5 - 1);
      node.id = CEVAL_ATAN2;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "ln", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_LN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "log10", 5)) {
      expression = expression + (5 - 1);
      node.id = CEVAL_LOG10;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "log", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_LOG;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sinh", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_SINH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cosh", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_COSH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "tanh", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_TANH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sin", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_SIN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cos", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_COS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "tan", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_TAN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "asin", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_ASIN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "acos", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_ACOS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "atan", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_ATAN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "deg2rad", 7)) {
      expression = expression + (7 - 1);
      node.id = CEVAL_DEG2RAD;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "rad2deg", 7)) {
      expression = expression + (7 - 1);
      node.id = CEVAL_RAD2DEG;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "signum", 6)) {
      expression = expression + (6 - 1);
      node.id = CEVAL_SIGNUM;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "gcd", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_GCD;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "hcf", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_HCF;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "lcm", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_LCM;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "int", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_INT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "frac", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_FRAC;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "<=", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_LESSER;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, ">=", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_GREATER;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "==", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_EQUAL;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "!=", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_NOTEQUAL;
      node.pre = ceval_precedence[node.id];
    } else {
      printf("[ceval]: Unknown token '%c'.\n", c);
      ceval_delete_tree(root.right);
      root.right = NULL;
      break;
    }
    previous_id = node.id;
    current = ceval_insert_node(current, node, isRightAssoc);
  }
  if (root.right) root.right -> parent = NULL;
  return root.right;
}
void ceval_print_node(const ceval_node * node, int indent) {
  int i;
  char number[20];
  const char * str;
  if (!node) return;
  ceval_print_node(node -> right, indent + 4);
  if(node->id == CEVAL_NUMBER) {
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
  ceval_print_node(node -> left, indent + 4);
}

void ceval_print_tree(const void * tree) {
  ceval_print_node((const ceval_node * ) tree, 0);
}

#endif
