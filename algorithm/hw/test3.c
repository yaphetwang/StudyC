#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>

/*
给定一个原始序列，一个特征序列，
请在原始序列中从左往右按匹配规则找到一个匹配特征序列的最短连续子序列，如果存在多个，返回最早匹配的连续子序列
匹配规则：
对于一个子序列，去除其中的n（n>=0） 个元素后，与特征序列相同，则称该子序列与特征序列匹配。
例如：原始序列为{4, 8, 4, 3, 6, 6, 8}，特征序列为{4, 6, 8}，则最短连续子序列为{4, 3, 6, 6, 8}，
*/
#define EVENTS_LEN 1000

static int *MatchLogTrait(const int *events, size_t eventsSize, const int *traits, size_t traitsSize, size_t *returnSize)
{
    int *res = (int *)malloc(sizeof(int) * eventsSize);
    memset(res, 0, sizeof(int) * eventsSize);

    int minCnt = eventsSize + 1;
    int index = 0;
    while (index <= eventsSize - traitsSize)
    {
        // 找下一个子序列
        int temp[EVENTS_LEN] = {0};
        int matchCnt = 0;
        int cnt = 0;
        int start_j = index;
        for (int i = 0; i < traitsSize; i++)
        {
            for (int j = start_j; j < eventsSize; j++)
            {
                if (cnt > 0)
                {
                    temp[cnt++] = events[j];
                }
                if (traits[i] == events[j])
                {
                    if (i == 0 && cnt == 0)
                    {
                        temp[cnt++] = events[j];
                    }
                    start_j = j + 1;
                    matchCnt++;
                    break;
                }
            }
        }

        if (cnt < minCnt && matchCnt == traitsSize)
        {
            minCnt = cnt;
            memset(res, 0, sizeof(int) * eventsSize);
            for (int i = 0; i < cnt; i++)
            {
                res[i] = temp[i];
            }
        }

        index++;
    }

    *returnSize = minCnt;
    return res;
}

int main()
{
    int events[] = {4, 8, 4, 3, 6, 6, 8};
    size_t eventsSize = sizeof(events) / sizeof(events[0]);
    int traits[] = {4, 6, 8};
    size_t traitsSize = sizeof(traits) / sizeof(traits[0]);
    size_t returnSize = 0;
    int *res = (int *)MatchLogTrait(events, eventsSize, traits, traitsSize, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    int events1[] = {2, 30, 4, 4, 6, 2, 2, 3, 4, 6, 6, 2, 4, 4, 6};
    size_t eventsSize1 = sizeof(events1) / sizeof(events1[0]);
    int traits1[] = {2, 4, 6};
    size_t traitsSize1 = sizeof(traits1) / sizeof(traits1[0]);
    size_t returnSize1 = 0;
    int *res1 = (int *)MatchLogTrait(events1, eventsSize1, traits1, traitsSize1, &returnSize1);
    for (int i = 0; i < returnSize1; i++)
    {
        printf("%d ", res1[i]);
    }
    printf("\n");

    return 0;
}