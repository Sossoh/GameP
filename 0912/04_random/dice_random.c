#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));
    for (int i = 1; i <= 10; i++)
        printf("%2d: %d\n", i, rand() % 6 + 1);
    return 0;
}
