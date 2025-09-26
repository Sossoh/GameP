
#include <stdio.h>

// 각 숫자를 5행×4열로 표현 (값 1이면 "■", 0이면 공백 두 칸)
static int zero[20]  ={1,1,1,1, 1,0,0,1, 1,0,0,1, 1,0,0,1, 1,1,1,1};
static int one[20]   ={0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0};
static int two[20]   ={1,1,1,1, 0,0,0,1, 1,1,1,1, 1,0,0,0, 1,1,1,1};
static int three[20] ={1,1,1,1, 0,0,0,1, 1,1,1,1, 0,0,0,1, 1,1,1,1};
static int four[20]  ={1,0,0,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1};
static int five[20]  ={1,1,1,1, 1,0,0,0, 1,1,1,1, 0,0,0,1, 1,1,1,1};
static int six[20]   ={1,0,0,0, 1,0,0,0, 1,1,1,1, 1,0,0,1, 1,1,1,1};
static int seven[20] ={1,1,1,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1};
static int eight[20] ={1,1,1,1, 1,0,0,1, 1,1,1,1, 1,0,0,1, 1,1,1,1};
static int nine[20]  ={1,1,1,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1};

static void digit_print(int dim[], int line) {
    for (int i = line * 4; i <= line * 4 + 3; ++i) {
        if (dim[i] == 1) printf("■");
        else printf("  ");
    }
    printf("  ");
}

static void number_check(long long k, int line) {
    if (k >= 1) {
        number_check(k / 10, line);
        switch (k % 10) {
            case 0: digit_print(zero,  line); break;
            case 1: digit_print(one,   line); break;
            case 2: digit_print(two,   line); break;
            case 3: digit_print(three, line); break;
            case 4: digit_print(four,  line); break;
            case 5: digit_print(five,  line); break;
            case 6: digit_print(six,   line); break;
            case 7: digit_print(seven, line); break;
            case 8: digit_print(eight, line); break;
            case 9: digit_print(nine,  line); break;
        }
    }
}

int main(void) {
    long long num;
    printf("디지털 숫자 출력 프로그램\n");
    printf("1 이상의 정수 입력 후 Enter> ");
    if (scanf("%lld", &num) != 1) return 0;
    if (num < 1) { puts("1 이상의 정수를 입력하세요."); return 0; }

    for (int line = 0; line <= 4; ++line) {
        number_check(num, line);
        printf("\n");
    }
    return 0;
}
