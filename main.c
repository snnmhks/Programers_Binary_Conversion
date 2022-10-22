#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
간단하게 0을 제거하는 함수와 2진수로 바꿔주는 함수를 만들어주어서 반복하면 된다.
0을 제거할 때 제거해주기 까다로우며 상수로 받아오니 쉽게 0의 갯수와 1의 갯수를 세면 똑같은 효과를 발휘한다.
2진 변환도 1의 갯수가 매개변수로 들어가면 충분하다.
2진 변환은 간단하게 2진수 위치를 변환될 수와 비교하면서 변환한다 예로 10이 있다면 
첫 번째 2진수 위치는 1의 값을 가지므로 패스
두 번째 2진수 위치는 2의 값을 가지므로 패스
세 번째 2진수 위치는 4의 값을 가지므로 패스
네 번째 2진수 위치는 8의 값을 가지므로 패스
다섯 번째 2진수 위치는 16의 값을 가지므로 10보다 크다 따라서 그 직전의 2진수가 1이 되어야 함을 알 수 있다.
그러면 네 번째 2진수 위치를 1로 바꾸고 10 - 8을 하여 2를 아까와 같은 방법으로 위치를 찾는다.
-> 1010이 나옴
*/

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.

static char s[20] = "10000000000000000000";

int RemoveZero(char* s, int length, int* Remove0)
// 0과 1을 세는 함수
{
    int OneNum = 0;
    for (int i = 0; i < length; i++)
    {
        if (s[i] == '1')
            // 1을 세고
        {
            OneNum += 1;
        }
        else if (s[i] == '0')
            // 0을 센다
        {
            *Remove0 += 1;
        }
    }
    return OneNum;
}

char* TransferTwo(int onenum, int* MaxCount)
// 이진 변환 함수
{
    s[0] = '1';
    for (int i = 1; i < 20; i++)
    {
        s[i] = '0';
    }
    // 이진 변환한 수를 담는 배열 초기화
    int tmp = 1;
    // 2를 계속 곱하는 수
    *MaxCount = 0;
    // 변환될 수의 최대 길이
    int count = 0;
    // 2진법의 위치
    while (1)
    {
        if (onenum > tmp)
            // 변환될 수가 2진법의 위치에 해당되는 수보다 크면
            // 다음 2진법 위치에 해당되는 수로 바꾼다.
        {
            tmp = tmp * 2;
            count += 1;
        }
        else if (onenum < tmp)
            // 변환될 수가 2진법의 위치에 해당되는 수보다 작으면
            // 또한 최대 길이가 정해지지 않았으면 
            // 바로 직전 2진법의 위치가 최대 길이에 해당되므로 최대 길이를 바꾸어준다.
            // 직전 2진법의 위치가 1이 되어야 한다.
        {
            tmp = tmp / 2;
            count -= 1;
            if (*MaxCount == 0)
            {
                *MaxCount = count;
            }
            s[*MaxCount - count] = '1';
            onenum -= tmp;
            count = 0;
            tmp = 1;
        }
        else if (onenum == tmp)
            // 같다는건 변환이 끝났다는 뜻
        {
            if (*MaxCount == 0)
                // 한방에 변환이 완료되면 최대 길이가 정해지지 않았으므로 최대길이 변경
            {
                *MaxCount = count;
            }
            else if (*MaxCount > count)
                // 마지막까지 2진 변환은 해줘야함
            {
                s[*MaxCount - count] = '1';
            }
            *MaxCount += 1;
            // 길이 보정 (0부터 카운트 하였기 때문에 길이는 +1 해줘야함)
            return s;
        }
    }
}

int* solution(const char* s) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int Remove0 = 0;
    int OneNum = 0;
    int length = strlen(s);
    int cycle = 0;
    int* answer = (int*)malloc(sizeof(int*) * 2);

    OneNum = RemoveZero(s, length, &Remove0);
    char* s1 = TransferTwo(OneNum, &length);
    cycle += 1;
    // 0지우고 2진 변환이 한싸이클
    if (length == 1)
        // 길이가 1이란 건 "1"만 남았다는 뜻
    {
        answer[0] = cycle;
        answer[1] = Remove0;
        printf("%d, %d", cycle, Remove0);
        return answer;
    }
    // 받아온 s는 상수 변수로 변하지 않기 때문에 기본적으로 1번 싸이클을 굴려서 
    // s1을 생성
    while (1)
    {
        OneNum = RemoveZero(s1, length, &Remove0);
        s1 = TransferTwo(OneNum, &length);
        cycle += 1;
        if (length == 1)
        {
            break;
        }
    }
    answer[0] = cycle;
    answer[1] = Remove0;
    printf("%d, %d", cycle, Remove0);
    return answer;
}

int main()
{
    const char* s = "01";
    int* answer = solution(s);
    printf("\n%d,%d", answer[0], answer[1]);

    /*int r = 0;
     int o = 2;
     int l = 2;
     char* s1 = TransferTwo(o, &l);
     printf("%d\n", l);
     for (int i = 0; i < l; i++)
     {
         printf("%c", s1[i]);
     }
     o = RemoveZero(s1, l, &r);
     printf("\n%d", o);*/
    _getch();
}