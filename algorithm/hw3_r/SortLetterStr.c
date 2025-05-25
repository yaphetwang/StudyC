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
    int ascii_a = *(char *)a;
    int ascii_b = *(char *)b;
    return ascii_a - ascii_b;
}

char *sortLetterStr(const char *letterStr)
{
    int len = strlen(letterStr);
    char *temp = calloc(len, 1);
    // memset(temp, 0, len);
    strcpy(temp, letterStr);

    qsort(temp, len, sizeof(char), cmp);

    char *result = (char *)malloc(len + 1);
    memset(result, 0, len + 1);
    int r_idx = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(temp[i]))
        {
            // 计算在全大写字母中的位置，A 位置为1
            int poi = temp[i] - 'A' + 1;
            // 计算新位置
            int n_idx = (poi) * (poi) % 26 + 1;
            result[r_idx++] = n_idx + 'A' - 1;
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

    char A = 'A';
    char Z = 'Z';
    printf("A ascii : %d\n", A);
    printf("Z ascii : %d\n", Z);

    char a = 'a';
    char z = 'z';
    printf("a ascii : %d\n", a);
    printf("z ascii : %d\n", z);

    int ascii_a = 97;
    printf("97 is char : %c\n", ascii_a);

    // 数字字符转换
    int num = 12345;
    char str[6];
    sprintf_s(str, 6, "%d", num);
    printf("num to str:%s\n", str);

    int num2 = atoi(str);
    printf("str to num:%d\n", num2);
    return 0;
}