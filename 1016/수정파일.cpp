#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// 함수 선언
void gotoxy(int x, int y);
void draw_rectangle_movable(int x, int y, int c, int r);
void show_intro();
void print_slow(const char* s, int delay);
void play_intro_bgm();
void play_loading_bgm();
void play_finish_bgm();
void play_ending_bgm();
void set_console_font();
void show_ending(int score);
void moving_signboard_game(char ch01[], int line_length);

// 메인 함수
int main(void)
{
    // 콘솔 기본 설정
    set_console_font();
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");

    SetConsoleTitle(L"🎮 Moving Billboard Ball Game 🎮");
    show_intro(); // 인트로 화면

    char ch01[50];
    int line_length;

    printf("Moving Billboard Ball Game\n\n");
    printf("Enter the file name containing text:\n");
    printf("Input> ");
    scanf("%s", ch01);
    printf("Enter the number of characters to display:\n");
    printf("Input> ");
    scanf("%d", &line_length);

    moving_signboard_game(ch01, line_length); // 본 게임 실행
    return 0;
}

// ✅ 콘솔 폰트 설정
void set_console_font()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(h, FALSE, &cfi);
    wcscpy_s(cfi.FaceName, L"Consolas");
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 18;
    SetCurrentConsoleFontEx(h, FALSE, &cfi);
}

// -----------------------------------------------
// 🎬 인트로
// -----------------------------------------------
void print_slow(const char* s, int delay)
{
    while (*s)
    {
        printf("%c", *s++);
        Sleep(delay);
    }
}

void show_intro()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int colors[] = { 9, 10, 11, 13, 14, 12 };

    // 깜빡이는 인트로 타이틀
    play_intro_bgm();
    for (int i = 0; i < 6; i++)
    {
        SetConsoleTextAttribute(hConsole, colors[i]);
        gotoxy(15, 8);
        printf("🎶  M O V I N G   B I L L B O A R D   G A M E  🎶");
        Sleep(180);
        gotoxy(15, 8);
        printf("                                                 ");
        Sleep(60);
    }

    // 제작자 표시 + 로딩 애니메이션
    SetConsoleTextAttribute(hConsole, 15);
    gotoxy(25, 10);
    print_slow("Created by soheE\n", 40);
    gotoxy(25, 11);
    print_slow("Loading", 40);
    play_loading_bgm();

    for (int i = 0; i < 8; i++)
    {
        Sleep(300);
        printf(".");
        Beep(400 + (i * 50), 70);
    }

    play_finish_bgm();
    Sleep(800);
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
}

// 🎵 간단한 효과음 함수들
void play_intro_bgm()
{
    int tones[] = { 262, 330, 392, 523 };
    for (int i = 0; i < 4; i++)
    {
        Beep(tones[i], 180);
        Sleep(50);
    }
}

void play_loading_bgm()
{
    for (int i = 0; i < 3; i++)
    {
        Beep(494, 100);
        Sleep(100);
        Beep(523, 100);
        Sleep(100);
    }
}

void play_finish_bgm()
{
    Beep(784, 200);
    Sleep(50);
    Beep(988, 250);
    Sleep(100);
    Beep(1047, 400);
}

void play_ending_bgm()
{
    int tones[] = { 659, 587, 523, 392, 330, 262 };
    for (int i = 0; i < 6; i++)
    {
        Beep(tones[i], 250);
        Sleep(60);
    }
    Beep(330, 500);
    Sleep(200);
}

// -----------------------------------------------
// 🎮 전광판 + 공 튕기기 게임 (잔상 제거 + 타이머)
// -----------------------------------------------
void moving_signboard_game(char ch01[], int line_length)
{
    system("cls");
    srand((unsigned)time(NULL));

    // 광고 문구 불러오기 (없으면 기본 "WELCOME")
    FILE* fp = fopen(ch01, "r");
    char chr[121] = "WELCOME";
    if (fp) {
        fgets(chr, 120, fp);
        fclose(fp);
    }

    // 기본 변수 설정
    int boardWidth = strlen(chr) + 2;
    int x = 35, y = 20;              // 전광판 좌표
    int ballX = 40, ballY = 5;       // 공 좌표
    int dirX = 1, dirY = 1;          // 공 이동 방향
    int score = 0;
    int tick = 0;
    int prevX = x, prevY = y;        // 이전 전광판 위치 (잔상 제거용)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);

    // 시간 측정용
    time_t start = time(NULL);
    time_t now;
    double elapsed;

    // 상단 안내 문구
    gotoxy(28, 2);
    printf("==== MOVING BILLBOARD BALL GAME ====");
    gotoxy(25, 4);
    printf("← → : Move | ESC : Quit");
    gotoxy(25, 5);
    printf("Catch the ball with the billboard!");

    while (1)
    {
        tick++;
        now = time(NULL);
        elapsed = difftime(now, start);

        // ===== 입력 처리 (즉시 반응) =====
        if (GetAsyncKeyState(VK_LEFT))  x--;
        if (GetAsyncKeyState(VK_RIGHT)) x++;
        if (x < 1) x = 1;
        if (x > 80 - boardWidth) x = 80 - boardWidth;

        // ===== 이전 전광판 지우기 (잔상 제거) =====
        if (x != prevX || y != prevY) {
            for (int i = 0; i < 3; i++) {
                gotoxy(prevX, prevY + i);
                printf("%-*s", boardWidth + 4, " "); // 공백으로 덮어쓰기
            }
        }

        // ===== 공 이동 (5틱마다 1칸) =====
        if (tick % 5 == 0)
        {
            gotoxy(ballX, ballY);
            printf(" ");
            ballX += dirX;
            ballY += dirY;

            // 벽 충돌 시 반사
            if (ballX <= 2 || ballX >= 78) dirX = -dirX;
            if (ballY <= 2) dirY = -dirY;
        }

        // ===== 전광판 출력 =====
        draw_rectangle_movable(x, y, boardWidth, 1);
        gotoxy(x + 1, y + 1);
        printf("%s", chr);

        // ===== 공 출력 =====
        gotoxy(ballX, ballY);
        printf("O");

        // ===== 충돌 판정 =====
        if (ballY == y && ballX >= x && ballX <= x + boardWidth)
        {
            dirY = -dirY;
            score++;
            Beep(700, 50);
        }

        // ===== 바닥 닿으면 종료 =====
        if (ballY > y + 2)
        {
            gotoxy(35, 10);
            printf("💥 GAME OVER 💥");
            Beep(300, 500);
            break;
        }

        // ===== ESC 누르면 즉시 종료 =====
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gotoxy(35, 10);
            printf("💫 EXIT 💫");
            break;
        }

        // ===== 상단 HUD 표시 (점수 + 시간) =====
        gotoxy(5, 1);
        printf("Score: %d   Time: %.0f sec   ", score, elapsed);

        // 현재 위치를 이전 위치로 저장
        prevX = x; prevY = y;

        Sleep(20); // 루프 딜레이 (입력 반응속도)
    }

    Sleep(1500);

    gotoxy(30, 13);
    printf("Your Play Time: %.0f seconds", elapsed);
    Sleep(1500);
}

// ✅ 전광판 그리기 함수
void draw_rectangle_movable(int x, int y, int c, int r)
{
    int i, j;
    gotoxy(x, y);
    printf("┌");
    for (i = 0; i < c; i++) printf("─");
    printf("┐");

    for (i = 0; i < r; i++)
    {
        gotoxy(x, y + 1 + i);
        printf("│");
        for (j = 0; j < c; j++) printf(" ");
        printf("│");
    }

    gotoxy(x, y + r + 1);
    printf("└");
    for (i = 0; i < c; i++) printf("─");
    printf("┘");
}

// -----------------------------------------------
// 🎬 엔딩 화면
// -----------------------------------------------
void show_ending(int score)
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int colors[] = { 14, 13, 12, 11, 10, 9 };

    // 컬러 깜빡이는 엔딩 텍스트
    for (int i = 0; i < 6; i++)
    {
        SetConsoleTextAttribute(hConsole, colors[i]);
        gotoxy(30, 10);
        printf("T H E   E N D");
        Sleep(300);
    }

    play_ending_bgm();

    // 깜빡이는 엔딩 연출
    for (int i = 0; i < 3; i++)
    {
        gotoxy(30, 10);
        printf("              ");
        Sleep(250);
        gotoxy(30, 10);
        printf("T H E   E N D");
        Sleep(250);
    }

    SetConsoleTextAttribute(hConsole, 15);
    gotoxy(28, 12);
    printf("Press any key to exit...");
    _getch();
}

// -----------------------------------------------
// 커서 이동
// -----------------------------------------------
void gotoxy(int x, int y)
{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
