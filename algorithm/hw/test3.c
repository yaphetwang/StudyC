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
                    // 匹配到 特征序列第一个数字后，后面的数字才放入temp数组记录
                    temp[cnt++] = events[j];
                }
                if (traits[i] == events[j])
                {
                    if (i == 0 && cnt == 0)
                    {
                        // 该轮寻找第一次匹配到 特征序列第一个数字
                        temp[cnt++] = events[j];
                    }
                    // 匹配到 特征序列 中的一个数字后，匹配下一个数字时 寻找的起点
                    start_j = j + 1;
                    matchCnt++; // 累加总共匹配到的数字
                    break;
                }
            }
        }

        // 该轮匹配 结束，判断是否 完全匹配到特征序列
        if (cnt < minCnt && matchCnt == traitsSize)
        {
            // 匹配到特征序列的子序列长度小于上次的子序列，进行覆盖
            minCnt = cnt;
            memset(res, 0, sizeof(int) * eventsSize);
            for (int i = 0; i < cnt; i++)
            {
                res[i] = temp[i];
            }
        }

        index++;
    }

    *returnSize = minCnt > eventsSize ? 0 : minCnt;
    return res;
}

/*
滑动窗口 再来一遍, 其实跟第一种方法一样，不算滑窗
请在原始序列中从左往右按匹配规则找到一个匹配特征序列的最短连续子序列，如果存在多个，返回最早匹配的连续子序列
匹配规则：
对于一个子序列，去除其中的n（n>=0） 个元素后，与特征序列相同，则称该子序列与特征序列匹配。
例如：原始序列为{4, 8, 4, 3, 6, 6, 8}，特征序列为{4, 6, 8}，则最短连续子序列为{4, 3, 6, 6, 8}，
*/

static int *MatchLogTrait2(const int *events, size_t eventsSize, const int *traits, size_t traitsSize, size_t *returnSize)
{
    int *res = (int *)malloc(sizeof(int) * eventsSize);
    memset(res, 0, sizeof(int) * eventsSize);

    int minCnt = eventsSize + 10;
    int trait_idx = 0;

    int left = 0, right = 0;
    while (right < eventsSize)
    {
        if (events[right] == traits[trait_idx])
        {
            trait_idx++;
            right++;
        }
        else
        {
            right++;
        }

        if (trait_idx == traitsSize)
        {
            if (minCnt > right - left)
            {
                minCnt = right - left;
                int r_index = 0;
                for (int i = left; i < right; i++)
                {
                    res[r_index++] = events[i];
                }
            }

            left++; // 可以优化下， 让left直接跳到匹配特征序列第一个元素的下一个原始序列位置
            right = left;
            trait_idx = 0;
        }
    }

    *returnSize = minCnt > eventsSize ? 0 : minCnt;
    return res;
}

/*
滑窗
例如：原始序列为{4, 8, 4, 3, 6, 6, 8}，特征序列为{4, 6, 8}，则最短连续子序列为{4, 3, 6, 6, 8}，
*/
static int *MatchLogTrait3(const int *events, size_t eventsSize, const int *traits, size_t traitsSize, size_t *returnSize)
{
    int *res = (int *)malloc(sizeof(int) * eventsSize);
    memset(res, 0, sizeof(int) * eventsSize);

    int minLen = INT_MAX;
    int start = -1;
    int left = 0;
    int trait_idx = 0;

    for (int right = 0; right < eventsSize; right++)
    {
        if (events[right] == traits[trait_idx])
        {
            trait_idx++;

            // 当完全匹配特征数组时
            if (trait_idx == traitsSize)
            {
                // 尝试从左边收缩窗口
                int tempLeft = left;
                int tempIndex = traitsSize - 1;

                for (int i = right; i >= tempLeft; i--)
                {
                    if (events[i] == traits[tempIndex])
                    {
                        tempIndex--;
                        if (tempIndex < 0)
                        {
                            tempLeft = i;
                            break;
                        }
                    }
                }

                // 更新最短子数组
                int currentLen = right - tempLeft + 1;
                if (currentLen < minLen)
                {
                    minLen = currentLen;
                    start = tempLeft;
                }

                // 重置搜索，从下一个位置开始
                left = tempLeft + 1;
                trait_idx = 0;
                right = left - 1; // 因为for循环会right++
            }
        }
    }

    if (start != -1)
    {
        *returnSize = minLen;
        for (int i = 0; i < minLen; i++)
        {
            res[i] = events[start + i];
        }
    }
    else
    {
        *returnSize = 0;
    }

    return res;
}

/*
直接遍历原始序列，先记录匹配特征序列第一个元素的位置， 遍历起始位置去匹配
*/
static int *MatchLogTrait4(const int *events, size_t eventsSize, const int *traits, size_t traitsSize, size_t *returnSize)
{
    int *res = (int *)malloc(sizeof(int) * eventsSize);
    memset(res, 0, sizeof(int) * eventsSize);

    int t_idx = 0;
    int temp[eventsSize];
    for (int i = 0; i <= eventsSize - traitsSize; i++)
    {
        if (events[i] == traits[0])
        {
            temp[t_idx++] = i;
        }
    }

    if (t_idx == 0)
    {
        *returnSize = 0;
        return res;
    }

    int minCnt = eventsSize + 10;
    int start = -1;

    for (int i = 0; i < t_idx; i++)
    {
        int trait_idx = 0;
        for (int idx = temp[i]; idx < eventsSize; idx++)
        {
            if (events[idx] == traits[trait_idx])
            {
                trait_idx++;
            }

            if (trait_idx == traitsSize)
            {
                if (minCnt > idx - temp[i] + 1)
                {
                    minCnt = idx - temp[i] + 1;
                    start = temp[i];
                }
            }
        }
    }

    if (start != -1)
    {
        *returnSize = minCnt;
        for (int i = 0; i < minCnt; i++)
        {
            res[i] = events[start + i];
        }
    }
    else
    {
        *returnSize = 0;
    }
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
    printf("MatchLogTrait:\n");
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    printf("MatchLogTrait2:\n");
    res = (int *)MatchLogTrait2(events, eventsSize, traits, traitsSize, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    printf("MatchLogTrait3:\n");
    res = (int *)MatchLogTrait3(events, eventsSize, traits, traitsSize, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    printf("MatchLogTrait4:\n");
    res = (int *)MatchLogTrait4(events, eventsSize, traits, traitsSize, &returnSize);
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
    res1 = (int *)MatchLogTrait2(events1, eventsSize1, traits1, traitsSize1, &returnSize1);
    for (int i = 0; i < returnSize1; i++)
    {
        printf("%d ", res1[i]);
    }
    printf("\n");
    res1 = (int *)MatchLogTrait3(events1, eventsSize1, traits1, traitsSize1, &returnSize1);
    for (int i = 0; i < returnSize1; i++)
    {
        printf("%d ", res1[i]);
    }
    printf("\n");
    res1 = (int *)MatchLogTrait4(events1, eventsSize1, traits1, traitsSize1, &returnSize1);
    for (int i = 0; i < returnSize1; i++)
    {
        printf("%d ", res1[i]);
    }
    printf("\n");

    return 0;
}