#ifndef CEVAL
#define CEVAL

#include "./core/parser.h"
#include "./core/evaluator.h"

// functions accessible from main() 
// - double ceval_result(char * inp) returns the result of valid math expression stored as a char array `inp`
// - void ceval_tree(char * inp) prints the parse tree for the input expression `inp`
// - define CEVAL_EPSILON (default value : 1e-2), CEVAL_DELTA (default value : 1e-6) and CEVAL_MAX_DIGITS (default value : 15) manually before the include directive

double ceval_result(char * expr) {
    void * tree = ceval_make_tree(expr);
    double result = ceval_evaluate_tree(tree);
    ceval_delete_tree(tree);
    #ifdef CEVAL_ERROR
        printf("Error encountered\n");
        #undef CEVAL_ERROR
        return 0;
    #endif
    return result;
}
void ceval_tree(char * expr) {
    void * tree = ceval_make_tree(expr);
    #ifdef CEVAL_ERROR
        printf("Error encountered\n");
        #undef CEVAL_ERROR
        return;
    #endif
    ceval_print_tree(tree);
    ceval_delete_tree(tree);
}

#ifdef CEVAL_CXX
    double ceval_result(std::string expr) {
        return ceval_result((char * ) expr.c_str());
    }
    void ceval_tree(std::string expr) {
        ceval_tree((char * ) expr.c_str());
    }
#endif
#endif
