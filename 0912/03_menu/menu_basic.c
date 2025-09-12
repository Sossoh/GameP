#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

static int menu_display(void) {
    int select;
    system("cls");
    printf("간식 만들기\n\n");
    printf("1. 햄버거\n");
    printf("2. 스파게티\n");
    printf("3. 프로그램 종료\n\n");
    printf("메뉴번호 입력> ");
    select = getch() - '0';
    return select;
}

static void press_any_key(void) {
    printf("\n\n아무키나 누르면 메인 메뉴로...");
    getch();
}

static void hamburger(void) {
    system("cls");
    printf("햄버거 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

static void spaghetti(void) {
    system("cls");
    printf("스파게티 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

int main(void) {
    int c;
    while ((c = menu_display()) != 3) {
        switch (c) {
        case 1: hamburger(); break;
        case 2: spaghetti(); break;
        default: break;
        }
    }
    return 0;
}
