
// 반짝반짝 작은별(C Major) - Windows는 Beep로 재생, 그 외 OS는 콘솔에 노트 출력

#include <stdio.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

static double note_freq_from_A4(int semitone_from_A4) {
    return 440.0 * pow(2.0, semitone_from_A4 / 12.0);
}

// C4~C5 범위 매핑 (A4 기준 반음 오프셋)
enum {
    C4 = -9, D4 = -7, E4 = -5, F4 = -4, G4 = -2, A4_ = 0, B4 = 2, C5 = 3, D5 = 5, E5 = 7, F5 = 8, G5 = 10
};

typedef struct { int semi; int ms; const char* name; } Note;

int main(void) {
    // 반짝반짝 작은별 (C장조)
    const Note song[] = {
        {C4, 500, "C4"}, {C4, 500, "C4"}, {G4, 500, "G4"}, {G4, 500, "G4"},
        {A4_,500, "A4"}, {A4_,500, "A4"}, {G4, 1000,"G4"},
        {F4, 500, "F4"}, {F4, 500, "F4"}, {E4, 500, "E4"}, {E4, 500, "E4"},
        {D4, 500, "D4"}, {D4, 500, "D4"}, {C4, 1000,"C4"},

        {G4, 500, "G4"}, {G4, 500, "G4"}, {F4, 500, "F4"}, {F4, 500, "F4"},
        {E4, 500, "E4"}, {E4, 500, "E4"}, {D4, 1000,"D4"},

        {G4, 500, "G4"}, {G4, 500, "G4"}, {F4, 500, "F4"}, {F4, 500, "F4"},
        {E4, 500, "E4"}, {E4, 500, "E4"}, {D4, 1000,"D4"},

        {C4, 500, "C4"}, {C4, 500, "C4"}, {G4, 500, "G4"}, {G4, 500, "G4"},
        {A4_,500, "A4"}, {A4_,500, "A4"}, {G4, 1000,"G4"},
        {F4, 500, "F4"}, {F4, 500, "F4"}, {E4, 500, "E4"}, {E4, 500, "E4"},
        {D4, 500, "D4"}, {D4, 500, "D4"}, {C4, 1000,"C4"}
    };
    const int N = (int)(sizeof(song)/sizeof(song[0]));

#ifdef _WIN32
    printf("Playing Twinkle Twinkle (Beep)...\n");
    for (int i = 0; i < N; ++i) {
        int freq = (int)(note_freq_from_A4(song[i].semi) + 0.5);
        Beep(freq, song[i].ms);
        Sleep(30);
    }
#else
    printf("Non-Windows 환경: 노트와 길이만 출력합니다.\n");
    for (int i = 0; i < N; ++i) {
        double f = note_freq_from_A4(song[i].semi);
        printf("%s (%.2f Hz) for %d ms\n", song[i].name, f, song[i].ms);
    }
#endif
    return 0;
}
