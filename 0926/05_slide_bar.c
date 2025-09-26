// Windows 콘솔 전용: 방향키로 수평/수직 슬라이드 바 제어(수정본)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

static void gotoxy(int x, int y) {
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

static void draw_rectangle(int cols, int rows) {
    // 상단
    putchar('+'); for (int i=0;i<cols;i++) putchar('-'); puts("+");
    // 내부
    for (int r=0;r<rows;r++) {
        putchar('|');
        for (int c=0;c<cols;c++) putchar(' ');
        puts("|");
    }
    // 하단
    putchar('+'); for (int i=0;i<cols;i++) putchar('-'); puts("+");
}

// 수평 슬라이드 바: 폭 length, y 행에 표시, x 위치에 포인터
static void draw_horizontal_slide(int x, int y, int length, const char *s) {
    int inner = length;                 // 내부 폭
    gotoxy(1, y);                       // y행에 프레임
    draw_rectangle(inner+1, 1);         // 내부 1행
    // 포인터(프레임 내부 한 칸 띄고 오프셋 보정)
    int px = x; if (px < 1) px = 1; if (px > inner) px = inner;
    gotoxy(px + 1 + 1, y + 1);          // 좌측테두리(1) + 내부오프셋 +1
    printf("%s", s);
    gotoxy(inner + 3, y);               // 상태표시
    printf(" x=%2d ", px);
}

// 수직 슬라이드 바: 높이 length, x 열에 표시, y 위치에 포인터
static void draw_vertical_slide(int x, int y, int length, const char *s) {
    // 프레임은 화면 상단부터 고정
    gotoxy(x, 1);
    draw_rectangle(1, length);          // 내부 높이 length
    // 포인터를 프레임 내부 중앙 열(x+1)에 표시
    int py = y; if (py < 1) py = 1; if (py > length) py = length;
    gotoxy(x + 1, py + 1);              // 좌측테두리(1) + 내부 중앙 열
    printf("%s", s);
    gotoxy(x + 3, length + 2);
    printf(" y=%2d ", py);
}

static void move_arrow_key(int key, int *px, int *py, int max_x, int max_y) {
    // 방향키는 0 또는 224 이후 실제 코드
    if (key == 0 || key == 224) key = getch();
    switch (key) {
        case 72: (*py)--; if (*py < 1) *py = 1; break;          // Up
        case 80: (*py)++; if (*py > max_y) *py = max_y; break;  // Down
        case 75: (*px)--; if (*px < 1) *px = 1; break;          // Left
        case 77: (*px)++; if (*px > max_x) *px = max_x; break;  // Right
        default: break;
    }
}

int main(void) {
    // UTF-8 출력(■ 표시 안정화)
    SetConsoleOutputCP(65001);

    const char *slide = "■";
    int x = 1, y = 1;
    int h_len = 50, v_len = 15;

    printf("슬라이드바 표시\n\n");
    printf("수평 슬라이드바의 길이(최대 70)를 입력하고 Enter> ");
    if (scanf("%d", &h_len) != 1) return 0;
    if (h_len < 5) h_len = 5; if (h_len > 70) h_len = 70;

    printf("수직 슬라이드바의 길이(최대 19)를 입력하고 Enter> ");
    if (scanf("%d", &v_len) != 1) return 0;
    if (v_len < 3) v_len = 3; if (v_len > 19) v_len = 19;

    // 초기 위치 보정
    if (x > h_len) x = h_len;
    if (y > v_len) y = v_len;

    int ch = 0;
    do {
        system("cls");
        // 수직 바: 화면 좌측 x=1, 높이 v_len
        draw_vertical_slide(1, y, v_len, slide);
        // 수평 바: 수직 바 하단에서 2줄 아래
        draw_horizontal_slide(x, v_len + 3, h_len, slide);
        printf("\nESC 종료, 방향키 이동");
        ch = getch();
        move_arrow_key(ch, &x, &y, h_len, v_len);
    } while (ch != 27);
    return 0;
}
