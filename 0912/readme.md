# Game Programming (C) — Console Basics

간단한 콘솔 기반 게임 프로그래밍 실습을 **가독성 있게 정리**했습니다. 실습 코드는 각각 **독립 실행** 가능하며, `gcc` 또는 Visual Studio에서 빌드할 수 있습니다.  
Windows 전용 API(`conio.h`, `windows.h`)가 포함된 예제는 주석으로 표시했습니다.

## 폴더 구조
```
.
├── README.md
├── src
│   ├── 01_console              # 콘솔 제어(커서 이동, 화면 지우기, 키 입력)
│   ├── 02_draw                 # 텍스트 모드 도형 그리기
│   ├── 03_menu                 # 메뉴 시스템
│   ├── 04_random               # 난수와 로또 예제
│   └── 05_varargs              # 가변 인수 함수
└── utils
    └── console.h               # gotoxy 등 공용 유틸 (Windows 전용)
```

## 빌드 방법

### MinGW-w64 (Windows, gcc)
```bash
# 예시: 커서 이동 예제
gcc -O2 -Wall src/01_console/gotoxy_example.c -o bin/gotoxy_example.exe
```

### Visual Studio (Windows)
- 각 `.c` 파일을 새 빈 콘솔 프로젝트에 추가
- `utils/console.h` 포함 경로 설정

> **주의**: `conio.h`, `windows.h`는 Windows 전용입니다. WSL·Linux·macOS에서는 동작하지 않습니다.

## 포함 개념 요약
- 콘솔 커서 이동과 화면 지우기, 입력 버퍼 처리
- 아스키 코드 vs 스캔 코드, 화살표 이동
- 텍스트 모드 사각형 그리기
- 단계형 메뉴 시스템
- 범위 난수 생성, 중복 제거, 선택 정렬
- 가변 인수 함수(printf 원리)

원자료: 강의 슬라이드(게임 프로그래밍 C 기본 모듈).

