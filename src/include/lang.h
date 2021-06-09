#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

// aliases 
typedef int i32;
typedef char i8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long u64;
typedef long long ssize_t;


// buffer.c
typedef struct Buffer {
    char* string;
    u8 length;
    u32 allocated_size;
} buffer_t;

buffer_t* buffer_init();

void buffer_add(buffer_t* buffer, const char s);

void buffer_append(buffer_t* buffer, const char* data);

void buffer_clear(buffer_t* buffer);

void buffer_destroy(buffer_t* buffer);


// helpers.c
bool is_whitespace(char c);

bool is_line_terminate(char c);

bool is_eof(char c);

bool is_identifier_start(char c);

bool is_identifier_part(char c);

// token.c
typedef enum TokenKind {
    TOKEN_EOF = INT_MIN,
    TOKEN_SYMBOL, TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_PLUS, TOKEN_MINUS,
    TOKEN_SLASH, TOKEN_STAR,
    TOKEN_EQUAL, TOKEN_SEMICOLON,
    TOKEN_GT, TOKEN_LT,
    TOKEN_RIGHT_PARENT, TOKEN_LEFT_PARENT,
    TOKEN_RIGHT_BRACKET, TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACE, TOKEN_LEFT_BRACE
} token_kind_t;

typedef struct Token {
    char* value;
    token_kind_t kind;
} token_t;

token_t* token_init(char* value, int kind);

// lexer.c
typedef struct Lexer {
    int offset;
    char* source;
    char current_char;
    token_t* current_token;
    buffer_t* current_buffer;
} lexer_t;

lexer_t* lexer_init(char* source);

token_t* lexer_next_token(lexer_t* lexer);

void lexer_destroy(lexer_t* lexer);

// io.c
char* read_file(const char* filename);

void tatar_panic(const char* const data);


// ast.c

typedef struct AST {
    enum {
        AST_VARIABLE_DEFINITION,
        AST_BINARY_EXPRESSION,
        AST_COMPOUND
    } type;

    // variable definition
    char* variable_name;
    ast_t* variable_value;

    // binary expression
    int left_operand;
    int right_operand;
    int operator_kind;

    // compound 
    ast_t** compound_value;
    size_t compound_size;
} ast_t;

ast_t* ast_init(int kind);

// parser.c

typedef struct Parser {
    int offset;
    lexer_t* lexer;
    token_t* current_token;
    token_t* previous_token;
} parser_t;

parser_t* parser_init(lexer_t* lexer);
void parser_consume(parser_t* parser, int kind);

