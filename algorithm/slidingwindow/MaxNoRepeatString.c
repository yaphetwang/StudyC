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

    // char s[] = "abcabcbb";
    char s[] = "pwwkew";

    int max = 0;
    int len = strlen(s);
    printf("len:%d\n", len);
    if (len == 0)
    {
        printf("%d\n", max);
        return 0;
    }

    int arr[256];
    for (int left = 0, right = 0; right < len; right++)
    {
        char c = s[right];
        int index_r = c;
        printf("index_r:%d\n", index_r);
        arr[index_r]++;
        while (arr[index_r] > 1)
        {
            // 说明存在重复的字符
            char r = s[left];
            int index_l = r;
            arr[index_l]--;
            left++;
        }

        // 记录长度
        max = max > right - left + 1 ? max : right - left + 1;
    }

    printf("%d\n", max);

    return 0;
}
