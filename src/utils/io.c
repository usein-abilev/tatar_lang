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
        *line = malloc(INITIAL_ALLOC);
        *length = INITIAL_ALLOC;
    }

    int current_char;
    while ((current_char = getc(file)) != EOF) {
        if (current_char == '\r') continue;
        read_number++;
        if (read_number > *length) {
            size_t realloc_size = *length + ALLOC_STEP;
            char* temp = realloc(*line, realloc_size + 1);
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

    (*line)[read_number] = '\0';
    return (ssize_t)read_number;
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Could not read file '%s'\n", filename);
        exit(1);
    }

    char* line = NULL;
    char* buffer = calloc(1, sizeof(char));
    buffer[0] = '\0';
    size_t length = 0;
    
    while(read_line(&buffer, &length, file))
    
    fclose(file);

    return buffer;
}
