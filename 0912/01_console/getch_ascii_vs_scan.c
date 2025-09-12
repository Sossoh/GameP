#include <stdio.h>
#include <conio.h>

int main(void) {
    int chr;
    puts("키를 누르세요. ESC 종료");
    do {
        chr = getch();
        if (chr == 0 || chr == 0xE0) {   // 확장키 프리픽스
            chr = getch();
            printf("확장키 code=%d\n", chr);
        } else {
            printf("아스키 code=%d\n", chr);
        }
    } while (chr != 27); // ESC
    return 0;
}
