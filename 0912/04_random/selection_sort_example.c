#include <stdio.h>

static void selection_sort(int r[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (r[j] < r[min]) min = j;
        }
        int temp = r[min];
        r[min] = r[i];
        r[i] = temp;
    }
}

int main(void) {
    int a[6] = { 42, 7, 31, 18, 7, 12 };
    selection_sort(a, 6);
    for (int i = 0; i < 6; i++) printf("%d ", a[i]);
    puts("");
    return 0;
}
