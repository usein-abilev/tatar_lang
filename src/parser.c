#include "include/lang.h"

parser_t* parser_init(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(parser_t));
    parser->lexer = lexer;
    parser->current_token = lexer_next_token(lexer);
    parser->previous_token = parser->current_token;
    parser->offset = 0;

    return parser;
}

void parser_consume(parser_t* parser, int kind) {
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