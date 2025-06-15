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

/*
给定一个字符串,仅有数字，空格或-组成
1.删除所有的空格和-
2.数字从左到右3个一组，直到无剩余，剩余2个或4个数字（不允许剩余1个）
3，剩余2个无需再分组，剩余4个则需从左到右2个一组
4. 每一组中间 用 -  拼接
*/
char *formatStr(char *str)
{
    int len = strlen(str);
    char *res = (char *)malloc(len + 1);
    memset(res, 0, len + 1);

    char temp[len];
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ' && str[i] != '-')
        {
            temp[index++] = str[i];
        }
    }

    int cycle = 0;
    int group = index / 3;
    int remain = index % 3;

    cycle = remain == 1 ? (group - 1) : group;

    int j = 0;
    for (int i = 0; i < cycle; i++)
    {
        res[j++] = temp[i * 3];
        res[j++] = temp[i * 3 + 1];
        res[j++] = temp[i * 3 + 2];
        if (i < cycle - 1)
        {
            res[j++] = '-';
        }
    }

    if (remain == 2)
    {
        res[j++] = '-';
        res[j++] = temp[cycle * 3];
        res[j++] = temp[cycle * 3 + 1];
    }
    else if (remain == 1)
    {
        res[j++] = '-';
        res[j++] = temp[cycle * 3];
        res[j++] = temp[cycle * 3 + 1];
        res[j++] = '-';
        res[j++] = temp[cycle * 3 + 2];
        res[j++] = temp[cycle * 3 + 3];
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

    // char str[] = "-9- 3-86 3 6";
    char str[] = "759 4-8 5 -6";
    char *formatRes = formatStr(str);
    printf("res:%s\n", formatRes);

    return 0;
}