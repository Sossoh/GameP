
# 가변 인수 (Variable Arguments)


##핵심 요약

- ...을 사용하면 인자 개수를 유동적으로 받을 수 있음
- <stdarg.h> + va_list + va_start / va_arg / va_end 필수
- printf, scanf 같은 표준 함수도 이 원리 기반으로 구현

## 개념 정리
- **가변 인수 함수**: 호출 시 인자의 개수가 고정되지 않고 달라질 수 있는 함수  
  - 예: `printf`, `scanf`
- 함수 원형에는 반드시 **고정 매개변수 ≥ 1개**가 있어야 하며, 그 뒤에 `...`을 붙여 정의  
  - `int printf(const char *format, ...);`

## 관련 헤더와 자료형
- `<stdarg.h>` 헤더 포함
- **va_list**  
  - 가변 인수 처리를 위한 포인터 변수 타입
  - 인수들의 정보를 담고 있음

## 매크로 함수
- `va_start(ap, last)`  
  - `ap`를 초기화, `last`는 고정 매개변수 중 마지막 인수
- `va_arg(ap, type)`  
  - `ap`에서 다음 인수를 꺼내어 `type`으로 반환
- `va_end(ap)`  
  - 가변 인수 처리를 종료, 리소스 정리

## 예시 코드
```c
#include <stdio.h>
#include <stdarg.h>

double sum(int count, ...) {
    va_list ap;
    double total = 0.0;

    va_start(ap, count);           // 초기화
    for (int i = 0; i < count; i++) {
        total += va_arg(ap, double); // 순서대로 인수 추출
    }
    va_end(ap);                    // 정리

    return total;
}

int main(void) {
    printf("합계 = %.2f\n", sum(2, 10.5, 20.2));
    printf("합계 = %.2f\n", sum(4, 1.0, 2.0, 3.0, 4.0));
    return 0;
}
