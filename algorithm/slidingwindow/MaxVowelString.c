#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 包含指定瑕疵度的最长元音子串 */

int IsVowel(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {

        return 1;
    }
    return 0;
}

int main()
{
    char str[] = "asdbuiodevauufgh";
    int flaw = 0;

    int len = strlen(str);
    int length = 0;
    int left = 0, right = 0;
    int cnt = 0;
    while (right < len)
    {
        cnt += !IsVowel(str[right]);

        while (cnt > flaw)
        {
            cnt -= !IsVowel(str[left++]);
        }

        if (cnt == flaw && IsVowel(str[right]) && IsVowel(str[left]))
        {
            char temp[10] = {0};
            strncpy(temp, str + left, right - left + 1);
            printf("%s\n", temp);
            length = length > (right - left + 1) ? length : (right - left + 1);
        }

        right++;
    }

    printf("%d", length);
}