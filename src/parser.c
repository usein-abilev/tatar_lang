#include "include/lang.h"

static void parser_consume(parser_t* parser, int kind);
static void parser_expect(parser_t* parser, int kind);
static ast_node_t* parser_parse_variable(parser_t* parser);
static ast_node_t* parser_parse_expression(parser_t* parser);
static void syntax_error(parser_t* parser) {

}

void print_parser_state(parser_t* parser) {
    printf("\n----- Parser State -----\n");
    printf(
        "Current token: (%i) -> '%s'\n",
        parser->current_token->kind,
        parser->current_token->value
    );
    printf(
        "Previos token: (%i) -> '%s'\n",
        parser->previous_token->kind,
        parser->previous_token->value
    );
    printf("------------------------\n\n");
}

parser_t* parser_init(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(parser_t));
    parser->lexer = lexer;
    parser->current_token = lexer_next_token(lexer);
    parser->previous_token = parser->current_token;
    parser->offset = 0;

    return parser;
}

ast_node_t* parser_parse(parser_t* parser) {
    vector_t* statements = vector_init(32);
    ast_node_t* root = ast_make_block_stmt(statements);

    while (parser->current_token->kind != TOKEN_EOF) {
        switch (parser->current_token->kind) {
            case TOKEN_LET:
                vector_push(statements, parser_parse_variable(parser));
                break;

            default: {
                    printf("[error]: Unexpected token: '%s' (type: %i)\n", parser->current_token->value, parser->current_token->kind);
                    exit(EINVAL);
                }
        }
    }

    return root;
}

static ast_node_t* parser_parse_variable(parser_t* parser) {
    bool constant = false;
    switch (parser->current_token->kind) {
        case TOKEN_CONST:
            parser_consume(parser, TOKEN_CONST);
            parser_consume(parser, TOKEN_LET);
            constant = true;

            break;

        default:
            parser_consume(parser, TOKEN_LET);
            constant = false;
    }

    parser_consume(parser, TOKEN_SYMBOL);

    char* name = parser->previous_token->value;

    parser_consume(parser, TOKEN_EQUAL);

    ast_node_t* expression = parser_parse_expression(parser);
    parser_consume(parser, TOKEN_SEMICOLON);
    return ast_make_variable(false, name, expression);
}

static ast_node_t* parser_parse_expression(parser_t* parser) {
    // todo
}

static void parser_consume(parser_t* parser, int kind) {
    if (parser->current_token->kind == kind) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexer_next_token(parser->lexer);
        return;
    }

    printf(
        "Unexpected token: '%s' (type: %d)\n",
        parser->current_token->value,
        parser->current_token->kind
    );

    exit(EINVAL);
}

static void parser_expect(parser_t* parser, int kind) {
    token_t* token = lexer_next_token(parser->lexer);

    if (token->kind != kind) {
        printf(
            "Expected token '%s' but found '%s'",
            kind,
            token->value
        );

        exit(EINVAL);
    }

    parser->previous_token = parser->current_token;
    parser->current_token = token;
}