#ifndef BET_PARSER
#define BET_PARSER
#include "./tokens.h"

#include "./functions.h"

#include<stdio.h>
#include<malloc.h>
#include<string.h> //for memcmp() and c_str()

void deleteNode(Node * node) {
  if (!node) return; //nothing to delete
  deleteNode(node -> left); //delete left node
  deleteNode(node -> right); //delete right node
  free(node); //delete the parent
}
void deleteET(void * tree) {
  deleteNode((Node * ) tree); //start recursive deletetion from the root node
}
Node * insertNode(Node * current, Node item, int isRightAssoc) {
  if (item.ID != OPENPAR && //Operations enclosed by open/close parentheses need to be resolved before everything else, hence, the tree is not climbed
    item.ID != NEGSIGN && //negation is similar to OPENPAR. -Exp == -(Exp)
    item.ID != POSSIGN) {
    if (isRightAssoc) {
      while (current -> pre > item.pre) {
        current = current -> parent; //for right assoc operators, climb up the tree until the PREC[current] <= PREC[new_node]
      }
    } else {
      while (current -> pre >= item.pre) {
        current = current -> parent; //for left assoc operators, climb up the tree until the PREC[current] < PREC[new_node]
      }
    }
  }
  //   .         *** ADDITION OF A CLOSEPAR ***             .
  //    .                                                    .
  //     \                                                    \              
  //     parent                                              parent                                                    
  //       /\                                                  /\                                                           
  //      /  \                                                /  \                                    
  //    left  (        +      )             ====>         left  subtree_under_OPENPAR            
  //           \                                                             
  //            \                                                            
  //   subtree_under_OPENPAR
  if (item.ID == CLOSEPAR) { 
    //do not add the close parenthesis in the tree, just remove it's paired open counterpart
    //current has climbed to the OPENPAR that is to be removed
    //current->parent is the parent of the OPENPAR node
    //current->right is the subtree_under_OPENPAR
    Node * parentOfOPENPAR = current -> parent;
    parentOfOPENPAR -> right = current -> right; //join parent with subtree_under_OPENPAR
    if (current -> right) current -> right -> parent = parentOfOPENPAR; //join the subtree_under_OPENPAR with the parent
    free(current); //remove (
    current = parentOfOPENPAR;

    if (current -> right -> ID == COMMA && (current -> ID == POWFUN || current -> ID == ATAN2)) {  // if the right child is a comma and the node itself is a pow() function
      Node * addressOfCOMMA = current -> right;
      parentOfOPENPAR -> left = addressOfCOMMA -> left;
      addressOfCOMMA -> left -> parent = parentOfOPENPAR;
      parentOfOPENPAR -> right = addressOfCOMMA -> right;
      addressOfCOMMA -> right -> parent = parentOfOPENPAR;
      free(addressOfCOMMA); //remove ',' node
    }
    return current;
  }
  Node * newnode = (Node * ) malloc(sizeof(Node));
  //create new node
  * newnode = item;
  newnode -> right = NULL;
  //                    *** ADDITION OF A NEW NODE ***
  //     current                                                      current
  //       /\                                                           /\
  //      /  \         +          newnode           ====>              /  \      
  // left  right                                                left    newnode
  //                                                                       /\
  //                                                                      /  \
  //                                                                   right  NULL

  newnode -> left = current -> right;
  if (current -> right) current -> right -> parent = newnode;
  current -> right = newnode;
  newnode -> parent = current;
  current = newnode;
  return current;
}
void * makeET(const char * expression) {
  if (expression == NULL) return NULL;

  //initialize the tree with the least precedence root node '('
  Node root = {
    OPENPAR,
    PREC[OPENPAR],
    0,
    NULL,
    NULL,
    NULL
  };
  NodeID previousID = OPENPAR;
  Node * current = & root;
  int isRightAssoc = 0;
  while (1) {
    Node node;
    char c = * expression++; /* get latest character of string */
    isRightAssoc = (c == '^' || c == ')') ? 1 : 0; //close parenthesis is given right associativity because it needs to climb up to it's paired counterpart while the tree is climbed
    // string ends 
    if (c == '\0') break;
    // whitespaces are to be ignored
    else if (TOKEN_ID(c) == WHITESPACE) continue;
    // deal with a multidigit number
    else if (c == '(' || c == ')') {
      node.ID = TOKEN_ID(c);
      node.pre = PREC[node.ID];
    } else if (TOKEN_ID(c) == NUMBER) {
      node.pre = PREC[NUMBER];
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
      sscanf(number, "%lf", & node.number); //sscanf() scans the char array `number` and formats it into a numeric double type and stores the result at &node.number
      node.ID = NUMBER;
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '\\' || c == '^' || //fundamental operations
      (c == '!' && * (expression) != '=') ||
      (c == '<' && * (expression) != '=') ||
      (c == '>' && * (expression) != '=') || //!, <, > should not be followed by = sign
      c == ',') {
      if (previousID == NUMBER || previousID == CLOSEPAR || previousID == FACTORIAL) {
        node.ID = TOKEN_ID(c);
        node.pre = PREC[node.ID];
      } else {
        if (c == '-') { //a negation
          node.ID = NEGSIGN;
          node.pre = PREC[node.ID];
        } else if (c == '+') { //a positive sign
          node.ID = POSSIGN;
          node.pre = PREC[node.ID];
        } else {
          printf("[PARSER]: Misplaced '%c' sign\n", c);
          return NULL;
        }
      }
    } else if (!memcmp(expression - 1, "PI", 2)) {
      expression = expression + (2 - 1);
      node.ID = NUMBER;
      node.pre = PREC[node.ID];
      node.number = CONST_PI;
    } else if (!memcmp(expression - 1, "E", 1)) {
      expression = expression + (1 - 1);
      node.ID = NUMBER;
      node.pre = PREC[node.ID];
      node.number = CONST_E;
    } else if (!memcmp(expression - 1, "abs", 3)) {
      expression = expression + (3 - 1);
      node.ID = ABS;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "sqrt", 4)) {
      expression = expression + (4 - 1);
      node.ID = SQRT;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "cbrt", 4)) {
      expression = expression + (4 - 1);
      node.ID = CBRT;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "ceil", 4)) {
      expression = expression + (4 - 1);
      node.ID = CEIL;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "floor", 5)) {
      expression = expression + (5 - 1);
      node.ID = FLOOR;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "pow", 3)) {
      expression = expression + (3 - 1);
      node.ID = POWFUN;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "atan2", 5)) {
      expression = expression + (5 - 1);
      node.ID = ATAN2;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "exp", 3)) {
      expression = expression + (3 - 1);
      node.ID = EXP;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "ln", 2)) {
      expression = expression + (2 - 1);
      node.ID = LN;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "log", 3)) {
      expression = expression + (3 - 1);
      node.ID = LOG;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "sinh", 4)) {
      expression = expression + (4 - 1);
      node.ID = SINH;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "cosh", 4)) {
      expression = expression + (4 - 1);
      node.ID = COSH;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "tanh", 4)) {
      expression = expression + (4 - 1);
      node.ID = TANH;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "sin", 3)) {
      expression = expression + (3 - 1);
      node.ID = SIN;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "cos", 3)) {
      expression = expression + (3 - 1);
      node.ID = COS;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "tan", 3)) {
      expression = expression + (3 - 1);
      node.ID = TAN;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "asin", 4)) {
      expression = expression + (4 - 1);
      node.ID = ARCSIN;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "acos", 4)) {
      expression = expression + (4 - 1);
      node.ID = ARCCOS;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "atan", 4)) {
      expression = expression + (4 - 1);
      node.ID = ARCTAN;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "<=", 2)) {
      expression = expression + (2 - 1);
      node.ID = LESSER;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, ">=", 2)) {
      expression = expression + (2 - 1);
      node.ID = GREATER;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "==", 2)) {
      expression = expression + (2 - 1);
      node.ID = EQUAL;
      node.pre = PREC[node.ID];
    } else if (!memcmp(expression - 1, "!=", 2)) {
      expression = expression + (2 - 1);
      node.ID = NOTEQUAL;
      node.pre = PREC[node.ID];
    } else {
      printf("[PARSER]: Unknown token '%c'.\n", c);
      deleteET(root.right);
      root.right = NULL;
      break;
    }
    previousID = node.ID;
    current = insertNode(current, node, isRightAssoc);
  }
  if (root.right) root.right -> parent = NULL;
  return root.right; //the address of the right child of the least precedence '(' node is to be returned
}
#ifdef CXX
void * makeET(std::string expr) {
  return makeET((char *)expr.c_str());
}
#endif
void printNode(const Node * node, int indent) {
  int i;
  char number[20];
  const char * str;
  if (!node) return;
  printNode(node -> right, indent + 4); //print the right subtree indented four-spaces away from the it's parent node
  switch (node -> ID) {
  case NUMBER:
    if ((long) node -> number == node -> number)
      sprintf(number, "%.0f", node -> number);
    else sprintf(number, "%.2f", node -> number);
    str = number;
    break;
  case OPENPAR:
    str = "(";
    break;
  case CLOSEPAR:
    str = ")";
    break;
  case PLUS:
    str = "+";
    break;
  case MINUS:
    str = "-";
    break;
  case NEGSIGN:
    str = "-";
    break;
  case POSSIGN:
    str = "+";
    break;
  case TIMES:
    str = "*";
    break;
  case DIVIDE:
    str = "/";
    break;
  case MODULUS:
    str = "%";
    break;
  case QUOTIENT:
    str = "\\";
    break;
  case POW:
    str = "^";
    break;
  case FACTORIAL:
    str = "!";
    break;
  case ABS:
    str = "abs";
    break;
  case CEIL:
    str = "ceil";
    break;
  case FLOOR:
    str = "floor";
    break;
  case EXP:
    str = "exp";
    break;
  case POWFUN:
    str = "pow";
    break;
  case ATAN2:
    str = "atan2";
    break;
  case LN:
    str = "ln";
    break;
  case LOG:
    str = "log";
    break;
  case SQRT:
    str = "sqrt";
    break;
  case CBRT:
    str = "cbrt";
    break;
  case SINH:
    str = "sinh";
    break;
  case COSH:
    str = "cosh";
    break;
  case TANH:
    str = "tanh";
    break;
  case SIN:
    str = "sin";
    break;
  case COS:
    str = "cos";
    break;
  case TAN:
    str = "tan";
    break;
  case ARCSIN:
    str = "asin";
    break;
  case ARCCOS:
    str = "acos";
    break;
  case ARCTAN:
    str = "atan";
    break;
  case COMMA:
    str = ",";
    break;
  case LESSER:
    str = "<=";
    break;
  case GREATER:
    str = ">=";
    break;
  case LESSER_S:
    str = "<";
    break;
  case GREATER_S:
    str = ">";
    break;
  case EQUAL:
    str = "==";
    break;
  case NOTEQUAL:
    str = "!=";
    break;
  default:
    str = "[PARSER]: Error!";
  }
  for (i = 0; i < indent; i++) {
    putchar(' ');
    putchar(' '); //increase indentation 
  }
  puts(str); //print a the parent node
  printNode(node -> left, indent + 4); //print the left subtree indented four spaces away from it's parent node
}

void printET(const void * tree) {
  printNode((const Node * ) tree, 0);
}

#endif
