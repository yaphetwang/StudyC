#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int str_conut[1000];
static char *getMaxOccuredSubstring(const char *inputStr)
{

    int len = strlen(inputStr);

    int left = 0;
    int right = left + 3;
    int maxCount = 0;
    while (right <= len)
    {
        char subStr[3];
        // 截取子串
        strncpy(subStr, inputStr + left, 3);
        printf("%s\n", subStr);
        // int count = 0;
        // for (int i = left; i < right; i++)
        // {
        //     subStr[count++] = inputStr[i];
        // }

        int str_index = atoi(subStr);
        str_conut[str_index]++;
        maxCount = str_conut[str_index] > maxCount ? str_conut[str_index] : maxCount;

        left++;
        right++;
    }

    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (maxCount == str_conut[i])
        {
            count++;
        }
    }
    printf("count:%d\n", count);
    printf("maxCount:%d\n", maxCount);

    int count_i = 0;
    int maxOccuredStrLen = count * 4 + count;
    char *maxOccuredStr = (char *)malloc(maxOccuredStrLen);
    memset(maxOccuredStr, 0, maxOccuredStrLen);
    for (int i = 0; i < 1000; i++)
    {
        if (maxCount == str_conut[i])
        {
            count_i++;
            char temp[4];
            sprintf(temp, "%d", i);
            // itoa(i, temp, 10); 此函数不存在
            strcat(maxOccuredStr, temp);
            // strcat_s(maxOccuredStr, maxOccuredStrLen, temp);
            count_i < count ? strcat(maxOccuredStr, ",") : 0;
        }
    }

    return maxOccuredStr;
}

int main()
{
    char inputStr[] = "11212112";
    // scanf("%s", inputStr);
    char *maxOccuredStr = getMaxOccuredSubstring(inputStr);
    printf("%s\n", maxOccuredStr);

    // strstr函数用于在一个字符串中查找另一个字符串首次出现的位置。
    // 如果找到子字符串，则返回指向子字符串在原字符串中首次出现位置的指针；
    // 如果未找到，则返回 NULL。
    char inputStr2[] = "11212112";
    char *subStr = strstr(inputStr, inputStr2);
    printf("%ld\n", subStr - inputStr);

    // 如果 s1 和 s2 是相同的，则返回 0；
    // 如果 s1<s2 则返回小于 0；如果 s1>s2 则返回大于 0。
    int cmp = strcmp(inputStr, inputStr2);
    printf("%d\n", cmp);

    return 0;
}
