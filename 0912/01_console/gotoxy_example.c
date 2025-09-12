#include <stdio.h>
#include "../../utils/console.h"  // gotoxy, clrscr

int main(void) {
    gotoxy(2, 4);
    printf("Hello");
    gotoxy(40, 20);
    printf("Hello");
    return 0;
}
