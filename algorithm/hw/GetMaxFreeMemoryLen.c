#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
题目 找出来 贴一下
*/

// 穷举法
int GetMaxFreeMemoryLen(char *memory, int cnt)
{
    int i = 0, j = 0, len = 0, maxLen = 0;
    len = strlen(memory);
    printf("Memory len: %d\n", len);

    while (i < len)
    {
        if (memory[i] == '.')
        {
            int count = 0;
            for (int j = i + 1; j < len; j++)
            {
                count += (memory[j] == 'x');
                if (count == (cnt + 1))
                {
                    maxLen = (j - i) > maxLen ? (j - i) : maxLen;
                    break;
                }
            }
        }
        i++;
    }
    return maxLen;
}

// 滑动窗口法
int GetMaxFreeMemoryLen2(char *memory, int cnt)
{

    int left = 0, right = 0, maxLen = 0, count = 0;
    int len = strlen(memory);

    while (right < len)
    {
        // 右指针向右移动
        count += (memory[right] == 'x');
        // 左指针向右移动
        while (count > cnt)
        {
            count -= (memory[left] == 'x');
            left++;
        }
        // 计算最大长度
        maxLen = (right - left + 1) > maxLen ? (right - left + 1) : maxLen;
        right++;
    }
    return maxLen;
}

int main()
{
    char memory[] = "..x..x..xx...";
    int cnt = 2;
    int maxLen = GetMaxFreeMemoryLen(memory, cnt);
    printf("Max free memory length: %d\n", maxLen);

    int maxLen2 = GetMaxFreeMemoryLen2(memory, cnt);
    printf("Max free memory length: %d\n", maxLen2);
    return 0;
}