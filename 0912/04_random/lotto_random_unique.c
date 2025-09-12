#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void) {
    int lotto[6];
    srand((unsigned)time(NULL));
    for (int i = 0; i < 6; i++) {
        int v = rand() % 45 + 1;
        bool dup = false;
        for (int j = 0; j < i; j++) {
            if (lotto[j] == v) { dup = true; break; }
        }
        if (dup) { i--; continue; }
        lotto[i] = v;
    }
    for (int i = 0; i < 6; i++)
        printf("%2d\n", lotto[i]);
    return 0;
}
