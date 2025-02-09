#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
先按照ASCII码升序
再计算新位置，得到新位置对应的字母
*/

int cmp(const void *a, const void *b)
{
    int ascii1 = *(char *)a;
    int ascii2 = *(char *)b;
    return ascii1 - ascii2;
}

char *sortLetterStr(const char *letterStr)
{
    int len = strlen(letterStr);
    char temp[len];
    strcpy(temp, letterStr);
    qsort(temp, len, sizeof(char), cmp);

    char *result = (char *)malloc(len + 1);
    memset(result, 0, len + 1);
    int r_idx = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(temp[i]))
        {
            int poi = temp[i] - 'A' + 1;
            int n_index = (poi) * (poi) % 26 + 1;
            result[r_idx++] = n_index + 'A' - 1;
        }
        else
        {
            int poi = temp[i] - 'a' + 1;
            int n_index = (poi) * (poi) % 26 + 1;
            result[r_idx++] = n_index + 'a' - 1;
        }
    }

    result[r_idx] = '\0';

    return result;
}

int main()
{
    char letterStr[] = "abB";
    char *result = sortLetterStr(letterStr);
    printf("%s\n", result);
    free(result);

    // 数字字符转换
    int num = 12345;
    char str[6];
    sprintf_s(str, 6, "%d", num);
    printf("num to str:%s\n", str);

    int num2 = atoi(str);
    printf("str to num:%d\n", num2);
    return 0;
}