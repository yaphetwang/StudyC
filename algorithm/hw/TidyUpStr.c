#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100

// 整理字符串，把相邻的大小写字母消除，输出剩下的字符串

// 用栈最合适
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

    char *stack = (char *)malloc(MAX_N * sizeof(char));
    memset(stack, 0, MAX_N);
    int top = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (top > 0)
        {
            if (((stack[top - 1] - str[i]) == 32 || (stack[top - 1] - str[i]) == -32))
            {
                top--;
            }
            else
            {
                stack[top++] = str[i];
            }
        }
        else
        {
            stack[top++] = str[i];
        }
    }

    int index = 1;
    for (size_t i = 0; i < top; i++)
    {
        newStr[index++] = stack[i];
    }

    newStr[index] = '"';
    newStr[index + 1] = '\0';

    return newStr;
}

int main()
{
    char str[] = "commMmon";
    char str1[] = "DfFdmM";
    char str2[] = "i";
    char str3[] = "DafFdmM";
    char *newStr = tidyUpStr(str);
    printf("%s\n", newStr);
    char *newStr1 = tidyUpStr(str1);
    printf("%s\n", newStr1);
    char *newStr2 = tidyUpStr(str2);
    printf("%s\n", newStr2);
    char *newStr3 = tidyUpStr(str3);
    printf("%s\n", newStr3);
    return 0;
}