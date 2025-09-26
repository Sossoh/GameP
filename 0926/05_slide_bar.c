
// Windows 콘솔 전용: 방향키로 수평/수직 슬라이드 바 제어
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

static void gotoxy(int x, int y) {
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

static void draw_rectangle(int cols, int rows) {
    // ASCII로 테두리
    putchar('+'); for (int i=0;i<cols;i++) putchar('-'); puts("+");
    for (int r=0;r<rows;r++) {
        putchar('|');
        for (int c=0;c<cols;c++) putchar(' ');
        puts("|");
    }
    putchar('+'); for (int i=0;i<cols;i++) putchar('-'); puts("+");
}

static void draw_horizontal_slide(int x, int y, int length, const char *s) {
    int real_len = length;
    gotoxy(1, y);
    draw_rectangle(real_len+1, 1);
    gotoxy(x+2, y+1);
    printf("%s", s);
    gotoxy(real_len+3, y);
    printf(" x=%2d", x);
}

static void draw_vertical_slide(int x, int y, int length, const char *s) {
    gotoxy(x, 1);
    draw_rectangle(1, length);
    gotoxy(x+3, y+1);
    printf("%s", s);
    gotoxy(x+3, length+2);
    printf(" y=%2d", y);
}

static void move_arrow_key(int key, int *px, int *py, int max_x, int max_y) {
    // 방향키는 0 또는 224 이후 추가 코드가 들어옴
    if (key == 0 || key == 224) key = getch();
    switch (key) {
        case 72: (*py)--; if (*py < 1) *py = 1; break;        // Up
        case 80: (*py)++; if (*py > max_y) *py = max_y; break; // Down
        case 75: (*px)--; if (*px < 1) *px = 1; break;         // Left
        case 77: (*px)++; if (*px > max_x) *px = max_x; break; // Right
        default: break;
    }
}

int main(void) {
    const char *slide = "■";
    int x = 1, y = 1;
    int h_len = 50, v_len = 15;

    printf("슬라이드바 표시\n\n");
    printf("수평 슬라이드바의 길이(최대 70)를 입력하고 Enter> ");
    scanf("%d", &h_len); if (h_len < 5) h_len = 5; if (h_len > 70) h_len = 70;
    printf("수직 슬라이드바의 길이(최대 19)를 입력하고 Enter> ");
    scanf("%d", &v_len); if (v_len < 3) v_len = 3; if (v_len > 19) v_len = 19;
    system("cls");

    int ch = 0;
    do {
        system("cls");
        draw_vertical_slide(1, y, v_len, slide);
        draw_horizontal_slide(x, v_len + 3, h_len, slide);
        printf("\nESC 종료, 방향키 이동");
        ch = getch();
        move_arrow_key(ch, &x, &y, h_len, v_len);
    } while (ch != 27);
    return 0;
}
