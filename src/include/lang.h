#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

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

void buffer_destroy (buffer_t* buffer);


// helpers.c
bool is_whitespace(char c);

bool is_line_terminate(char c);

bool is_eof(char c);

bool is_identifier_start(char c);

// token.c
typedef enum TokenKind {
    eof = INT_MIN,
    symbol, identifier, number,
    plus, minus,
    slash, star
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
} lexer_t;

lexer_t* lexer_init(char* source);

token_t* lexer_next_token(lexer_t* lexer);

// io.c
char* read_file(const char* filename);