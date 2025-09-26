
#include <stdio.h>

static void serial_number(long long n) {
    if (n > 0) {
        serial_number(n / 10);
        printf("%lld\n", n % 10);
    }
}

static void reverse_number(long long n) {
    if (n <= 0) return;
    printf("%lld\n", n % 10);
    if (n / 10 > 0) reverse_number(n / 10);
}

int main(void) {
    long long number;
    printf("정수를 입력하고 Enter> ");
    if (scanf("%lld", &number) != 1) return 0;

    printf("\n[재귀: 높은 단위부터]\n");
    if (number == 0) puts("0");
    else serial_number(number);

    printf("\n[재귀: 낮은 단위부터]\n");
    if (number == 0) puts("0");
    else reverse_number(number);

    return 0;
}
