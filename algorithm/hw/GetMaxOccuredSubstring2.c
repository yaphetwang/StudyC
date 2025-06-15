#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_LEN 1000
#define SUBSTR_LEN 3
typedef struct
{
    char str[3];
    int count;
} StrCount;

int cmp(const char *a, const char *b)
{
    for (int i = 0; i < SUBSTR_LEN; i++)
    {
        if (a[i] != b[i])
        {
            return -1;
        }
    }
    return 0;
    // 针对字符 可以使用 strcmp 函数来判断
}

static char *getMaxOccurredSubstring(const char *inputStr)
{
    StrCount *str_count = (StrCount *)malloc(sizeof(StrCount) * ARRAY_LEN);
    memset(str_count, 0, sizeof(StrCount) * ARRAY_LEN);
    int len = strlen(inputStr);

    int index = 0;
    int left = 0;
    int right = left + 3;
    int maxCount = 0;
    while (right <= len)
    {
        char subStr[3];
        // 截取子串
        strncpy(subStr, inputStr + left, 3);
        printf("subStr:%s\n", subStr);

        bool isFound = false;
        for (int i = 0; i < ARRAY_LEN; i++)
        {
            if (cmp(subStr, str_count[i].str) == 0)
            {
                str_count[i].count++;
                maxCount = str_count[i].count > maxCount ? str_count[i].count : maxCount;
                isFound = true;
                break;
            }
        }

        if (!isFound)
        {
            strcpy(str_count[index].str, subStr);
            // str_count[index].str[0] = subStr[0];
            // str_count[index].str[1] = subStr[1];
            // str_count[index].str[2] = subStr[2];
            str_count[index].count = 1;
            index++;
        }

        left++;
        right++;
    }

    int count = 0;
    for (int i = 0; i < ARRAY_LEN; i++)
    {
        if (maxCount == str_count[i].count)
        {
            count++;
        }
    }
    printf("count:%d\n", count);
    printf("maxCount:%d\n", maxCount);

    int count_i = 0;
    int maxOccurredStrLen = count * 3 + count;
    char *maxOccurredStr = (char *)malloc(maxOccurredStrLen);
    memset(maxOccurredStr, 0, maxOccurredStrLen);
    for (int i = 0; i < ARRAY_LEN; i++)
    {
        if (maxCount == str_count[i].count)
        {
            count_i++;
            strcat(maxOccurredStr, str_count[i].str);
            // strcat_s(maxOccurredStr, maxOccurredStrLen, str_count[i].str);
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
