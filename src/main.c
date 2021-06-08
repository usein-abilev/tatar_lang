#include "include/lang.h"

int main() {
    char* source = read_file("./lang_sources/common.allah");

    printf("Input data: %s\n\n", source);
    buffer_t* buffer = buffer_init();
    buffer_append(buffer, source);
    printf("Stored data: %s\n\n", buffer->string);

    // lexer_t* lexer = lexer_init(source);
    // token_t* token = lexer_next_token(lexer);
    // printf("token: (%i, %s)\n", token->kind, token->value);

    return 0;
}