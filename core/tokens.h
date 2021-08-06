#ifndef CEVAL_TOKENS
#define CEVAL_TOKENS
#include<string.h>

// precedences :: <https://en.cppreference.com/w/cpp/language/operator_precedence>

typedef enum ceval_node_id {
    CEVAL_WHITESPACE, // 0
    CEVAL_OPENPAR, CEVAL_CLOSEPAR, // 1
    CEVAL_COMMA, // 2

    CEVAL_OR, // 3
    CEVAL_AND, // 4
    CEVAL_BIT_OR, // 5
    CEVAL_BIT_XOR, // 6 
    CEVAL_BIT_AND, // 7
    CEVAL_EQUAL, CEVAL_NOTEQUAL, // 8
    CEVAL_LESSER, CEVAL_GREATER, CEVAL_LESSER_S, CEVAL_GREATER_S, // 9
    CEVAL_BIT_LSHIFT, CEVAL_BIT_RSHIFT, // 10
    CEVAL_PLUS, CEVAL_MINUS, // 11
    CEVAL_TIMES, CEVAL_DIVIDE, CEVAL_MODULO, CEVAL_QUOTIENT, // 12

    CEVAL_POW, // 13 '**' operator

    CEVAL_GCD, CEVAL_HCF, CEVAL_LCM, CEVAL_LOG,
    CEVAL_ATAN2, CEVAL_SCI2DEC, CEVAL_POWFUN, 

    CEVAL_ABS, CEVAL_EXP, CEVAL_SQRT,CEVAL_CBRT, 
    CEVAL_LN, CEVAL_LOG10, CEVAL_CEIL, CEVAL_FLOOR, 
    CEVAL_SIGNUM, CEVAL_FACTORIAL, CEVAL_INT, CEVAL_FRAC, 
    CEVAL_DEG2RAD, CEVAL_RAD2DEG, CEVAL_SIN, CEVAL_COS, 
    CEVAL_TAN, CEVAL_ASIN, CEVAL_ACOS, CEVAL_ATAN, 
    CEVAL_SINH, CEVAL_COSH, CEVAL_TANH,

    CEVAL_NOT, CEVAL_BIT_NOT, // 14
    CEVAL_POSSIGN, CEVAL_NEGSIGN, // 15
    CEVAL_NUMBER, // 16
    CEVAL_CONST_PI, // 16
    CEVAL_CONST_E // 16
} ceval_node_id;
typedef enum ceval_token_type {
    CEVAL_UNARY_OPERATOR,
    CEVAL_BINARY_OPERATOR,
    CEVAL_UNARY_FUNCTION,
    CEVAL_BINARY_FUNCTION,
    CEVAL_OTHER
} ceval_token_type;
typedef struct ceval_token_info_ {
    ceval_node_id id;
    const char * symbol; 
    double prec;
    ceval_token_type token_type;
} ceval_token_info_; 
ceval_token_info_ ceval_token_info[] = {
    { CEVAL_WHITESPACE, " ", 0, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\n", 0, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\t", 0, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\r", 0, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\b", 0, CEVAL_OTHER },

    { CEVAL_DEG2RAD, "deg2rad", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_RAD2DEG, "rad2deg", 15, CEVAL_UNARY_FUNCTION },

    { CEVAL_SIGNUM, "signum", 15, CEVAL_UNARY_FUNCTION },

    { CEVAL_ATAN2, "atan2", 15, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_LOG10, "log10", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_FLOOR, "floor", 15, CEVAL_UNARY_FUNCTION },

    { CEVAL_SQRT, "sqrt", 15 , CEVAL_UNARY_FUNCTION },
    { CEVAL_CBRT, "cbrt", 15 , CEVAL_UNARY_FUNCTION },
    { CEVAL_CEIL, "ceil", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_FRAC, "frac", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_FACTORIAL, "fact", 15, CEVAL_UNARY_FUNCTION }, 
    { CEVAL_SINH, "sinh", 15, CEVAL_UNARY_FUNCTION }, //hyperbolics before trig functions
    { CEVAL_COSH, "cosh", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_TANH, "tanh", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_ASIN, "asin", 15, CEVAL_UNARY_FUNCTION }, 
    { CEVAL_ACOS, "acos", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_ATAN, "atan", 15, CEVAL_UNARY_FUNCTION },
    
    { CEVAL_POWFUN, "pow", 15, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_GCD, "gcd", 15, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_HCF, "hcf", 15, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_LCM, "lcm", 15, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_LOG, "log", 15, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_INT, "int", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_SIN, "sin", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_COS, "cos", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_TAN, "tan", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_ABS, "abs", 15 , CEVAL_UNARY_FUNCTION },
    { CEVAL_EXP, "exp", 15 , CEVAL_UNARY_FUNCTION }, //exp before e
    { CEVAL_CONST_PI, "_pi", 18, CEVAL_OTHER },

    { CEVAL_CONST_E, "_e", 18, CEVAL_OTHER },
    { CEVAL_LN, "ln", 15, CEVAL_UNARY_FUNCTION },
    { CEVAL_OR, "||", 3, CEVAL_BINARY_OPERATOR },
    { CEVAL_AND, "&&", 4, CEVAL_BINARY_OPERATOR },
    { CEVAL_EQUAL, "==", 8 , CEVAL_BINARY_OPERATOR },
    { CEVAL_NOTEQUAL, "!=", 8 , CEVAL_BINARY_OPERATOR },
    { CEVAL_LESSER, "<=", 9 , CEVAL_BINARY_OPERATOR }, //<= and >= before < and >
    { CEVAL_GREATER, ">=", 9 , CEVAL_BINARY_OPERATOR },
    { CEVAL_BIT_LSHIFT, "<<", 10, CEVAL_BINARY_OPERATOR},
    { CEVAL_BIT_RSHIFT, ">>", 10, CEVAL_BINARY_OPERATOR},
    { CEVAL_QUOTIENT, "//", 13 , CEVAL_BINARY_OPERATOR }, 
    { CEVAL_POW, "**", 14 , CEVAL_BINARY_OPERATOR },

    { CEVAL_OPENPAR, "(", 1, CEVAL_OTHER },
    { CEVAL_CLOSEPAR, ")", 1, CEVAL_OTHER },
    { CEVAL_COMMA, ",", 2 , CEVAL_BINARY_OPERATOR },
    { CEVAL_BIT_OR, "|", 5, CEVAL_BINARY_OPERATOR},
    { CEVAL_BIT_XOR, "^", 6, CEVAL_BINARY_OPERATOR},
    { CEVAL_BIT_AND, "&", 7, CEVAL_BINARY_OPERATOR},
    { CEVAL_LESSER_S, "<", 9 , CEVAL_BINARY_OPERATOR },
    { CEVAL_GREATER_S, ">", 9 , CEVAL_BINARY_OPERATOR },
    { CEVAL_PLUS, "+", 11 , CEVAL_BINARY_OPERATOR }, //PLUS, MINUS are to be looked up before POSSIGN, NEGSIGN
    { CEVAL_MINUS, "-", 11 , CEVAL_BINARY_OPERATOR },
    { CEVAL_POSSIGN, "+", 12, CEVAL_UNARY_OPERATOR }, 
    { CEVAL_NEGSIGN, "-", 12, CEVAL_UNARY_OPERATOR }, 
    { CEVAL_TIMES, "*", 13 , CEVAL_BINARY_OPERATOR },
    { CEVAL_DIVIDE, "/", 13 , CEVAL_BINARY_OPERATOR },
    { CEVAL_MODULO, "%", 13 , CEVAL_BINARY_OPERATOR },
    { CEVAL_NOT, "!", 16, CEVAL_UNARY_FUNCTION},
    { CEVAL_BIT_NOT, "~", 16, CEVAL_UNARY_OPERATOR},

    { CEVAL_SCI2DEC, "e", 17 , CEVAL_BINARY_OPERATOR },
    { CEVAL_NUMBER, "0", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "1", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "2", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "3", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "4", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "5", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "6", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "7", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "8", 18, CEVAL_OTHER },
    { CEVAL_NUMBER, "9", 18, CEVAL_OTHER },
}; 
#ifndef CEVAL_TOKEN_TABLE_SIZE
#define CEVAL_TOKEN_TABLE_SIZE sizeof(ceval_token_info) / sizeof(ceval_token_info[0])
#endif
int ceval_is_binary_opr(ceval_node_id id) {
    for (int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (ceval_token_info[i].id == id && ceval_token_info[i].token_type == CEVAL_BINARY_OPERATOR) {
            return 1;
        }
    }
    return 0;
}
int ceval_is_binay_fun(ceval_node_id id) {
    for (int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (ceval_token_info[i].id == id && ceval_token_info[i].token_type == CEVAL_BINARY_FUNCTION) {
            return 1;
        }
    }
    return 0;
}
const char * ceval_token_symbol(ceval_node_id id) {
    for (int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (id == ceval_token_info[i].id) {
            return ceval_token_info[i].symbol;
        }
    }
}
ceval_node_id ceval_token_id(char * symbol) {
    for (int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (!strcmp(ceval_token_info[i].symbol, symbol)) {
            return ceval_token_info[i].id;
        }
    }
}
double ceval_token_prec(ceval_node_id id) {
    for (int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (id == ceval_token_info[i].id) {
            return ceval_token_info[i].prec;
        }
    }
}
typedef struct ceval_node {
    enum ceval_node_id id;
    double pre;
    double number;
    struct ceval_node * left, * right, * parent;
}
ceval_node;
#ifdef __cplusplus
  #define CEVAL_CXX
  #include<iostream>
  #include<string>
#endif
#endif