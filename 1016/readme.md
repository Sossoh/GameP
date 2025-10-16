원본코드

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void moving_character_signboard(char file_name[], int line_length);
void gotoxy(int x, int y);
void draw_rectangle(int c, int r);

int main(void)
{
   char file_name[20];
   int line_length;
   printf("움직이는 글자 광고판\n\n");
   printf("광고내용이 들어있는 파일 이름을\n");
   printf("입력하고 Enter>");
   scanf("%s", file_name);
   printf("광고판에 표시할 문자수를 \n");
   printf("입력하고 Enter>");
   scanf("%d", &line_length);
   moving_character_signboard(file_name, line_length);
   return 0;
}

void moving_character_signboard(char file_name[], int line_length)
{
              //[함수 10.3.1]의 정의 부분 참고
   char *ptr, chr[121];
   int i, j, length, count=0, countx;
   FILE *fp;
   ptr=(char *)malloc(line_length);
   gotoxy(1, 9);
   draw_rectangle(line_length/2, 1);
   fp=fopen(file_name, "r");
   if (fp==NULL)
   {
      printf("file open error!");
      exit(1);
   }
   while(!feof(fp))
   {
      //부분 1의 처리
      fgets(chr, 120, fp);
      length=strlen(chr);
      ptr[line_length]='\0';
      for(j=0;j<line_length;j++)          
      {
         count=0;
         for(i=0;i<line_length-j-1;i++)
            ptr[i]=' ';
         for(i=line_length-j-1;i<line_length;i++)
         {
            ptr[i]=chr[count];
            count++;
         }
         gotoxy(3, 10);
         Sleep(200);
         printf("%s", ptr);
      }
      //부분 2의 처리 
      count=1;
      for(j=line_length-2;j<length;j++)  
      {
         countx=0;      
         for(i=count;i<count+line_length;i++)
         {
            ptr[countx]=chr[i];
            countx++;
         }
         count++;
         if ((length-line_length)<=count)
            break;
         gotoxy(3, 10);
         Sleep(200);
         printf("%s", ptr);
      }
      //부분 3의 처리
      for(j=0;j<line_length;j++)      
      {
         for(i=0;i<line_length-j-1;i++)
            ptr[i]=ptr[i+1];
         for(i=line_length-j-1;i<line_length;i++)
            ptr[i]=' ';
         gotoxy(3, 10);
         Sleep(200);
         printf("%s", ptr);
      }
   }
   gotoxy(1, 12);
   fclose(fp);
}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void draw_rectangle(int c, int r)
{
    //[함수 3.5.2]의 정의부분 참고
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7]; 
    for(i=1;i<7;i++)
      b[i]=0xa0+i;

    printf("%c%c",a, b[3]);
    for(i=0;i<c;i++)
     printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r;i++)
    {
   printf("%c%c", a, b[2]);
   for(j=0;j<c;j++)
      printf("  ");
   printf("%c%c",a, b[2]);
   printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<c;i++)
   printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

```

## 주요 기능 분석
코드는 크게 3개의 애니메이션 파트로 나뉘어 광고판 효과를 구현합니다.

글자 등장 (부분 1)

광고판의 오른쪽 끝에서부터 텍스트가 한 글자씩 나타나며 왼쪽으로 서서히 채워집니다.

예: [ H] → [ He] → [ Hel]

글자 스크롤 (부분 2)

파일에서 읽어온 전체 텍스트가 광고판 길이만큼 잘려서 오른쪽에서 왼쪽으로 쭉 흘러갑니다.

예: [Hello Wor] → [ello Worl] → [llo World]

글자 퇴장 (부분 3)

광고판에 남아있는 텍스트가 왼쪽 끝으로 한 글자씩 사라지며 빈칸으로 채워집니다.

예: [rld ] → [ld ] → [d ]

## 함수별 역할
main() 함수

프로그램의 시작점입니다.

사용자에게 광고 내용이 담긴 파일 이름과 광고판에 표시될 **글자 수(길이)**를 입력받습니다.

입력받은 정보를 moving_character_signboard 함수에 넘겨주어 실제 애니메이션을 실행시킵니다.

moving_character_signboard() 함수

이 코드의 핵심 로직이 들어있는 함수입니다.

fopen으로 파일을 열고 fgets로 한 줄씩 텍스트(chr)를 읽어옵니다.

malloc을 통해 광고판 길이만큼의 메모리(ptr)를 할당하여 현재 화면에 보여줄 내용을 담습니다.

while(!feof(fp)) 루프를 통해 파일의 모든 줄에 대해 아래의 애니메이션을 반복합니다.

부분 1, 2, 3의 for 루프를 순차적으로 실행하며 위에서 설명한 '등장 → 스크롤 → 퇴장' 애니메이션을 구현합니다.

Sleep(200) 함수를 이용해 0.2초 간격으로 화면을 갱신하여 움직이는 것처럼 보이게 합니다.

gotoxy() 함수

콘솔 창의 커서 위치를 지정된 x, y 좌표로 이동시키는 Windows 전용 함수입니다. 이를 통해 광고판의 정해진 위치에만 텍스트를 계속 덧씌울 수 있습니다.

draw_rectangle() 함수

'ㅂ' + 한자 키 등에서 볼 수 있는 특수문자(선 문자)를 이용해 콘솔 창에 **광고판의 테두리(사각형)**를 그립니다.

## 코드의 특징 및 문제점
Windows 의존성: windows.h, gotoxy, Sleep 함수는 Windows 운영체제에서만 동작하므로, 리눅스나 macOS에서는 컴파일되지 않습니다.

파일 처리 버그: fclose(fp);가 while 루프 안에 있습니다. 이 때문에 파일의 첫 번째 줄만 처리하고 파일이 닫혀버려, 두 번째 줄부터는 광고가 표시되지 않는 오류가 있습니다. fclose(fp);는 while 루프가 끝난 뒤에 위치해야 합니다.

메모리 할당: ptr=(char *)malloc(line_length); 부분은 ptr[line_length]='\0'; 에서 할당된 메모리보다 1바이트 더 뒤를 접근하는 오버플로우(overflow) 위험이 있습니다. malloc(line_length + 1)로 수정하는 것이 안전합니다.
