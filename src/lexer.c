#include "include/lang.h"

lexer_t* lexer_init(char* source) {
    lexer_t* lexer = calloc(1, sizeof(lexer_t));
    lexer->offset = 0;
    lexer->source = source;
    lexer->current_char = lexer->source[lexer->offset];

    return lexer;
}

static char lexer_peek_char(lexer_t* lexer, int offset) {
    return lexer->source[lexer->offset + offset];
}

static void lexer_advance(lexer_t* lexer) {
    lexer->current_char = lexer_peek_char(lexer, 0);
    lexer->offset++;
}

static char* lexer_parse_identifier(lexer_t* lexer, char s) {
    buffer_t* buffer = buffer_init();
    buffer_add(buffer, s);

    while (is_identifier_start(lexer->current_char) || (lexer->current_char >= '0' && lexer->current_char <= '9')) {
        buffer_add(buffer, lexer->current_char);
        lexer_advance(lexer);
    }

    char* data = buffer->string;
    buffer_destroy(buffer);
    
    return data;
}

token_t* lexer_next_token(lexer_t* lexer) {
    while (lexer->current_char != '\0') {
        if (is_whitespace(lexer->current_char)) {
            lexer_advance(lexer);
            continue;
        }

        if (is_identifier_start(lexer->current_char)) {
            char* value = lexer_parse_identifier(lexer, lexer->current_char);
            return token_init(value, identifier);
        }

        printf("current char: %c\n", lexer->current_char);

        lexer_advance(lexer);
    }

    lexer->current_token = token_init('\0', eof);
    return lexer->current_token;
}
