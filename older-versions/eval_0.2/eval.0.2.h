/*
 *      - Addition(+), Subtraction(-), Multiplication(*), Division(/), Modulus(%), Quotient(\), Exponentiation(^) and Factorial(!)
 *        operations are supported for integers and floating point numbers
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
#include<stdio.h>
#include<malloc.h>
#include<math.h>
 //various types of tokens
typedef enum NodeID{
    WHITESPACE, 
    OPENPAR, CLOSEPAR, //parentheses
    POSSIGN, NEGSIGN, //positive and negative signs
    PLUS, MINUS,  //additive operators
    TIMES, DIVIDE, MODULUS, QUOTIENT,  //multiplicative operators
    POW, //exponential operator
    FACTORIAL, //unary factorial operator
    NUMBER //numbers
}NodeID;
 //their precedences
const int PREC[] = {
    0,  
    1, 1,  //parentheses
    3, 3, //positive and negative signs
    2, 2,  //additive operators
    4, 4, 4, 4,  //multiplicative operators
    5, //exponential operator
    6, //factorial
    10 //numbers
};
NodeID TOKEN_ID(char token){
    switch(token){
        case '(': return OPENPAR;
        case ')': return CLOSEPAR;
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return TIMES;
        case '/': return DIVIDE;
        case '%': return MODULUS;
        case '\\':return QUOTIENT;
        case '^': return POW;
        case '!': return FACTORIAL;
        default: 
                if('0'<=token && token<='9') return NUMBER;
                else if(token==' ' || token=='\t' || token=='\r' || token=='\n') return WHITESPACE;
    }
return OPENPAR;
}
typedef struct _Node {
    enum NodeID ID;
    int pre;
    double number; //only to be used if this.ID == NUMBER
    struct _Node *left, *right, *parent;
} Node;
double modulus(double a, double b){
    //modulus will be in the range [0, b)
    //it can be found by repeatedly subtracting `b` from `a` until we get a result in that range
    while(1){
        if(a<b){
            return a;
        }
        a = a - b;
    }
}
double quotient(double a, double b){
    //a = b*q + r
    //q = (a - r)/b
    return (a-modulus(a, b))/b;
}
void deleteNode (Node* node){
    if(!node) return; //nothing to delete
    deleteNode (node->left); //delete left node
    deleteNode (node->right); //delete right node
    free(node); //delete the parent
}
void  deleteET (void* tree){
    deleteNode ((Node*)tree); //start recursive deletetion from the root node
}
Node* insertNode (Node* current, Node item, int isRightAssoc){
    if(item.ID!=OPENPAR&& //Operations enclosed by open/close parentheses need to be resolved before everything else, hence, the tree is not climbed
        item.ID!=NEGSIGN&& //negation is similar to OPENPAR. -Exp == -(Exp)
        item.ID!=POSSIGN){
        if(isRightAssoc){
            while(current->pre > item.pre){
                current = current->parent; //for right assoc operators, climb up the tree until the PREC[current] <= PREC[new_node]
            }
        }else{
            while(current->pre >= item.pre){
            current = current->parent;    //for left assoc operators, climb up the tree until the PREC[current] < PREC[new_node]
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
    if(item.ID==CLOSEPAR){ //do not add the close parenthesis in the tree, just remove it's paired open counterpart
    //current has climbed to the OPENPAR that is to be removed
    //current->parent is the parent of the OPENPAR node
    //current->right is the subtree_under_OPENPAR
        Node * parentOfOPENPAR = current->parent;
        parentOfOPENPAR->right = current->right; //join parent with subtree_under_OPENPAR
        if(current->right) current->right->parent = parentOfOPENPAR; //join the subtree_under_OPENPAR with the parent
        free(current); //remove (
        current = parentOfOPENPAR;
        return current;
    }
    Node* newnode = (Node *)malloc(sizeof(Node));
    //create new node
    *newnode = item;
    newnode->right = NULL;
//                    *** ADDITION OF A NEW NODE ***
//     current                                                      current
//       /\                                                           /\
//      /  \         +          newnode           ====>              /  \      
// left  right                                                left    newnode
//                                                                       /\
//                                                                      /  \
//                                                                   right  NULL

    newnode->left = current->right;
    if(current->right) current->right->parent = newnode;
    current->right = newnode;
    newnode->parent = current;
    current = newnode;
return current;
}
void * makeET(const char * expression){
    if(expression==NULL) return NULL;

    //initialize the tree with the least precedence root node '('
    Node root = {OPENPAR, PREC[OPENPAR], 0, NULL, NULL, NULL};
    NodeID previousID = OPENPAR;
    Node * current = &root;
    int isRightAssoc = 0;
    while(1){
        Node node;
        char c = *expression++; /* get latest character of string */
        isRightAssoc = (c=='^'||c==')')?1:0; //close parenthesis is given right associativity because it needs to climb up to it's paired counterpart while the tree is climbed
        // string ends 
        if(c=='\0') break;
        // whitespaces are to be ignored
        else if(TOKEN_ID(c)==WHITESPACE) continue;
        // deal with a multidigit number
        else if(c=='('||c==')'){
            node.ID = TOKEN_ID(c);
            node.pre = PREC[node.ID];
        }
        else if(TOKEN_ID(c)==NUMBER){
            node.pre = PREC[NUMBER];
            int i;
            char number[15];
            for(i=0;i+1<sizeof(number);){
                number[i++] = c;
                c = *expression;
                if(TOKEN_ID(c)==NUMBER || c=='.')
                    expression++;
                else break;
            }
            number[i] = '\0';
            sscanf(number, "%lf", &node.number); //sscanf() scans the char array `number` and formats it into a numeric double type and stores the result at &node.number
            node.ID = NUMBER;
        }else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='\\'||c=='^'||c=='!'){ //one of the four fundamental binary math operators
            if(previousID==NUMBER||previousID==CLOSEPAR||previousID==FACTORIAL){
                node.ID = TOKEN_ID(c);
                node.pre = PREC[node.ID];
            }else{
                if(c=='-'){ //a negation
                    node.ID = NEGSIGN;
                    node.pre = PREC[node.ID];
                }else if(c=='+'){ //a positive sign
                    node.ID = POSSIGN;
                    node.pre = PREC[node.ID];
                }else{
                    printf("[PARSER]: Misplaced '%c' sign\n", c);
                    return NULL;
                }
            }
        }else{
            printf("[PARSER]: Unknown token '%c'.\n", c);
            deleteET (root.right);
            root.right = NULL;
            break;
        }
        previousID = node.ID;
        current = insertNode (current, node, isRightAssoc);
    }
    if(root.right) root.right->parent = NULL;
    return root.right; //the address of the right child of the least precedence '(' node is to be returned
}
double _evaluateET (const Node* node){
    if(!node) return 0;
    double left, right;
    left  = _evaluateET (node->left);
    right = _evaluateET (node->right);
    switch(node->ID){
        case PLUS:      return left+right;
        case MINUS:     return left-right;
        case NEGSIGN:   return -right;
        case POSSIGN:   return right;
        case TIMES:     return left*right;
        case DIVIDE:    return left/right;
        case MODULUS:    return modulus(left, right);
        case QUOTIENT: return quotient(left, right);
        case POW:      return pow(left, right); //from math.h
        case FACTORIAL:return tgamma(left+1); //true_gamma(x+1) == factorial(x)
        default:        return node->number;
    }
}
//argument is of type `void`, so the main code doesn't depend on Node type
double evaluateET(const void * node){
    return _evaluateET((Node *)node);
}
double evaluateCString(char * expr){
    void * tree = makeET(expr);
    double result = evaluateET(tree);
    deleteET(tree);
return result;
}

void printNode (const Node* node, int indent){
    int i;
    char number[20];
    const char* str;
    if(!node) return;
    printNode (node->right, indent+4);  //print the right subtree indented four-spaces away from the it's parent node
    switch(node->ID){
        case NUMBER:
            if((long)node->number == node->number)
                 sprintf(number, "%.0f", node->number);
            else sprintf(number, "%.2f", node->number);
            str = number;
            break;
        case OPENPAR: str = "(";   break;
        case CLOSEPAR:str = ")";  break;
        case PLUS:        str = "+";   break;
        case MINUS:       str = "-";   break;
        case NEGSIGN:     str = "-";   break;
        case POSSIGN:     str = "+";   break;
        case TIMES:       str = "*";   break;
        case DIVIDE:      str = "/";   break;
        case MODULUS:     str = "%";   break;
        case QUOTIENT:    str = "\\";  break;
        case POW:         str = "^";   break;
        case FACTORIAL:   str = "!";   break;
        default:          str = "error";
    }
    for(i=0; i < indent; i++) putchar(' '); puts(str); //print a the parent node
    printNode (node->left, indent+4); //print the left subtree indented four spaces away from it's parent node
}

void printET (const void* tree){
    printNode ((const Node*)tree, 0); 
}
