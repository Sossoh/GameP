원본코드

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void moving_character_signboard(char file_name[], int line_length);
void gotoxy(int x, int y);
void draw_rectangle(int c, int r);

int main(void)
{
   char file_name[20];
   int line_length;
   printf("움직이는 글자 광고판\n\n");
   printf("광고내용이 들어있는 파일 이름을\n");
   printf("입력하고 Enter>");
   scanf("%s", file_name);
   printf("광고판에 표시할 문자수를 \n");
   printf("입력하고 Enter>");
   scanf("%d", &line_length);
   moving_character_signboard(file_name, line_length);
   return 0;
}

void moving_character_signboard(char file_name[], int line_length)
{
              //[함수 10.3.1]의 정의 부분 참고
   char *ptr, chr[121];
   int i, j, length, count=0, countx;
   FILE *fp;
   ptr=(char *)malloc(line_length);
   gotoxy(1, 9);
   draw_rectangle(line_length/2, 1);
   fp=fopen(file_name, "r");
   if (fp==NULL)
   {
      printf("file open error!");
      exit(1);
   }
   while(!feof(fp))
   {
      //부분 1의 처리
      fgets(chr, 120, fp);
      length=strlen(chr);
      ptr[line_length]='\0';
      for(j=0;j<line_length;j++)          
      {
         count=0;
         for(i=0;i<line_length-j-1;i++)
            ptr[i]=' ';
         for(i=line_length-j-1;i<line_length;i++)
         {
            ptr[i]=chr[count];
            count++;
         }
         gotoxy(3, 10);
         Sleep(200);
         printf("%s", ptr);
      }
      //부분 2의 처리 
      count=1;
      for(j=line_length-2;j<length;j++)  
      {
         countx=0;      
         for(i=count;i<count+line_length;i++)
         {
            ptr[countx]=chr[i];
            countx++;
         }
         count++;
         if ((length-line_length)<=count)
            break;
         gotoxy(3, 10);
         Sleep(200);
         printf("%s", ptr);
      }
      //부분 3의 처리
      for(j=0;j<line_length;j++)      
      {
         for(i=0;i<line_length-j-1;i++)
            ptr[i]=ptr[i+1];
         for(i=line_length-j-1;i<line_length;i++)
            ptr[i]=' ';
         gotoxy(3, 10);
         Sleep(200);
         printf("%s", ptr);
      }
   }
   gotoxy(1, 12);
   fclose(fp);
}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void draw_rectangle(int c, int r)
{
    //[함수 3.5.2]의 정의부분 참고
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7]; 
    for(i=1;i<7;i++)
      b[i]=0xa0+i;

    printf("%c%c",a, b[3]);
    for(i=0;i<c;i++)
     printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r;i++)
    {
   printf("%c%c", a, b[2]);
   for(j=0;j<c;j++)
      printf("  ");
   printf("%c%c",a, b[2]);
   printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<c;i++)
   printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

```

## 주요 기능 분석
코드는 크게 3개의 애니메이션 파트로 나뉘어 광고판 효과를 구현합니다.

글자 등장 (부분 1)

광고판의 오른쪽 끝에서부터 텍스트가 한 글자씩 나타나며 왼쪽으로 서서히 채워집니다.

예: [ H] → [ He] → [ Hel]

글자 스크롤 (부분 2)

파일에서 읽어온 전체 텍스트가 광고판 길이만큼 잘려서 오른쪽에서 왼쪽으로 쭉 흘러갑니다.

예: [Hello Wor] → [ello Worl] → [llo World]

글자 퇴장 (부분 3)

광고판에 남아있는 텍스트가 왼쪽 끝으로 한 글자씩 사라지며 빈칸으로 채워집니다.

예: [rld ] → [ld ] → [d ]

## 함수별 역할
main() 함수

프로그램의 시작점입니다.

사용자에게 광고 내용이 담긴 파일 이름과 광고판에 표시될 **글자 수(길이)**를 입력받습니다.

입력받은 정보를 moving_character_signboard 함수에 넘겨주어 실제 애니메이션을 실행시킵니다.

moving_character_signboard() 함수

이 코드의 핵심 로직이 들어있는 함수입니다.

fopen으로 파일을 열고 fgets로 한 줄씩 텍스트(chr)를 읽어옵니다.

malloc을 통해 광고판 길이만큼의 메모리(ptr)를 할당하여 현재 화면에 보여줄 내용을 담습니다.

while(!feof(fp)) 루프를 통해 파일의 모든 줄에 대해 아래의 애니메이션을 반복합니다.

부분 1, 2, 3의 for 루프를 순차적으로 실행하며 위에서 설명한 '등장 → 스크롤 → 퇴장' 애니메이션을 구현합니다.

Sleep(200) 함수를 이용해 0.2초 간격으로 화면을 갱신하여 움직이는 것처럼 보이게 합니다.

gotoxy() 함수

콘솔 창의 커서 위치를 지정된 x, y 좌표로 이동시키는 Windows 전용 함수입니다. 이를 통해 광고판의 정해진 위치에만 텍스트를 계속 덧씌울 수 있습니다.

draw_rectangle() 함수

'ㅂ' + 한자 키 등에서 볼 수 있는 특수문자(선 문자)를 이용해 콘솔 창에 **광고판의 테두리(사각형)**를 그립니다.

## 코드의 특징 및 문제점
Windows 의존성: windows.h, gotoxy, Sleep 함수는 Windows 운영체제에서만 동작하므로, 리눅스나 macOS에서는 컴파일되지 않습니다.

파일 처리 버그: fclose(fp);가 while 루프 안에 있습니다. 이 때문에 파일의 첫 번째 줄만 처리하고 파일이 닫혀버려, 두 번째 줄부터는 광고가 표시되지 않는 오류가 있습니다. fclose(fp);는 while 루프가 끝난 뒤에 위치해야 합니다.

메모리 할당: ptr=(char *)malloc(line_length); 부분은 ptr[line_length]='\0'; 에서 할당된 메모리보다 1바이트 더 뒤를 접근하는 오버플로우(overflow) 위험이 있습니다. malloc(line_length + 1)로 수정하는 것이 안전합니다.


---
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
---
