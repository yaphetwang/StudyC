#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100

// 领取纪念品

int GetGifts(int *persons, int persons_count, int *gifts, int gifts_count)
{
    bool flag = false;
    while (!flag)
    {
        for (size_t i = 0; i < gifts_count; i++)
        {
            if (gifts[i] == -1)
            {
                // 已经被领取了
                continue;
            }

            int p_count = 0;
            int count = 0;
            for (size_t j = 0; j < persons_count; j++)
            {
                if (persons[j] == -1)
                {
                    continue;
                }

                p_count++; // 计算该轮剩余人数
                if (gifts[i] == persons[j])
                {
                    gifts[i] = -1;
                    persons[j] = -1;
                    break;
                }
                else
                {
                    count++; // 计算该轮没有领的人数
                }
            }

            if (p_count == count)
            {
                // 该轮全部没领 结束
                flag = true;
                break;
            }
        }

        flag = true;
    }

    int res = 0;
    for (size_t i = 0; i < persons_count; i++)
    {
        res += (persons[i] != -1);
    }
    return res;
}

int GetGifts2(int *persons, int persons_count, int *gifts, int gifts_count)
{
    int res = 0;
    for (size_t i = 0; i < gifts_count; i++)
    {
        if (gifts[i] == -1)
        {
            // 已经被领取了
            continue;
        }

        int p_count = 0;
        int count = 0;
        for (size_t j = 0; j < persons_count; j++)
        {
            if (persons[j] == -1)
            {
                continue;
            }

            p_count++; // 计算该轮剩余人数
            if (gifts[i] == persons[j])
            {
                gifts[i] = -1;
                persons[j] = -1;
                break;
            }
            else
            {
                count++; // 计算该轮没有领的人数
            }
        }

        if (p_count == count)
        {
            // 该轮全部没领 结束
            for (size_t i = 0; i < persons_count; i++)
            {
                res += (persons[i] != -1);
            }
            return res;
        }
    }

    return res;
}

int main()
{
    int persons[] = {0, 0, 0, 1, 1, 0};
    int persons_count = sizeof(persons) / sizeof(persons[0]);
    int gifts[] = {0, 1, 1, 1, 0, 0};
    int gifts_count = sizeof(gifts) / sizeof(gifts[0]);
    int res = GetGifts2(persons, persons_count, gifts, gifts_count);
    printf("%d\n", res);

    int persons1[] = {0, 1, 0, 0, 1, 0};
    int persons_count1 = sizeof(persons) / sizeof(persons[0]);
    int gifts1[] = {1, 0, 0, 0, 0, 1};
    int gifts_count1 = sizeof(gifts) / sizeof(gifts[0]);
    int res1 = GetGifts2(persons1, persons_count1, gifts1, gifts_count1);
    printf("%d", res1);
    return 0;
}