#include <stdio.h>

int main(void) {
    unsigned char a = 0xA6, b[7];
    for (int i = 1; i < 7; i++) b[i] = 0xA0 + i;
    printf("%c%c", a, b[3]);
    printf("%c%c", a, b[4]);
    printf("\n");
    printf("%c%c", a, b[6]);
    printf("%c%c", a, b[5]);
    printf("\n");
    return 0;
}
