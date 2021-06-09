#include "../include/lang.h"

static ssize_t read_line(char** line, size_t* length, FILE* file) {
    const size_t INITIAL_ALLOC = 16;
    const size_t ALLOC_STEP = 16;
    size_t read_number = 0;

    if (!line || !length || !file) {
        errno = EINVAL;
        return -1;
    }

    if (!*line) {
        *line = calloc(1, INITIAL_ALLOC);
        *length = INITIAL_ALLOC;
    }

    int current_char;
    while ((current_char = getc(file)) != EOF) {
        read_number++;

        if (read_number > *length) {
            int realloc_size = *length + ALLOC_STEP;
            char* temp = (char*)realloc(*line, realloc_size + 1);

            if (temp == NULL) {
                errno = ENOMEM;
                return -1;
            }

            *line = temp;
            *length = realloc_size;
        }

        if (LLONG_MAX < *length) {
            errno = ERANGE;
            return -1;
        }

        (*line)[read_number - 1] = (char)current_char;

        if (current_char == '\n') break;
    }

    if (current_char == EOF) {
        errno = 0;
        return -1;
    }

    (*line)[read_number] = '\0';
    return (ssize_t)read_number;
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Could not read file '%s'\n", filename);
        exit(1);
    }

    int buffer_size = 16;
    char* buffer = calloc(1, buffer_size * sizeof(*buffer));

    char* line = NULL;

    size_t allocated_line_size = 0;
    ssize_t current_line_size = 0;

    size_t total_size = 0;

    while (1) {
        current_line_size = read_line(&line, &allocated_line_size, file);
        if (current_line_size != EOF) total_size += current_line_size;

        if (total_size > buffer_size) {
            buffer_size += total_size;
            char* temp = realloc(buffer, buffer_size + 1);

            if (temp == NULL) {
                errno = ENOMEM;
                exit(1);
            }

            buffer = temp;
        }
        if (line != NULL) {
            strncat(buffer, line, current_line_size);
        }

        if (current_line_size == EOF) break;
    }

    fclose(file);

    if (line) {
        free(line);
    }

    return buffer;
}

void tatar_panic(const char* const data) {
    printf("[panic]: %s\n", data);
    exit(1);
}