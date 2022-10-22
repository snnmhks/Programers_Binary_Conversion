#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
�����ϰ� 0�� �����ϴ� �Լ��� 2������ �ٲ��ִ� �Լ��� ������־ �ݺ��ϸ� �ȴ�.
0�� ������ �� �������ֱ� ��ٷο�� ����� �޾ƿ��� ���� 0�� ������ 1�� ������ ���� �Ȱ��� ȿ���� �����Ѵ�.
2�� ��ȯ�� 1�� ������ �Ű������� ���� ����ϴ�.
2�� ��ȯ�� �����ϰ� 2���� ��ġ�� ��ȯ�� ���� ���ϸ鼭 ��ȯ�Ѵ� ���� 10�� �ִٸ� 
ù ��° 2���� ��ġ�� 1�� ���� �����Ƿ� �н�
�� ��° 2���� ��ġ�� 2�� ���� �����Ƿ� �н�
�� ��° 2���� ��ġ�� 4�� ���� �����Ƿ� �н�
�� ��° 2���� ��ġ�� 8�� ���� �����Ƿ� �н�
�ټ� ��° 2���� ��ġ�� 16�� ���� �����Ƿ� 10���� ũ�� ���� �� ������ 2������ 1�� �Ǿ�� ���� �� �� �ִ�.
�׷��� �� ��° 2���� ��ġ�� 1�� �ٲٰ� 10 - 8�� �Ͽ� 2�� �Ʊ�� ���� ������� ��ġ�� ã�´�.
-> 1010�� ����
*/

// �Ķ���ͷ� �־����� ���ڿ��� const�� �־����ϴ�. �����Ϸ��� ���ڿ��� �����ؼ� ����ϼ���.

static char s[20] = "10000000000000000000";

int RemoveZero(char* s, int length, int* Remove0)
// 0�� 1�� ���� �Լ�
{
    int OneNum = 0;
    for (int i = 0; i < length; i++)
    {
        if (s[i] == '1')
            // 1�� ����
        {
            OneNum += 1;
        }
        else if (s[i] == '0')
            // 0�� ����
        {
            *Remove0 += 1;
        }
    }
    return OneNum;
}

char* TransferTwo(int onenum, int* MaxCount)
// ���� ��ȯ �Լ�
{
    s[0] = '1';
    for (int i = 1; i < 20; i++)
    {
        s[i] = '0';
    }
    // ���� ��ȯ�� ���� ��� �迭 �ʱ�ȭ
    int tmp = 1;
    // 2�� ��� ���ϴ� ��
    *MaxCount = 0;
    // ��ȯ�� ���� �ִ� ����
    int count = 0;
    // 2������ ��ġ
    while (1)
    {
        if (onenum > tmp)
            // ��ȯ�� ���� 2������ ��ġ�� �ش�Ǵ� ������ ũ��
            // ���� 2���� ��ġ�� �ش�Ǵ� ���� �ٲ۴�.
        {
            tmp = tmp * 2;
            count += 1;
        }
        else if (onenum < tmp)
            // ��ȯ�� ���� 2������ ��ġ�� �ش�Ǵ� ������ ������
            // ���� �ִ� ���̰� �������� �ʾ����� 
            // �ٷ� ���� 2������ ��ġ�� �ִ� ���̿� �ش�ǹǷ� �ִ� ���̸� �ٲپ��ش�.
            // ���� 2������ ��ġ�� 1�� �Ǿ�� �Ѵ�.
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
            // ���ٴ°� ��ȯ�� �����ٴ� ��
        {
            if (*MaxCount == 0)
                // �ѹ濡 ��ȯ�� �Ϸ�Ǹ� �ִ� ���̰� �������� �ʾ����Ƿ� �ִ���� ����
            {
                *MaxCount = count;
            }
            else if (*MaxCount > count)
                // ���������� 2�� ��ȯ�� �������
            {
                s[*MaxCount - count] = '1';
            }
            *MaxCount += 1;
            // ���� ���� (0���� ī��Ʈ �Ͽ��� ������ ���̴� +1 �������)
            return s;
        }
    }
}

int* solution(const char* s) {
    // return ���� malloc �� ���� �Ҵ��� ������ּ���. �Ҵ� ���̴� ��Ȳ�� �°� �������ּ���.
    int Remove0 = 0;
    int OneNum = 0;
    int length = strlen(s);
    int cycle = 0;
    int* answer = (int*)malloc(sizeof(int*) * 2);

    OneNum = RemoveZero(s, length, &Remove0);
    char* s1 = TransferTwo(OneNum, &length);
    cycle += 1;
    // 0����� 2�� ��ȯ�� �ѽ���Ŭ
    if (length == 1)
        // ���̰� 1�̶� �� "1"�� ���Ҵٴ� ��
    {
        answer[0] = cycle;
        answer[1] = Remove0;
        printf("%d, %d", cycle, Remove0);
        return answer;
    }
    // �޾ƿ� s�� ��� ������ ������ �ʱ� ������ �⺻������ 1�� ����Ŭ�� ������ 
    // s1�� ����
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