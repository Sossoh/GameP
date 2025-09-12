## 커서의 위치 제어

- **gotoxy 함수**  
  - `SetConsoleCursorPosition` 기반으로 구현  
  - `(x, y)` 좌표를 받아 해당 위치로 커서를 이동  
  - 좌표계: **(1,1) = 왼쪽 상단**  
  - Windows 전용, Linux/Unix에서는 `ncurses` 필요  

ASCII Code & Scan Code

아스키 코드 (ASCII code)

문자에 대해 미리 약속된 코드 값

예: 'a' → 97

스캔 코드 (Scan code)

각 키보드 키 자체에 할당된 코드 값

일반적으로 확장키 코드를 의미

2바이트: 상위 바이트 = 스캔 코드, 하위 바이트 = 아스키 코드

확장키: 1바이트(256개) 아스키 코드로 표현 불가 → 화살표, Home, End, PageUp, PageDown 등

<img width="477" height="124" alt="image" src="https://github.com/user-attachments/assets/79458eda-31a5-4caa-9ff5-4309eb855cc9" />
