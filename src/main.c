#include "include/lang.h"

int main() {
    char* source = read_file("./lang_sources/common.allah");
    printf("Compiling:\n\n%s\n\n", source);

    lexer_t* lexer = lexer_init(source);    
    parser_t* parser = parser_init(lexer);
    
    lexer_destroy(lexer);
    free(source);

    return 0;
}