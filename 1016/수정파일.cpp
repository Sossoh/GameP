#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// 함수 선언
void moving_character_signboard(char ch01[], int line_length);
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
void show_rhythm_game(int* score);

// 메인 함수
int main(void)
{
    set_console_font();
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");

    show_intro();

    char ch01[20];
    int line_length;
    int score = 0;

    printf("Moving Text Billboard\n\n");
    printf("Enter the file name that contains the ad text:\n");
    printf("Input and press Enter> ");
    scanf("%s", ch01);
    printf("Enter the number of characters to display on the board:\n");
    printf("Input and press Enter> ");
    scanf("%d", &line_length);

    moving_character_signboard(ch01, line_length);
    show_rhythm_game(&score);
    show_ending(score);
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

    play_intro_bgm();
    for (int i = 0; i < 6; i++)
    {
        SetConsoleTextAttribute(hConsole, colors[i]);
        gotoxy(18, 8);
        printf("🎶  M O V I N G   T E X T   B I L L B O A R D  🎶");
        Sleep(180);
        gotoxy(18, 8);
        printf("                                                   ");
        Sleep(60);
    }

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
// 🎮 광고판 (박스 + 텍스트 같이 이동 + 4방향 이동)
// -----------------------------------------------
void moving_character_signboard(char ch01[], int line_length)
{
    char chr[121];
    int length;
    int x = 3, y = 8; // 박스 시작 좌표
    FILE* fp = fopen(ch01, "r");
    if (!fp) { printf("File open error!"); exit(1); }

    fgets(chr, 120, fp);
    fclose(fp);
    length = strlen(chr);

    int paused = 0;
    int prevX = x, prevY = y;

    // 초기 박스 출력
    int boxWidth = strlen(chr) + 2;
    draw_rectangle_movable(x, y, boxWidth, 1);
    gotoxy(x + (boxWidth - (int)strlen(chr)) / 2 + 1, y + 1);
    printf("%s", chr);

    while (1)
    {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) break; // ESC 종료
            if (key == ' ') {     // 일시정지
                paused = !paused;
                gotoxy(0, 20);
                if (paused) printf("[PAUSED] Press SPACE to resume...");
                else printf("                                       ");
            }
        }
        if (paused) continue;

        // 이동 처리 (4방향)
        if (GetAsyncKeyState(VK_LEFT))  x--;
        if (GetAsyncKeyState(VK_RIGHT)) x++;
        if (GetAsyncKeyState(VK_UP))    y--;
        if (GetAsyncKeyState(VK_DOWN))  y++;

        // 콘솔 경계 제한
        if (x < 1) x = 1;
        if (y < 1) y = 1;
        if (x > 80 - boxWidth) x = 80 - boxWidth;
        if (y > 22) y = 22;

        // 이전 위치와 다를 때만 화면 갱신
        if (x != prevX || y != prevY) {
            // 이전 위치 지우기
            for (int i = 0; i < 5; i++) {
                gotoxy(1, prevY + i);
                printf("                                                                 ");
            }

            // 새 위치 박스 + 텍스트 출력
            draw_rectangle_movable(x, y, boxWidth, 1);
            int textX = x + (boxWidth - (int)strlen(chr)) / 2 + 1;
            gotoxy(textX, y + 1);
            printf("%s", chr);

            prevX = x;
            prevY = y;
        }

        Sleep(50);
    }
}

// ✅ 이동 가능한 테두리
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
// 🥁 리듬 미니게임
// -----------------------------------------------
void show_rhythm_game(int* score)
{
    system("cls");
    srand((unsigned)time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    *score = 0;
    gotoxy(30, 3);
    printf("==== RHYTHM MODE ====\n");
    gotoxy(25, 5);
    printf("Press ENTER when the 'O' hits the line!");
    gotoxy(40, 14);
    printf("---------------------- [JUDGE LINE] ----------------------");

    for (int round = 1; round <= 10; round++)
    {
        int posX = 48;
        int posY = 5;
        int targetY = 13;
        int hit = 0;
        int timing = 0;

        for (posY = 5; posY <= targetY; posY++)
        {
            gotoxy(posX, posY);
            printf("O");
            Sleep(100);
            gotoxy(posX, posY);
            printf(" ");

            if (_kbhit()) {
                char key = _getch();
                if (key == 13) {
                    timing = abs(targetY - posY);
                    if (timing == 0) {
                        gotoxy(45, 16);
                        printf("PERFECT! +10");
                        Beep(880, 100);
                        *score += 10;
                    }
                    else if (timing <= 1) {
                        gotoxy(45, 16);
                        printf("GOOD! +7");
                        Beep(700, 80);
                        *score += 7;
                    }
                    else {
                        gotoxy(45, 16);
                        printf("MISS!");
                        Beep(300, 80);
                    }
                    hit = 1;
                    break;
                }
            }
        }

        if (!hit) {
            gotoxy(45, 16);
            printf("MISS!");
            Beep(300, 100);
        }

        Sleep(500);
        gotoxy(45, 16);
        printf("                ");
    }

    gotoxy(42, 18);
    printf("Your Score: %d / 100", *score);
    Beep(600, 300);
    Sleep(1200);
}

// -----------------------------------------------
// 🎬 엔딩 화면
// -----------------------------------------------
void show_ending(int score)
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int colors[] = { 14, 13, 12, 11, 10, 9 };

    for (int i = 0; i < 6; i++)
    {
        SetConsoleTextAttribute(hConsole, colors[i]);
        gotoxy(30, 10);
        printf("T H E   E N D");
        Sleep(300);
    }

    play_ending_bgm();

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
    printf("Your Final Score: %d / 100", score);
    gotoxy(25, 14);
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
