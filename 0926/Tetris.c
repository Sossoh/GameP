#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// ----- 설정 -----
#define ROWS 22          // 보드 세로(가시영역)
#define COLS 10          // 보드 가로
#define ORIGIN_X 4       // 콘솔 출력 시작 X
#define ORIGIN_Y 2       // 콘솔 출력 시작 Y
#define TICK_MS 300      // 중력 간격(ms)

// ----- 전역 -----
static int board[ROWS][COLS];     // 0=빈칸 1=고정블록
static int piece[3][3];           // 현재 3x3 조각
static int px, py;                // 조각의 보드 내 위치(좌상단 기준)
static int running = 1;

// ----- 유틸 -----
static void gotoxy(int x, int y){
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
static void hide_cursor(void){
    CONSOLE_CURSOR_INFO info = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
static void clear_console(void){
    // 빠른 전체 지우기(간단 구현)
    system("cls");
}

// ----- 그리기 -----
static void draw_board_only(void){
    // 테두리
    gotoxy(ORIGIN_X - 2, ORIGIN_Y - 1);
    printf("+------------+"); // COLS=10 => 10칸 + 좌우=2 => 12개 '-'
    for(int r=0; r<ROWS; r++){
        gotoxy(ORIGIN_X - 2, ORIGIN_Y + r);
        putchar('|');
        for(int c=0;c<COLS;c++){
            if(board[r][c]) printf("[]");
            else printf("  ");
        }
        putchar('|');
    }
    gotoxy(ORIGIN_X - 2, ORIGIN_Y + ROWS);
    printf("+------------+");
    // 안내
    gotoxy(ORIGIN_X + 2*COLS + 2, ORIGIN_Y);
    printf("[조작] ←/→ 이동  ↓ 소프트드롭  SPACE 회전  ESC 종료");
}

static void draw_with_piece(void){
    // 보드 복합 그리기(조각 오버레이)
    // 배경
    gotoxy(0,0);
    for(int r=0;r<ROWS;r++){
        gotoxy(ORIGIN_X - 1, ORIGIN_Y + r);
        for(int c=0;c<COLS;c++){
            int cell = board[r][c];
            // 조각이 덮는 위치인지 확인
            int pr = r - py;
            int pc = c - px;
            int overlay = 0;
            if(pr>=0 && pr<3 && pc>=0 && pc<3){
                overlay = piece[pr][pc];
            }
            if(cell || overlay) printf("[]");
            else printf("  ");
        }
    }
}

// ----- 조각 로직 -----
static void copy_piece(const int src[3][3], int dst[3][3]){
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) dst[i][j]=src[i][j];
}

static void rotate_right(int m[3][3]){
    int t[3][3];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) t[j][2-i]=m[i][j];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) m[i][j]=t[i][j];
}

static int collide_at(int m[3][3], int x, int y){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(!m[i][j]) continue;
            int ry = y + i;
            int rx = x + j;
            if(rx<0 || rx>=COLS || ry<0 || ry>=ROWS) return 1;
            if(board[ry][rx]) return 1;
        }
    }
    return 0;
}

static void lock_piece(void){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(piece[i][j]){
                int ry = py + i;
                int rx = px + j;
                if(ry>=0 && ry<ROWS && rx>=0 && rx<COLS){
                    board[ry][rx] = 1;
                }
            }
        }
    }
}

static int clear_full_lines(void){
    int cleared = 0;
    for(int r=ROWS-1; r>=0; r--){
        int full = 1;
        for(int c=0;c<COLS;c++){
            if(board[r][c]==0){ full = 0; break; }
        }
        if(full){
            // r행 삭제 후 위로 당김
            for(int k=r; k>0; k--){
                for(int c=0;c<COLS;c++){
                    board[k][c] = board[k-1][c];
                }
            }
            for(int c=0;c<COLS;c++) board[0][c]=0;
            cleared++;
            r++; // 같은 r 재검사
        }
    }
    return cleared;
}

static void spawn_piece(void){
    // T 모양(요청 코드 기반)
    const int T[3][3] = {
        {0,1,0},
        {0,1,0},
        {1,1,1}
    };
    copy_piece(T, piece);
    px = (COLS/2) - 2; // 대략 중앙
    if(px<0) px = 0;
    py = 0;
    // 스폰 즉시 충돌이면 게임오버
    if(collide_at(piece, px, py)){
        running = 0;
    }
}

// ----- 입력 처리 -----
static void handle_input(void){
    if(!_kbhit()) return;
    int ch = _getch();
    // 화살표는 2개 입력이 들어올 수 있음
    if(ch==224){ // 특수키 프리픽스
        int k = _getch();
        if(k==75){ // ←
            if(!collide_at(piece, px-1, py)) px--;
        }else if(k==77){ // →
            if(!collide_at(piece, px+1, py)) px++;
        }else if(k==80){ // ↓
            if(!collide_at(piece, px, py+1)) py++;
        }else if(k==72){ // ↑(회전 대체)
            int backup[3][3]; copy_piece(piece, backup);
            rotate_right(piece);
            if(collide_at(piece, px, py)){
                copy_piece(backup, piece); // 불가하면 롤백
            }
        }
    }else if(ch==' '){ // SPACE 회전
        int backup[3][3]; copy_piece(piece, backup);
        rotate_right(piece);
        if(collide_at(piece, px, py)){
            copy_piece(backup, piece);
        }
    }else if(ch==27){ // ESC
        running = 0;
    }
}

// ----- 메인 루프 -----
int main(void){
    hide_cursor();
    clear_console();
    // 보드 초기화
    for(int r=0;r<ROWS;r++) for(int c=0;c<COLS;c++) board[r][c]=0;
    // 첫 조각
    spawn_piece();
    // 프레임 타이밍
    DWORD last = GetTickCount();

    while(running){
        // 중력
        DWORD now = GetTickCount();
        if(now - last >= TICK_MS){
            last = now;
            if(!collide_at(piece, px, py+1)){
                py++;
            }else{
                // 고정
                lock_piece();
                clear_full_lines();
                spawn_piece();
            }
        }

        // 입력
        handle_input();

        // 렌더
        // 테두리는 최초 1회만 그려도 되지만 간단히 매 프레임 갱신
        gotoxy(0,0);
        draw_board_only();
        draw_with_piece();

        Sleep(10); // CPU 점유 완화
    }

    gotoxy(ORIGIN_X, ORIGIN_Y + ROWS + 2);
    printf("Game Over. 아무 키나 누르면 종료...");
    _getch();
    return 0;
}
