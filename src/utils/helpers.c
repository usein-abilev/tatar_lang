#include "../include/lang.h"

bool is_whitespace(char c) {
    return c == 10 || c == 32;
}

bool is_line_terminate(char c) {
    return c == '\r' || c == '\n';
}

bool is_eof(char c) {
    return c == '\0';
}

bool is_identifier_start(char c) {
    return c == '$' || c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}