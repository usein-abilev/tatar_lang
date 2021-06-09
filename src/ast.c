#include "include/lang.h"

ast_t* ast_init(int kind) {
    ast_t* ast = calloc(1, sizeof(ast_t));
    ast->type = kind;

    // variable definition
    ast->variable_name = (void*)0;
    ast->variable_value = (void*)0;

    // binary expression
    ast->left_operand = (void*)0;
    ast->right_operand = (void*)0;
    ast->operator_kind = (void*)0;

    // compound 
    ast->compound_value = (void*)0;
    ast->compound_size = 0;

    return ast;
}