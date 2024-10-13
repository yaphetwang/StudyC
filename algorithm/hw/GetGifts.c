#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100

// 领取纪念品， 纪念品类型为0,1  每个人想要的礼物也是0,1
/*
类似下面该题
学校的自助午餐提供圆形和方形的三明治，分别用数字 0 和 1 表示。所有学生站在一个队列里，每个学生要么喜欢圆形的要么喜欢方形的。
餐厅里三明治的数量与学生的数量相同。所有三明治都放在一个 栈 里，每一轮：

如果队列最前面的学生 喜欢 栈顶的三明治，那么会 拿走它 并离开队列。
否则，这名学生会 放弃这个三明治 并回到队列的尾部。
这个过程会一直持续到队列里所有学生都不喜欢栈顶的三明治为止。
*/

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
// 模拟法
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

// 更好的思路，计算两种礼物的个数，匹配人员，剩下的就是没有领礼物的人
int GetGifts3(int *persons, int persons_count, int *gifts, int gifts_count)
{
    int s1 = 0;
    for (size_t i = 0; i < persons_count; i++)
    {
        s1 += persons[i];
    }
    int s0 = persons_count - s1;

    for (size_t i = 0; i < gifts_count; i++)
    {
        if (gifts[i] == 0 && s0 > 0)
        {
            s0--;
        }
        else if (gifts[i] == 1 && s1 > 0)
        {
            s1--;
        }
        else
        {
            // 没人要这个礼物，结束
            break;
        }
    }

    return s0 + s1;
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
    int persons_count1 = sizeof(persons1) / sizeof(persons1[0]);
    int gifts1[] = {1, 0, 0, 0, 0, 1};
    int gifts_count1 = sizeof(gifts1) / sizeof(gifts1[0]);
    int res1 = GetGifts2(persons1, persons_count1, gifts1, gifts_count1);
    printf("%d\n", res1);

    int persons2[] = {0, 0, 0, 1, 1, 0};
    int persons_count2 = sizeof(persons2) / sizeof(persons2[0]);
    int gifts2[] = {0, 1, 1, 1, 0, 0};
    int gifts_count2 = sizeof(gifts2) / sizeof(gifts2[0]);
    int res2 = GetGifts3(persons2, persons_count2, gifts2, gifts_count2);
    printf("%d\n", res2);

    int persons3[] = {0, 1, 0, 0, 1, 0};
    int persons_count3 = sizeof(persons3) / sizeof(persons3[0]);
    int gifts3[] = {1, 0, 0, 0, 0, 1};
    int gifts_count3 = sizeof(gifts3) / sizeof(gifts3[0]);
    int res3 = GetGifts3(persons3, persons_count3, gifts3, gifts_count3);
    printf("%d\n", res3);

    return 0;
}