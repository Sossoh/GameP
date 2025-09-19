// 카드 섞은 뒤(피셔-예이츠) 무늬->번호로 정렬 분류(qsort)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int suit;  // 0:♠, 1:◆, 2:♥, 3:♣
    int rank;  // 1(A) .. 13(K)
} Card;

static const char* SUIT_UTF8[4] = {"\xE2\x99\xA0", "\xE2\x97\x86", "\xE2\x99\xA5", "\xE2\x99\xA3"};

static void init_deck(Card *a) {
    int k = 0;
    for (int s = 0; s < 4; ++s) {
        for (int r = 1; r <= 13; ++r) {
            a[k].suit = s;
            a[k].rank = r;
            ++k;
        }
    }
}

static void print_card(const Card *c) {
    switch (c->rank) {
        case 1:  printf("A"); break;
        case 11: printf("J"); break;
        case 12: printf("Q"); break;
        case 13: printf("K"); break;
        default: printf("%-2d", c->rank); break;
    }
    printf("%s ", SUIT_UTF8[c->suit]);
}

static void print_deck(const Card *a) {
    for (int i = 0; i < 52; ++i) {
        print_card(&a[i]);
        if ((i+1) % 13 == 0) puts("");
    }
}

static void fisher_yates(Card *a, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Card tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

static int cmp_card(const void *p, const void *q) {
    const Card *a = (const Card*)p;
    const Card *b = (const Card*)q;
    if (a->suit != b->suit) return a->suit - b->suit;
    return a->rank - b->rank;
}

int main(void) {
    Card deck[52];
    srand((unsigned)time(NULL));

    init_deck(deck);
    puts("== 섞기 전 ==");
    print_deck(deck);

    fisher_yates(deck, 52);
    puts("\n== 섞은 후 ==");
    print_deck(deck);

    qsort(deck, 52, sizeof(Card), cmp_card);
    puts("\n== 정렬(무늬->번호) 후 ==");
    print_deck(deck);
    return 0;
}
