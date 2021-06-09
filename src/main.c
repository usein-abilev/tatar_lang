#include "include/lang.h"

int main() {
    char* source = read_file("./lang_sources/common.allah");
    printf("Compiling:\n\n%s\n\n", source);

    // printf("Stored data: %s\n\n", buffer->string);

    // lexer_t* lexer = lexer_init(source);
    // token_t* token = lexer_next_token(lexer);
    // printf("token: (%i, %s)\n", token->kind, token->value);
    free(source);

    return 0;
}