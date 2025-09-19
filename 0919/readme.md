
# 게임프로그래밍 실습 모음

카드 섞기 후 분류  
피아노 동요 플레이  
스택 구현과 테스트

## 파일 목록
- `shuffle_sort_cards.c` 카드 52장 생성 섞기 정렬 출력
- `piano_song_beep.c` 반짝반짝 작은별 재생 음계 계산 포함
- `stack.h` 스택 헤더
- `stack.c` 스택 구현 push pop
- `stack_test.c` 스택 테스트

## 빠른 시작

### GCC 또는 Clang
```bash
# 카드
gcc -O2 -std=c11 shuffle_sort_cards.c -o shuffle_sort_cards

# 피아노
# Windows가 아니면 노트와 길이만 출력
gcc -O2 -std=c11 piano_song_beep.c -o piano_song_beep -lm

# 스택
gcc -O2 -std=c11 stack.c stack_test.c -o stack_test
