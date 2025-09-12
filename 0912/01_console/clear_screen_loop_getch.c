#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../../utils/console.h"

int main(void) {
    for (int j = 1; j <= 9; j++) {
        clrscr();
        for (int i = 1; i <= 9; i++) {
            printf("%d*%d=%d\n", j, i, j * i);
        }
        printf("아무키나 누르시오.\n");
        getch();
    }
    return 0;
}
