#include <stdio.h>
#include <conio.h>
#include "../../utils/console.h"

#define X_MAX 79
#define Y_MAX 24

static void move_arrow_key(int key, int *x, int *y, int x_b, int y_b) {
    switch (key) {
    case 72: *y = (*y <= 1) ? 1 : *y - 1; break;           // 위
    case 75: *x = (*x <= 1) ? 1 : *x - 1; break;           // 좌
    case 77: *x = (*x >= x_b) ? x_b : *x + 1; break;       // 우
    case 80: *y = (*y >= y_b) ? y_b : *y + 1; break;       // 하
    default: break;
    }
}

int main(void) {
    int x = 10, y = 5;
    int key;
    clrscr();
    puts("화살표 키로 A 이동, ESC 종료");
    do {
        gotoxy(x, y);
        printf("A");
        key = getch();
        if (key == 0 || key == 0xE0) key = getch();
        move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
        gotoxy(x, y); printf(" "); // 잔상 지움용 간단 처리
    } while (key != 27);
    return 0;
}
