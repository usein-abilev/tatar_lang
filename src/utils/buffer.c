#include "../include/lang.h"

#define INITIAL_SIZE 8
#define ALLOCATE_SIZE 32

static void buffer_panic(buffer_t* buffer, const char* const message, int code) {
    printf(message + '\n');
    buffer_destroy(buffer);
    exit(code);
}

static void buffer_realloc(buffer_t* buffer, int new_size) {
    new_size += buffer->allocated_size + buffer->length + ALLOCATE_SIZE;

    if (buffer->string == NULL) {
        return buffer_panic(buffer, "Uninitialized string of buffer.", EINVAL);
    }

    char* result = realloc(buffer->string, new_size);
    if (result == NULL) {
        return buffer_panic(buffer, "Memory re-allocation error.", ENOMEM);
    }

    buffer->string = result;
    buffer->allocated_size = new_size;
}

static bool buffer_reached(buffer_t* buffer, int append_size) {
    return buffer->length + append_size + 1 > buffer->allocated_size;
}

buffer_t* buffer_init() {
    buffer_t* buffer = calloc(1, sizeof(buffer_t));
    buffer->string = calloc(1, INITIAL_SIZE);
    buffer->allocated_size = INITIAL_SIZE;
    buffer->length = 0;

    return buffer;
}

void buffer_add(buffer_t* buffer, const char s) {
    if (!buffer) {
        return buffer_panic(buffer, "buffer_add: invalid params. The buffer is not initialized", EINVAL);
    }

    if (buffer_reached(buffer, 0)) {
        buffer_realloc(buffer, 0);
    }

    buffer->string[buffer->length++] = s;
    buffer->string[buffer->length] = '\0';
}

void buffer_append(buffer_t* buffer, const char* data) {
    if (!buffer || !data) {
        return buffer_panic(buffer, "buffer_append: invalid params. The buffer or data is not initialized", EINVAL);
    }

    int data_length = strlen(data);

    if (buffer_reached(buffer, data_length)) {
        buffer_realloc(buffer, data_length);
    }

    strncat(buffer->string, data, data_length);
    buffer->length += data_length;
}

void buffer_destroy(buffer_t* buffer) {
    free(buffer->string);
    free(buffer);
}