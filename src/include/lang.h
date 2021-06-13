#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

// aliases 
typedef int i32;
typedef char i8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long u64;
typedef long long ssize_t;

// vector.c 
typedef struct Vector {
    void** data;
    size_t size;
    size_t capacity;
} vector_t;

vector_t* vector_init();
vector_t* vector_init(int init_capacity);
void vector_push(vector_t* vector, void* data);
void vector_clear(vector_t* vector);
void vector_destory(vector_t* vector);

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
    TOKEN_SYMBOL,

    // keywords 
    TOKEN_LET, TOKEN_CONST, TOKEN_FUN,
    TOKEN_RETURN, TOKEN_WHILE,
    TOKEN_FOR,

    // literals
    TOKEN_NUMBER, TOKEN_STRING,

    // punctuators
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
int token_get_precedence(int kind);

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
typedef struct ast_node {
    enum {
        AST_LITERAL,
        AST_VARIABLE_DEFINITION,
        AST_BINARY_EXPRESSION,
        AST_UNARY_EXPRESSION,
        AST_BLOCK_STATEMENT
    } kind;

    union {
        struct {
            char* value;
            char* raw;
        } literal;

        struct {
            bool is_const;
            char* name;
            struct ast_node* declaration;
        } variable_definition;

        struct {
            int operator;
            struct ast_node* left;
            struct ast_node* right;
        } binary_expression;

        struct {
            int operator;
            struct ast_node* expression;
        } unary_expession;

        struct {
            vector_t* body;
        } block_statement;
    }  data;
} ast_node_t;

ast_node_t* ast_make_literal(char* value, char* raw);
ast_node_t* ast_make_variable(
    bool is_const,
    char* name,
    ast_node_t* init
);
ast_node_t* ast_make_binary_exp(
    int operator,
    ast_node_t* left,
    ast_node_t* right
);
ast_node_t* ast_make_unary_exp(int operator, ast_node_t* expression);
ast_node_t* ast_make_block_stmt(vector_t* body);

// parser.c
typedef struct Parser {
    int offset;
    lexer_t* lexer;
    token_t* current_token;
    token_t* previous_token;
} parser_t;

parser_t* parser_init(lexer_t* lexer);
ast_node_t* parser_parse(parser_t* parser);