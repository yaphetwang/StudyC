#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>

/*
有N个非零且各不相同的整数，求出有多少对相反数（a和-a 是一对相反数）
*/
int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int CountRevertNum(int *num, int cnt)
{
    int count = 0;
    for (int i = 0; i < cnt; i++)
    {
        num[i] = abs(num[i]);
    }

    qsort(num, cnt, sizeof(int), cmp);

    for (size_t i = 0; i < cnt; i++)
    {
        if (num[i] - num[i - 1] == 0)
        {
            count++;
        }
    }
    return count;
}

/*
求两个数的第k个公约数
*/
int GetCommonDivisor(int a, int b, int k)
{
    int temp = a > b ? b : a;
    // 求两个数的公约数
    int count = 0;
    for (int i = 1; i <= temp; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            count++;
            if (count == k)
            {
                return i;
            }
        }
    }

    return 0;
}

/*给一串含有c个正整数的数组，求出有多少个下标的连续区间，它们的和 >= x
都是正整数，一旦 和 满足条件，随着下标右移，和一直是 >= x 的
2，4, 7
x = 6
 */
int CountInterval(int *num, int cnt, int x)
{
    int count = 0;
    int sum = 0;
    int left = 0, right = 0;
    sum += num[0];
    while (right < cnt)
    {
        if (sum >= x)
        {
            count += cnt - right;
            sum -= num[left];
            left++;
        }
        else
        {
            right++;
            sum += num[right];
        }
    }

    return count;
}

/*
N个人，每个人身上有数字M， 当两个人身上数字一样，说明是情侣， 计算单身的人数
5
1,1,2,2,3
1个单身
也可以用M当数组下标，计算出现的次数，次数对2取余不为0 就是单身
*/
int SingleCount(int cnt, int *num)
{
    int count = 0;
    for (int i = 0; i < cnt; i++)
    {
        if (i == cnt - 1)
        {
            count++;
            break;
        }
        if (num[i] == num[i + 1])
        {
            i = i + 1;
        }
        else
        {
            count++;
        }
    }
    return count;
}

/*
做加法
N个数，找出有多少对 数的和 为100，
5
1,99,98,2,2
答案:3
*/
int CountAnd(int *num, int cnt)
{
    int count = 0;
    qsort(num, cnt, sizeof(int), cmp);
    for (int i = 0; i < cnt; i++)
    {
        for (int j = cnt - 1; j > i; j--)
        {
            if (num[i] + num[j] == 100)
            {
                count++;
            }
            if (num[i] + num[j] < 100)
            {
                break;
            }
        }
    }
    return count;
}

/*
子串匹配
一个字符串s, 一个字符串p，请问最少去掉s中的多少个字符，才能使得p是s的子串
axb
ab
答案：1
*/
int MatchSonStr(char *s, char *p)
{
    int sLen = strlen(s);
    int pLen = strlen(p);

    int temp_idx = 0;
    int temp[sLen];
    for (int i = 0; i < sLen; i++)
    {
        if (s[i] == p[0])
        {
            temp[temp_idx++] = i;
        }
    }

    int remove_cnt = INT_MAX;
    for (int t = 0; t < temp_idx; t++)
    {
        int p_idx = 0;
        int r_cnt = 0;
        for (int i = temp[t]; i < sLen; i++)
        {
            if (s[i] == p[p_idx])
            {
                p_idx++;
            }
            else
            {
                r_cnt++;
            }
            if (p_idx == pLen)
            {
                remove_cnt = r_cnt < remove_cnt ? r_cnt : remove_cnt;
            }
        }
    }
    return remove_cnt == INT_MAX ? -1 : remove_cnt;
}

int main()
{
    int arr[] = {1, 2, 3, -1, -2};
    int count = CountRevertNum(arr, 5);
    printf("CountRevertNum:%d\n", count);

    int a = 8, b = 16, k = 3;
    printf("GetCommonDivisor:%d\n", GetCommonDivisor(a, b, k));

    int arr1[] = {2, 4, 7};
    printf("CountInterval:%d\n", CountInterval(arr1, 3, 6));

    int arr2[] = {1, 1, 1, 2, 2, 3};
    printf("SingleCount:%d\n", SingleCount(6, arr2));

    int arr3[] = {1, 99, 98, 2, 2};
    printf("CountAnd:%d\n", CountAnd(arr3, 5));

    char s[] = "axxdsebsan";
    char p[] = "ab";
    printf("MatchSonStr:%d\n", MatchSonStr(s, p));
}