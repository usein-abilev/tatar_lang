#include "../include/lang.h"
#define INITIAL_CAPACITY 8

static void vector_extend(vector_t* vector, int need);

vector_t* vector_init(int init_capacity) {
    if (init_capacity <= 0) {
        tatar_panic("invalid inital capacity for vector");
    }

    int capacity = MAX(INITIAL_CAPACITY, init_capacity);

    vector_t* vector = calloc(1, sizeof(vector_t));
    vector->data = calloc(1, capacity * sizeof(vector->data));
    vector->capacity = capacity;
    vector->size = 0;

    return vector;
}

void vector_push(vector_t* vector, void* data) {
    if (!vector) {
        tatar_panic("invalid input data for vector_push");
    }

    if (vector->capacity <= vector->size + 1) {
        vector_extend(vector, 1);
    }

    vector->data[vector->size++] = data;
}

void vector_clear(vector_t* vector) {
    for (int i = 0; i < vector->size; i++) {
        vector->data[i] = NULL;
    }

    vector->size = 0;
}

void vector_destory(vector_t* vector) {
    free(vector->data);
    free(vector);
}

static void vector_extend(vector_t* vector, int need) {
    if (vector == NULL || need <= 0)
        tatar_panic("invalid input data for vector_extend");

    int new_capacity = MAX(vector->capacity + INITIAL_CAPACITY, need);
    void** temp = realloc(vector->data, new_capacity * sizeof(vector->data));

    if (temp == NULL) {
        tatar_panic("re-alloc panic.");
    }

    vector->data = temp;
    vector->capacity = new_capacity;
}