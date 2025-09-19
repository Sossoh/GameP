
#include "stack.h"
#include <stdlib.h>

void stack_init(Stack* s, size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = 8;
    s->data = (int*)malloc(sizeof(int) * initial_capacity);
    s->size = 0;
    s->capacity = s->data ? initial_capacity : 0;
}

void stack_free(Stack* s) {
    free(s->data);
    s->data = NULL;
    s->size = s->capacity = 0;
}

int stack_is_empty(const Stack* s) {
    return s->size == 0;
}

static int stack_reserve(Stack* s, size_t new_cap) {
    if (new_cap <= s->capacity) return 1;
    int* p = (int*)realloc(s->data, sizeof(int) * new_cap);
    if (!p) return 0;
    s->data = p;
    s->capacity = new_cap;
    return 1;
}

void stack_push(Stack* s, int value) {
    if (s->size == s->capacity) {
        size_t new_cap = s->capacity ? s->capacity * 2 : 8;
        if (!stack_reserve(s, new_cap)) return; // 메모리 부족 시 무시
    }
    s->data[s->size++] = value;
}

int stack_pop(Stack* s, int* out) {
    if (s->size == 0) return 0;
    int v = s->data[--s->size];
    if (out) *out = v;
    return 1;
}
