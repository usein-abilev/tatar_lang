#include "include/lang.h"

lexer_t* lexer_init(char* const source) {
    lexer_t* lexer = calloc(1, sizeof(lexer_t));
    lexer->offset = 0;
    lexer->source = source;
    lexer->current_buffer = buffer_init();
    lexer->current_char = lexer->source[lexer->offset];

    return lexer;
}

static char lexer_peek_char(lexer_t* lexer, int offset) {
    return lexer->source[lexer->offset + offset];
}

static void lexer_advance(lexer_t* lexer) {
    lexer->offset++;
    lexer->current_char = lexer_peek_char(lexer, 0);
}

static token_t* lexer_consume_single(lexer_t* lexer, int kind) {
    char c = lexer->current_char;
    lexer_advance(lexer);
    return token_init((char[2]) { c, 0 }, kind);
}

static char* lexer_parse_number(lexer_t* lexer) {
    do {
        buffer_add(lexer->current_buffer, lexer->current_char);
        lexer_advance(lexer);
    } while (isdigit(lexer->current_char) && !is_eof(lexer->current_char));

    return lexer->current_buffer->string;
}

static char* lexer_parse_string_literal(lexer_t* lexer) {
    if (lexer->current_char != '"') {
        tatar_panic("Unable to parse string literal");
    }

    lexer_advance(lexer);

    while (lexer->current_char != '"' && !is_eof(lexer->current_char)) {
        if (is_line_terminate(lexer->current_char)) {
            tatar_panic("Unexpected line termination");
            break;
        }

        buffer_add(lexer->current_buffer, lexer->current_char);
        lexer_advance(lexer);
    }

    return lexer->current_buffer->string;
}

static char* lexer_parse_identifier(lexer_t* lexer) {
    if (!is_identifier_part(lexer->current_char)) {
        tatar_panic("Unable to parse identifier.");
    }

    do {
        buffer_add(lexer->current_buffer, lexer->current_char);
        lexer_advance(lexer);
    } while (is_identifier_part(lexer->current_char));

    return lexer->current_buffer->string;
}

token_t* lexer_next_token(lexer_t* lexer) {
    buffer_clear(lexer->current_buffer);

    while (lexer->current_char != '\0') {
        if (is_line_terminate(lexer->current_char) || is_whitespace(lexer->current_char)) {
            lexer_advance(lexer);
            continue;
        }

        if (lexer->current_char == '"') {
            lexer_parse_string_literal(lexer);
            lexer_advance(lexer);

            return lexer->current_token = token_init(lexer->current_buffer->string, TOKEN_STRING);
        }

        if (is_identifier_start(lexer->current_char)) {
            lexer_parse_identifier(lexer);
            lexer_advance(lexer);

            int kind;
            char* id = lexer->current_buffer->string;

            if (strcmp(id, "let") == 0) kind = TOKEN_LET;
            else if (strcmp(id, "const") == 0) kind = TOKEN_CONST;
            else if (strcmp(id, "fun") == 0) kind = TOKEN_FUN;
            else if (strcmp(id, "for") == 0) kind = TOKEN_FOR;
            else if (strcmp(id, "while") == 0) kind = TOKEN_WHILE;
            else if (strcmp(id, "return") == 0) kind = TOKEN_RETURN;
            else kind = TOKEN_SYMBOL;
            return lexer->current_token = token_init(id, kind);
        }

        if (isdigit(lexer->current_char)) {
            lexer_parse_number(lexer);
            lexer_advance(lexer);

            return lexer->current_token = token_init(lexer->current_buffer->string, TOKEN_NUMBER);
        }

        switch (lexer->current_char) {
            case '+': return lexer_consume_single(lexer, TOKEN_PLUS);
            case '-': return lexer_consume_single(lexer, TOKEN_MINUS);
            case '/': return lexer_consume_single(lexer, TOKEN_SLASH);
            case '*': return lexer_consume_single(lexer, TOKEN_STAR);
            case ';': return lexer_consume_single(lexer, TOKEN_SEMICOLON);
            case '=': return lexer_consume_single(lexer, TOKEN_EQUAL);
            case '(': return lexer_consume_single(lexer, TOKEN_LEFT_PARENT);
            case ')': return lexer_consume_single(lexer, TOKEN_RIGHT_PARENT);
            case '[': return lexer_consume_single(lexer, TOKEN_RIGHT_BRACKET);
            case ']': return lexer_consume_single(lexer, TOKEN_LEFT_BRACKET);
            case '>': return lexer_consume_single(lexer, TOKEN_GT);
            case '<': return lexer_consume_single(lexer, TOKEN_LT);
            case '{': return lexer_consume_single(lexer, TOKEN_RIGHT_BRACE);
            case '}': return lexer_consume_single(lexer, TOKEN_LEFT_BRACE);
        }

        printf("[error]: Unexpected char: '%c' (code: %i)\n", (char)lexer->current_char, lexer->current_char);
        exit(1);
    }

    lexer->current_token = token_init('\0', TOKEN_EOF);
    return lexer->current_token;
}

void lexer_destroy(lexer_t* lexer) {
    if (!lexer) return;

    buffer_destroy(lexer->current_buffer);
    free(lexer);
}