#include "../include/lang.h"

#define INITIAL_SIZE 8

static void buffer_realloc(buffer_t* buffer, int new_size) {
    if (new_size <= 0) {
        new_size = buffer->allocated_size * 2;
    }

    buffer->string = realloc(buffer->string, new_size);
    buffer->allocated_size = new_size;
}

buffer_t* buffer_init() {
    buffer_t* buffer = calloc(1, sizeof(buffer_t));
    buffer->string = malloc(INITIAL_SIZE);
    buffer->allocated_size = INITIAL_SIZE;
    buffer->length = 0;

    return buffer;
}

void buffer_add(buffer_t* buffer, char s) {
    if (buffer->string[buffer->length + 1] == '\0') {
        buffer_realloc(buffer, 0);
    }

    buffer->string[buffer->length++] = s;
}

void buffer_append(buffer_t* buffer, const char* data) {
    int data_length = strlen(data);

    if (buffer->length + data_length > buffer->allocated_size) {
        buffer_realloc(buffer, (buffer->length + data_length) * 2);
    }
    
    strcat(buffer->string, data);
}

void buffer_destroy(buffer_t* buffer) {
    free(buffer->string);
    free(buffer);
}

