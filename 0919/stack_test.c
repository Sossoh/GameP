
#include <stdio.h>
#include "stack.h"

int main(void) {
    Stack s;
    stack_init(&s, 0);

    // push 1..5
    for (int i = 1; i <= 5; ++i) {
        stack_push(&s, i);
        printf("push %d, size=%zu\n", i, s.size);
    }

    // pop 6번 시도
    for (int k = 0; k < 6; ++k) {
        int v;
        if (stack_pop(&s, &v)) {
            printf("pop -> %d, size=%zu\n", v, s.size);
        } else {
            printf("pop 실패(스택 비어있음)\n");
        }
    }

    stack_free(&s);
    return 0;
}
