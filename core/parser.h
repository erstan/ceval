#ifndef CEVAL_PARSER
#define CEVAL_PARSER
#include "./tokens.h"
#include "./functions.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>

void * ceval_make_tree(char * );
ceval_node * ceval_insert_node(ceval_node * , ceval_node, int);
void ceval_print_tree(const void * );
void ceval_print_node(const ceval_node * , int);
void ceval_delete_node(ceval_node * );
void ceval_delete_tree(void * );

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
            ceval_is_binay_fun(current -> id)) {
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
        ceval_token_prec(CEVAL_OPENPAR),
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
        if (c == '\0') break;
        int token_found = -1;
        char token[50];
        int len;
        for (int i = 0; i < CEVAL_TOKEN_TABLE_SIZE; i++) {
            strcpy(token, ceval_token_info[i].symbol);
            len = strlen(token);
            if (!memcmp(expression - 1, token, len)) {
                token_found = ceval_token_info[i].id;
                isRightAssoc = ( token_found == CEVAL_POW || token_found == CEVAL_CLOSEPAR ) ? 1 : 0;
                break;
            }
        }
        // if token is found
        if (token_found > -1) {
            //printf("token: %d\n", token_found);
            // check if the token is a binary operator
            if (ceval_is_binary_opr(token_found)) {
                // a binary operator must be preceded by a number, a numerical constant, a clospar, or a factorial
                if (previous_id == CEVAL_NUMBER ||
                    previous_id == CEVAL_CONST_PI ||
                    previous_id == CEVAL_CONST_E ||
                    previous_id == CEVAL_CLOSEPAR) {
                    // other tokens (other than CEVAL_NUMBER, CEVAL_CLOSEPAR) are allowed only before '+'s or '-'s
                    expression = expression + (len - 1);
                    node.id = token_found;
                    node.pre = ceval_token_prec(node.id);
                } else {
                    // if the operator is not preceded by a number, a numerical constant, a closepar, or a factorial, then check if the 
                    // character is a sign ('+' or '-')
                    if (c == '+') {
                        node.id = CEVAL_POSSIGN;
                        node.pre = ceval_token_prec(node.id);
                    } else if (c == '-') {
                        node.id = CEVAL_NEGSIGN;
                        node.pre = ceval_token_prec(node.id);
                    } else {
                        // if it is not a sign, then it must be a misplaced character
                        printf("[ceval]: Misplaced '%c' sign\n", c);
                        return NULL;
                    }
                }
            } else if (token_found == CEVAL_NUMBER){
                // if the token is a number, then store it in an array
                node.pre = ceval_token_prec(CEVAL_NUMBER);
                int i;
                char number[CEVAL_MAX_DIGITS];
                for (i = 0; i + 1 < sizeof(number);) {
                    number[i++] = c;
                    c = * expression;
                    if ('0' <= c && c <= '9' || c == '.')
                        expression++;
                    else 
                        break;
                }
                number[i] = '\0';
                //copy the contents of the number array at &node.number
                sscanf(number, "%lf", & node.number);
                node.id = CEVAL_NUMBER;
                goto END;
            } else if (token_found == CEVAL_WHITESPACE) {
                // skip whitespace
                continue;
            } else {
                // for any other token
                expression = expression + (len - 1);
                node.id = token_found;
                node.pre = ceval_token_prec(node.id);
                if (node.id == CEVAL_CONST_PI || node.id == CEVAL_CONST_E) {
                    node.number = (node.id == CEVAL_CONST_PI) ? CEVAL_PI : CEVAL_E;
                }
            }
        } else {
            // if the token is not found in the token table
            printf("[ceval]: Unknown token '%c'.\n", c);
            ceval_delete_tree(root.right);
            root.right = NULL;
            break;
        }
        END: ;
        previous_id = node.id;
        current = ceval_insert_node(current, node, isRightAssoc);
    }
    if (root.right) root.right -> parent = NULL;
    return root.right;
}
void ceval_print_node(const ceval_node * node, int indent) {
    int i;
    char number[CEVAL_MAX_DIGITS];
    const char * str;
    if (!node) return;
    ceval_print_node(node -> right, indent + 4);
    if (node -> id == CEVAL_NUMBER) {
        if ((long) node -> number == node -> number) //for integers, skip the trailing zeroes
            sprintf(number, "%.0f", node -> number);
        else sprintf(number, "%.2f", node -> number);
        str = number;
    } else {
        str = ceval_token_symbol(node -> id);
    }
    for (i = 0; i < indent; i++) {
        putchar(' ');
        putchar(' ');
    }
    printf("%s\n", str);
    ceval_print_node(node -> left, indent + 4);
}
void ceval_print_tree(const void * tree) {
    ceval_print_node((const ceval_node * ) tree, 0);
}
#endif