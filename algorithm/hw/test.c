#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 00:00-23:59
char *maxTime(char *timeStr)
{
    // 时针
    if (timeStr[0] == '?')
    {
        if (timeStr[1] == '?')
        {
            timeStr[0] = '2';
            timeStr[1] = '3';
        }
        else
        {
            timeStr[0] = (timeStr[1] < '4') ? '2' : '1';
        }
    }

    if (timeStr[1] == '?')
    {
        timeStr[1] = (timeStr[0] < '2') ? '9' : '3';
    }

    // 分针
    // timeStr[3] == '?' ? timeStr[3] = '5' : 0;
    // timeStr[4] == '?' ? timeStr[4] = '9' : 0;
    timeStr[3] = timeStr[3] == '?' ? '5' : timeStr[3];
    timeStr[4] = timeStr[4] == '?' ? '9' : timeStr[4];

    return timeStr;
}

/*
给定一个只含0和1的字符串，将其分割为两个子字符串，
求左字符串中0的个数和右字符串中1的个数的最大值。
输入：100010
输出：4(1000,10)
*/
int maxZeroOne(char *str)
{
    int res = 0;
    int len = strlen(str);

    int left = 0;
    int index = left + 1;
    while (index < len - 1)
    {
        int zero = 0, one = 0;
        for (int i = 0; i < index; i++)
        {
            zero += (str[i] == '0');
        }
        for (int j = index; j < len; j++)
        {
            one += (str[j] == '1');
        }
        res = (zero + one) > res ? (zero + one) : res;
        index++;
    }

    return res;
}

int main()
{
    char timeStr[] = "1?:?4";
    maxTime(timeStr);
    printf("timeStr:%s\n", timeStr);

    char zerooneStr[] = "100010";
    int len = maxZeroOne(zerooneStr);
    printf("maxZeroOne:%d\n", len);

    return 0;
}