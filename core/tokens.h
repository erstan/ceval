#ifndef CEVAL_TOKENS
#define CEVAL_TOKENS
#include<string.h>

typedef enum ceval_node_id {
    CEVAL_WHITESPACE, CEVAL_OPENPAR, CEVAL_CLOSEPAR, CEVAL_COMMA, 
    CEVAL_OR, CEVAL_AND, CEVAL_BIT_OR, CEVAL_BIT_XOR,
    CEVAL_BIT_AND, CEVAL_EQUAL, CEVAL_NOTEQUAL,CEVAL_LESSER,
    CEVAL_GREATER, CEVAL_LESSER_S, CEVAL_GREATER_S, CEVAL_BIT_LSHIFT, 
    CEVAL_BIT_RSHIFT, CEVAL_PLUS, CEVAL_MINUS, CEVAL_TIMES, 
    CEVAL_DIVIDE, CEVAL_MODULO, CEVAL_QUOTIENT, CEVAL_POW,
    CEVAL_GCD, CEVAL_HCF, CEVAL_LCM, CEVAL_LOG,
    CEVAL_ATAN2, CEVAL_POWFUN, 

    CEVAL_ABS, CEVAL_EXP, CEVAL_SQRT,CEVAL_CBRT, 
    CEVAL_LN, CEVAL_LOG10, CEVAL_CEIL, CEVAL_FLOOR, 
    CEVAL_SIGNUM, CEVAL_FACTORIAL, CEVAL_INT, CEVAL_FRAC, 
    CEVAL_DEG2RAD, CEVAL_RAD2DEG, CEVAL_SIN, CEVAL_COS, 
    CEVAL_TAN, CEVAL_ASIN, CEVAL_ACOS, CEVAL_ATAN, 
    CEVAL_SINH, CEVAL_COSH, CEVAL_TANH,CEVAL_NOT, 
    CEVAL_BIT_NOT,CEVAL_POSSIGN, CEVAL_NEGSIGN, 
    
    CEVAL_NUMBER, CEVAL_CONST_PI, CEVAL_CONST_E
} ceval_node_id;
typedef enum ceval_token_prec_specifiers {
// precedences :: <https://en.cppreference.com/w/cpp/language/operator_precedence>
// these precision specifiers are ordered in the ascending order of their precedences
// here, the higher precedence operators are evaluated first and end up at the bottom of the parse trees
    CEVAL_PREC_IGNORE, 
    // {' ', '\t', '\n', '\b', '\r'}
    CEVAL_PREC_PARANTHESES,
    // {'(', ')'}
    CEVAL_PREC_COMMA_OPR,
    // {','}
    CEVAL_PREC_LOGICAL_OR_OPR,
    // {'||'}
    CEVAL_PREC_LOGICAL_AND_OPR,
    // {'&&'}
    CEVAL_PREC_BIT_OR_OPR,
    // {'|'}
    CEVAL_PREC_BIT_XOR_OPR,
    // {'^'}
    CEVAL_PREC_BIT_AND_OPR,
    // {'&'}
    CEVAL_PREC_EQUALITY_OPRS,
    // {'==', '!='}
    CEVAL_PREC_RELATIONAL_OPRS,
    // {'<', '>', '<=', '>='}
    CEVAL_PREC_BIT_SHIFT_OPRS,
    // {'<<', '>>'}
    CEVAL_PREC_ADDITIVE_OPRS,
    // {'+', '-'}
    CEVAL_PREC_SIGN_OPRS,
    // {'+', '-'}
    CEVAL_PREC_MULTIPLICATIVE_OPRS,
    // {'*', '/', '%', '//'}
    CEVAL_PREC_EXPONENTIATION_OPR,
    // {'**'}
    CEVAL_PREC_FUNCTIONS,
    // {
    //     'exp()', 'sqrt()', 'cbrt()', 'sin()',
    //     'cos()', 'tan()', 'asin()', 'acos()', 
    //     'atan()', 'sinh()', 'cosh()', 'tanh()', 
    //     'abs()', 'ceil()', 'floor()', 'log10()', 
    //     'ln()', 'deg2rad()', 'rad2deg()', 'signum()',
    //     'int()', 'frac()', 'fact()', `pow()`, 
    //     `atan2()`, `gcd()`, `hcf()`, `lcm()`,
    //     `log()`
    // }
    CEVAL_PREC_NOT_OPRS,
    // {'!', '~'}}
    CEVAL_PREC_NUMERIC
    // {'pi', 'pi', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
} ceval_token_prec_specifiers;
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
static ceval_token_info_ ceval_token_info[] = {
    { CEVAL_WHITESPACE, " ", CEVAL_PREC_IGNORE, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\n", CEVAL_PREC_IGNORE, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\t", CEVAL_PREC_IGNORE, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\r", CEVAL_PREC_IGNORE, CEVAL_OTHER },
    { CEVAL_WHITESPACE, "\b", CEVAL_PREC_IGNORE, CEVAL_OTHER },

    { CEVAL_DEG2RAD, "deg2rad", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_RAD2DEG, "rad2deg", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },

    { CEVAL_SIGNUM, "signum", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },

    { CEVAL_ATAN2, "atan2", CEVAL_PREC_FUNCTIONS, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_LOG10, "log10", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_FLOOR, "floor", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },

    { CEVAL_SQRT, "sqrt", CEVAL_PREC_FUNCTIONS , CEVAL_UNARY_FUNCTION },
    { CEVAL_CBRT, "cbrt", CEVAL_PREC_FUNCTIONS , CEVAL_UNARY_FUNCTION },
    { CEVAL_CEIL, "ceil", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_FRAC, "frac", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_FACTORIAL, "fact", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION }, 
    { CEVAL_SINH, "sinh", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION }, 
    { CEVAL_COSH, "cosh", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_TANH, "tanh", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_ASIN, "asin", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION }, 
    { CEVAL_ACOS, "acos", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_ATAN, "atan", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    
    { CEVAL_POWFUN, "pow", CEVAL_PREC_FUNCTIONS, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_GCD, "gcd", CEVAL_PREC_FUNCTIONS, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_HCF, "hcf", CEVAL_PREC_FUNCTIONS, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_LCM, "lcm", CEVAL_PREC_FUNCTIONS, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_LOG, "log", CEVAL_PREC_FUNCTIONS, CEVAL_BINARY_FUNCTION }, 
    { CEVAL_INT, "int", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_SIN, "sin", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_COS, "cos", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_TAN, "tan", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_ABS, "abs", CEVAL_PREC_FUNCTIONS , CEVAL_UNARY_FUNCTION },
    { CEVAL_EXP, "exp", CEVAL_PREC_FUNCTIONS , CEVAL_UNARY_FUNCTION },

    { CEVAL_CONST_PI, "pi", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_LN, "ln", CEVAL_PREC_FUNCTIONS, CEVAL_UNARY_FUNCTION },
    { CEVAL_OR, "||", CEVAL_PREC_LOGICAL_OR_OPR, CEVAL_BINARY_OPERATOR },
    { CEVAL_AND, "&&", CEVAL_PREC_LOGICAL_AND_OPR, CEVAL_BINARY_OPERATOR },
    { CEVAL_EQUAL, "==", CEVAL_PREC_EQUALITY_OPRS, CEVAL_BINARY_OPERATOR },
    { CEVAL_NOTEQUAL, "!=", CEVAL_PREC_EQUALITY_OPRS, CEVAL_BINARY_OPERATOR },
    { CEVAL_LESSER, "<=", CEVAL_PREC_RELATIONAL_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_GREATER, ">=", CEVAL_PREC_RELATIONAL_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_BIT_LSHIFT, "<<", CEVAL_PREC_BIT_SHIFT_OPRS, CEVAL_BINARY_OPERATOR},
    { CEVAL_BIT_RSHIFT, ">>", CEVAL_PREC_BIT_SHIFT_OPRS, CEVAL_BINARY_OPERATOR},
    { CEVAL_QUOTIENT, "//", CEVAL_PREC_MULTIPLICATIVE_OPRS , CEVAL_BINARY_OPERATOR }, 
    { CEVAL_POW, "**", CEVAL_PREC_EXPONENTIATION_OPR , CEVAL_BINARY_OPERATOR },

    { CEVAL_CONST_E, "e", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_OPENPAR, "(", CEVAL_PREC_PARANTHESES, CEVAL_OTHER },
    { CEVAL_CLOSEPAR, ")", CEVAL_PREC_PARANTHESES, CEVAL_OTHER },
    { CEVAL_COMMA, ",", CEVAL_PREC_COMMA_OPR , CEVAL_BINARY_OPERATOR },
    { CEVAL_BIT_OR, "|", CEVAL_PREC_BIT_OR_OPR, CEVAL_BINARY_OPERATOR},
    { CEVAL_BIT_XOR, "^", CEVAL_PREC_BIT_XOR_OPR, CEVAL_BINARY_OPERATOR},
    { CEVAL_BIT_AND, "&", CEVAL_PREC_BIT_AND_OPR, CEVAL_BINARY_OPERATOR},
    { CEVAL_LESSER_S, "<", CEVAL_PREC_RELATIONAL_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_GREATER_S, ">", CEVAL_PREC_RELATIONAL_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_PLUS, "+", CEVAL_PREC_ADDITIVE_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_MINUS, "-", CEVAL_PREC_ADDITIVE_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_POSSIGN, "+", CEVAL_PREC_SIGN_OPRS, CEVAL_UNARY_OPERATOR }, 
    { CEVAL_NEGSIGN, "-", CEVAL_PREC_SIGN_OPRS, CEVAL_UNARY_OPERATOR }, 
    { CEVAL_TIMES, "*", CEVAL_PREC_MULTIPLICATIVE_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_DIVIDE, "/", CEVAL_PREC_MULTIPLICATIVE_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_MODULO, "%", CEVAL_PREC_MULTIPLICATIVE_OPRS , CEVAL_BINARY_OPERATOR },
    { CEVAL_NOT, "!", CEVAL_PREC_NOT_OPRS, CEVAL_UNARY_FUNCTION},
    { CEVAL_BIT_NOT, "~", CEVAL_PREC_NOT_OPRS, CEVAL_UNARY_OPERATOR},

    { CEVAL_NUMBER, "0", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "1", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "2", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "3", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "4", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "5", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "6", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "7", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "8", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
    { CEVAL_NUMBER, "9", CEVAL_PREC_NUMERIC, CEVAL_OTHER },
}; 
#ifndef CEVAL_TOKEN_TABLE_SIZE
#define CEVAL_TOKEN_TABLE_SIZE sizeof(ceval_token_info) / sizeof(ceval_token_info[0])
#endif
// function prototypes for mapping the attributes of various tokens
int ceval_is_binary_opr(ceval_node_id);
int ceval_is_binary_fun(ceval_node_id);
const char * ceval_token_symbol(ceval_node_id);
ceval_node_id ceval_token_id(char * symbol);
double ceval_token_prec(ceval_node_id);

int ceval_is_binary_opr(ceval_node_id id) {
    for(unsigned int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (ceval_token_info[i].id == id && ceval_token_info[i].token_type == CEVAL_BINARY_OPERATOR) {
            return 1;
        }
    }
    return 0;
}
int ceval_is_binary_fun(ceval_node_id id) {
    for(unsigned int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (ceval_token_info[i].id == id && ceval_token_info[i].token_type == CEVAL_BINARY_FUNCTION) {
            return 1;
        }
    }
    return 0;
}
const char * ceval_token_symbol(ceval_node_id id) {
    for(unsigned int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (id == ceval_token_info[i].id) {
            return ceval_token_info[i].symbol;
        }
    }
return "";
}
ceval_node_id ceval_token_id(char * symbol) {
    for(unsigned int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (!strcmp(ceval_token_info[i].symbol, symbol)) {
            return ceval_token_info[i].id;
        }
    }
return CEVAL_WHITESPACE;
}
double ceval_token_prec(ceval_node_id id) {
    for(unsigned int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
        if (id == ceval_token_info[i].id) {
            return ceval_token_info[i].prec;
        }
    }
return 0;
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
