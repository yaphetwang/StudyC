#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100

// 整理字符串，把相邻的大小写字母消除，输出剩下的字符串

// 暴力法
char *tidyUpStr(char *str)
{
    char *newStr = (char *)malloc(MAX_N * sizeof(char));
    memset(newStr, 0, MAX_N);
    newStr[0] = '"';

    int len = strlen(str);
    if (len < 2)
    {
        newStr[1] = str[0];
        newStr[2] = '"';
        newStr[3] = '\0';
        return newStr;
    }

    for (size_t i = 0; i < len - 1; i++)
    {
        if (str[i] == '0')
        {
            continue;
        }

        for (size_t j = i + 1; j < len; j++)
        {
            if (str[j] != '0' && ((str[i] - str[j]) == 32 || (str[i] - str[j]) == -32))
            {
                str[i] = '0';
                str[j] = '0';
                break;
            }
        }
    }

    int newLen = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != '0')
        {
            newLen++;
        }
    }

    if (newLen == 0)
    {
        newStr[1] = '"';
        newStr[2] = '\0';
        return newStr;
    }

    int j = 1;
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != '0')
        {
            newStr[j++] = str[i];
        }
    }

    newStr[j] = '"';
    newStr[j + 1] = '\0';

    return newStr;
}

int main()
{
    char str[] = "commMmon";
    char str1[] = "DfFdmM";
    char str2[] = "i";
    char *newStr = tidyUpStr(str);
    printf("%s\n", newStr);
    char *newStr1 = tidyUpStr(str1);
    printf("%s\n", newStr1);
    char *newStr2 = tidyUpStr(str2);
    printf("%s\n", newStr2);
    return 0;
}