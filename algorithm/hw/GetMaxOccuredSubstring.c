#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int str_count[1000];
static char *getMaxOccurredSubstring(const char *inputStr)
{

    int len = strlen(inputStr);

    int left = 0;
    int right = left + 3;
    int maxCount = 0;
    while (right <= len)
    {
        char subStr[4] = {0};
        // 截取子串
        strncpy(subStr, inputStr + left, 3);
        // strncpy_s(subStr, 4, inputStr + left, 3);//长度需要为4(是因为结束符？)
        // memcpy(subStr, inputStr + left, 3);
        // mempcpy(subStr, inputStr + left, 3);

        // int count = 0;
        // for (int i = left; i < right; i++)
        // {
        //     subStr[count++] = inputStr[i];
        // }
        printf("subStr:%s\n", subStr);

        int str_index = atoi(subStr);
        printf("str_index:%d\n", str_index);
        str_count[str_index]++;
        maxCount = str_count[str_index] > maxCount ? str_count[str_index] : maxCount;

        left++;
        right++;
    }

    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (maxCount == str_count[i])
        {
            count++;
        }
    }
    printf("count:%d\n", count);
    printf("maxCount:%d\n", maxCount);

    int count_i = 0;
    int maxOccurredStrLen = count * 4 + count;
    char *maxOccurredStr = (char *)malloc(maxOccurredStrLen);
    memset(maxOccurredStr, 0, maxOccurredStrLen);
    for (int i = 0; i < 1000; i++)
    {
        if (maxCount == str_count[i])
        {
            count_i++;
            char temp[4];
            // sprintf(temp, "%d", i);
            sprintf_s(temp, 4, "%d", i);
            // itoa(i, temp, 10); 此函数不存在
            strcat(maxOccurredStr, temp);
            // strcat_s(maxOccurredStr, maxOccurredStrLen, temp);
            // count_i < count ? strcat(maxOccurredStr, ",") : 0;
            strcat(maxOccurredStr, count_i < count ? "," : "");
        }
    }

    return maxOccurredStr;
}

int main()
{
    char inputStr[] = "11212112";
    // scanf("%s", inputStr);
    char *maxOccurredStr = getMaxOccurredSubstring(inputStr);
    printf("%s\n", maxOccurredStr);

    // strstr函数用于在一个字符串中查找另一个字符串 首次出现的位置。
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
