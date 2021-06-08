#include "include/lang.h"

token_t* token_init(char* value, int kind) {
    token_t* token = calloc(1, sizeof(token_t));
    token->value = value;
    token->kind = kind;

    return token;
}