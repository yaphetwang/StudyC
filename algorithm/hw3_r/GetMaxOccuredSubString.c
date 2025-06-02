#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARR_LEN 50
#define SUB_STR_LEN 3

typedef struct
{
    char str[SUB_STR_LEN + 1];
    int cnt;
} StrCnt;

int cmp(const char *a, const char *b)
{
    // for (int i = 0; i < SUBSTR_LEN; i++)
    // {
    //     if (a[i] != b[i])
    //     {
    //         return -1;
    //     }
    // }
    // return 0;
    return strcmp(a, b);
}

int cnt_cmp(const void *a, const void *b)
{
    StrCnt *str_a = (StrCnt *)a;
    StrCnt *str_b = (StrCnt *)b;
    if (str_a->cnt != str_b->cnt)
    {
        return str_b->cnt - str_a->cnt;
    }
    else
    {
        /* 这种写法也是升序*/
        return strcmp(str_a->str, str_b->str);
    }
}

static char *getMaxOccurredSubstring(const char *inputStr)
{
    StrCnt strcnt[ARR_LEN];
    int arr_idx = 0;
    int len = strlen(inputStr);
    int idx = 0;
    while (idx < len - 2)
    {
        char sub_str[SUB_STR_LEN + 1];
        strncpy(sub_str, inputStr + idx, SUB_STR_LEN);
        printf("subStr:%s\n", sub_str);

        int isHit = 0;

        for (int i = 0; i < ARR_LEN; i++)
        {
            if (!cmp(sub_str, strcnt[i].str))
            {
                strcnt[i].cnt++;
                isHit = 1;
                break;
            }
        }

        if (!isHit)
        {
            strcpy(strcnt[arr_idx].str, sub_str);
            strcnt[arr_idx].cnt = 1;
            arr_idx++;
        }

        idx++;
    }

    qsort(strcnt, arr_idx, sizeof(StrCnt), cnt_cmp);
    for (int i = 0; i < arr_idx; i++)
    {
        printf("subStr:%s,cnt:%d\n", strcnt[i].str, strcnt[i].cnt);
    }

    int maxOccurredStrLen = arr_idx * 3 + arr_idx;
    char *maxOccurredStr = (char *)malloc(maxOccurredStrLen);
    memset(maxOccurredStr, 0, maxOccurredStrLen);
    int maxCnt = strcnt[0].cnt;
    int count = 0;
    for (int i = 0; i < arr_idx; i++)
    {
        if (strcnt[i].cnt == maxCnt)
        {
            count++;
        }
    }
    
    for (int i = 0; i < arr_idx; i++)
    {
        if (strcnt[i].cnt == maxCnt)
        {
            strcat(maxOccurredStr, strcnt[i].str);
            count--;
            strcat(maxOccurredStr, count == 0? "":",");
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