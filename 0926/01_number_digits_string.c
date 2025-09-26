
#include <stdio.h>
#include <string.h>

int main(void) {
    char number[256];
    printf("금액(숫자)을 입력하고 Enter> ");
    if (scanf("%255s", number) != 1) return 0;

    int len = (int)strlen(number);

    printf("\n[정방향 출력]\n");
    for (int i = 0; i < len; i++) {
        if (number[i] >= '0' && number[i] <= '9')
            printf("%c\n", number[i]);
    }

    printf("\n[역방향 출력]\n");
    for (int i = len - 1; i >= 0; i--) {
        if (number[i] >= '0' && number[i] <= '9')
            printf("%c\n", number[i]);
    }
    return 0;
}
