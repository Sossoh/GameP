
#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct {
    int* data;
    size_t size;      // 현재 원소 수
    size_t capacity;  // 할당 크기
} Stack;

void stack_init(Stack* s, size_t initial_capacity);
void stack_free(Stack* s);
int  stack_is_empty(const Stack* s);
void stack_push(Stack* s, int value);   // 필요 시 자동 확장
int  stack_pop(Stack* s, int* out);     // 비어있으면 0, 성공 1

#endif // STACK_H
