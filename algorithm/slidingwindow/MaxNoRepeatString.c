#include <stdio.h>
#include <string.h>

/**
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

int max_no_repeat_sub_string(char *s, int len)
{
    int max = 0;
    if (len == 0)
    {
        printf("%d\n", max);
        return 0;
    }

    int arr[128] = {0};
    for (int left = 0, right = 0; right < len; right++)
    {
        char r = s[right];
        arr[r]++;
        while (arr[r] > 1)
        {
            // 说明存在重复的字符
            char l = s[left];
            arr[l]--;
            left++;
        }

        // 记录长度
        max = max > right - left + 1 ? max : right - left + 1;
    }

    return max;
}

int max_no_repeat_sub_string2(char *s, int len)
{
    int max = 0;
    if (len == 0)
    {
        printf("%d\n", max);
        return 0;
    }

    int arr[128] = {0};
    int left = 0, right = 0;
    while (right < len)
    {
        arr[s[right]]++;
        while (arr[s[right]] > 1)
        {
            // 说明存在重复的字符,循环到一直把左边的重复字符移出去
            arr[s[left]]--;
            left++;
        }
        // 记录长度
        max = max > right - left + 1 ? max : right - left + 1;
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

    int max = max_no_repeat_sub_string2(s, strlen(s));

    printf("%d\n", max);

    return 0;
}
