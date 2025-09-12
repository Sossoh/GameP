#include <stdio.h>
#include "../../utils/console.h"

int main(void) {
    for (int i = 1; i <= 9; i++) {
        gotoxy(35, 5 + i);
        printf("%d*%d=%2d", 3, i, 3 * i);
    }
    printf("\n");
    return 0;
}
