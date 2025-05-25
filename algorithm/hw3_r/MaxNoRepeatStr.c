#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 典型的  滑动窗口算法,  左右指针
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长连续子字符串 的长度。
 *
 * 示例 1:
 * <p>
 * 输入: s = "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子字符串是 "abc"，所以其长度为 3。
 *
 * 看这个大牛的算法递进
 * https://leetcode.cn/problems/wtcaE1/solutions/974092/jian-dan-yi-dong-javac-pythonjshua-dong-dtang/
 */

#define STR_ASCII 128

int max_no_repeat_sub_string(char *s, int len)
{
    int max = 0;
    if (len == 0)
    {
        return max;
    }

    // 用字符的ascii值 当做数组下标
    // int temp[STR_ASCII] = {0};
    // calloc 只是申请了一段内存并初始化为0，但是下标没指定吗？
    int *temp = (int *)calloc(STR_ASCII, 1);
    for (int i = 0; i < STR_ASCII; i++)
    {
        temp[i] = 0;
    }

    int left = 0, right = 0;
    while (right < len)
    {
        // 没有重复的，right一直++，更新了右指针
        temp[s[right]]++;

        while (temp[s[right]] > 1)
        {
            // 有重复的，从左边字符开始减，直到碰到该重复字符并把计数减到 <=1 为止，更新了左指针
            // 本质上  就是 left自增 指到了 right表示的字符
            temp[s[left]]--;
            left++;
        }

        max = max > (right - left + 1) ? max : right - left + 1;
        right++;
    }

    return max;
}

int main()
{
    char a = 'a';
    char z = 'z';
    char A = 'A';
    char Z = 'Z';
    printf("a:%d\n", a);
    printf("z:%d\n", z);
    printf("A:%d\n", A);
    printf("Z:%d\n", Z);

    char s[] = "abcabcbb";
    char s1[] = "pwwkew";

    int max = max_no_repeat_sub_string(s1, strlen(s1));

    printf("max:%d\n", max);

    return 0;
}