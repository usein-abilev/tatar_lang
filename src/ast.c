#include "include/lang.h"


ast_node_t* ast_make_literal(char* value, char* raw) {
    ast_node_t* node = calloc(1, sizeof(ast_node_t));
    node->kind = AST_LITERAL;
    node->data.literal.value = value;
    node->data.literal.raw = raw;

    return node;
}

ast_node_t* ast_make_variable(
    bool is_const,
    char* name,
    ast_node_t* init
) {
    ast_node_t* node = calloc(1, sizeof(ast_node_t));
    node->kind = AST_VARIABLE_DEFINITION;
    node->data.variable_definition.is_const = is_const;
    node->data.variable_definition.name = name;
    node->data.variable_definition.declaration = init;

    return node;
}

ast_node_t* ast_make_binary_exp(
    int operator,
    ast_node_t* left,
    ast_node_t* right
) {
    ast_node_t* node = calloc(1, sizeof(ast_node_t));
    node->kind = AST_BINARY_EXPRESSION;
    node->data.binary_expression.operator = operator;
    node->data.binary_expression.left = left;
    node->data.binary_expression.right = right;

    return node;
}

ast_node_t* ast_make_unary_exp(int operator, ast_node_t* expression) {
    ast_node_t* node = calloc(1, sizeof(ast_node_t));
    node->kind = AST_UNARY_EXPRESSION;
    node->data.unary_expession.operator = operator;
    node->data.unary_expession.expression = expression;

    return node;
}

ast_node_t* ast_make_block_stmt(vector_t* body) {
    ast_node_t* node = calloc(1, sizeof(ast_node_t));
    node->kind = AST_BLOCK_STATEMENT;
    node->data.block_statement.body = body;

    return node;
}