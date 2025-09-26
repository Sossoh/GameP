
#include <stdio.h>
#include <math.h>

static void print_high_to_low(long long n) {
    if (n <= 0) { puts("(0)"); return; }
    int len = (int)floor(log10((double)n)) + 1;
    for (int i = len; i >= 1; --i) {
        long long div = 1;
        for (int k = 1; k < i; ++k) div *= 10;
        long long d = n / div;
        printf("%lld\n", d);
        n -= d * div;
    }
}

static void print_low_to_high(long long n) {
    if (n <= 0) { puts("(0)"); return; }
    while (n > 0) {
        printf("%lld\n", n % 10);
        n /= 10;
    }
}

int main(void) {
    long long number;
    printf("정수를 입력하고 Enter> ");
    if (scanf("%lld", &number) != 1) return 0;

    printf("\n[높은 단위부터 출력]\n");
    print_high_to_low(number);

    printf("\n[낮은 단위부터 출력]\n");
    print_low_to_high(number);
    return 0;
}
