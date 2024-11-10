#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>

#define CHAR_LEN 6

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
/*数字序列排序后取前三分之一（向上取整），再取中间值（中位数）*/
int MedianNum(int *arr, int n)
{
    qsort(arr, n, sizeof(int), cmp);
    int threeIndex = (n % 3 == 0) ? n / 3 : n / 3 + 1;

    if (threeIndex % 2 != 0)
    {
        return arr[threeIndex / 2];
    }

    int sum = arr[threeIndex / 2 - 1] + arr[threeIndex / 2];
    return sum % 2 == 0 ? sum / 2 : sum / 2 + 1;
}

/*
x@y=2x+y+3,x$y=3x+2*y+1,@优先级高于$
103$104@105@2$106@107
*/
int getRetA(int x, int y)
{
    return 2 * x + y + 3;
}
int getRetB(int x, int y)
{
    return 3 * x + 2 * y + 1;
}

int PhoneInfoDecode(char *phoneInfo)
{
    int len = strlen(phoneInfo);
    char *stack = (char *)malloc(len);
    memset(stack, 0, len);
    int top = 0;
    // 先解析@
    for (int i = 0; i < len; i++)
    {
        if (phoneInfo[i] != '@')
        {
            stack[top++] = phoneInfo[i];
            continue;
        }
        // 遇到@,先取左边
        char t_left[CHAR_LEN] = {0};
        int tl = 0;
        while (top > 0 && stack[top - 1] != '$')
        {
            t_left[tl++] = stack[--top];
        }
        char left[CHAR_LEN] = {0};
        int l = 0;
        for (int t = tl - 1; t >= 0; t--)
        {
            left[l++] = t_left[t];
        }
        printf("left:%s\n", left);
        int x = atoi(left);
        // 取右边
        char right[6] = {0};
        int r = 0;
        int k = 0;
        for (k = i + 1; k < len; k++)
        {
            if (phoneInfo[k] == '@' && phoneInfo[k] == '$')
            {
                break;
            }
            right[r++] = phoneInfo[k];
        }
        printf("right:%s\n", right);
        int y = atoi(right);
        int ret = getRetA(x, y);
        printf("ret:%d\n", ret);
        char temp[6] = {0};
        sprintf(temp, "%d", ret);
        printf("temp:%s\n", temp);
        for (size_t i = 0; i < 6; i++)
        {
            if (temp[i] != '\0')
            {
                stack[top++] = temp[i];
            }
        }

        printf("stack:%s,top:%d\n", stack, top);
        i = k - 1;
        printf("i:%d\n", i);
    }

    // 再解析$
    printf("decode $\n");
    char temp_info[top];
    for (int i = 0; i < top; i++)
    {
        temp_info[i] = stack[i];
    }
    int count = top;
    printf("temp_info:%s\n", temp_info);
    memset(stack, 0, len);
    top = 0;
    for (int i = 0; i < count; i++)
    {
        if (temp_info[i] != '$')
        {
            stack[top++] = temp_info[i];
            continue;
        }
        // 遇到$,先取左边
        char t_left[6] = {0};
        int tl = 0;
        while (top > 0 && stack[top - 1] != '$')
        {
            t_left[tl++] = stack[--top];
        }
        char left[6] = {0};
        int l = 0;
        for (int t = tl - 1; t >= 0; t--)
        {
            left[l++] = t_left[t];
        }
        printf("left:%s\n", left);
        int x = atoi(left);
        // 取右边
        char right[6] = {0};
        int r = 0;
        int k = 0;
        for (k = i + 1; k < count; k++)
        {
            if (temp_info[k] == '$')
            {
                break;
            }
            right[r++] = temp_info[k];
        }
        printf("right:%s\n", right);
        int y = atoi(right);
        int ret = getRetB(x, y);
        printf("ret:%d\n", ret);
        char temp[6] = {0};
        sprintf(temp, "%d", ret);
        printf("temp:%s\n", temp);
        for (size_t i = 0; i < 6; i++)
        {
            if (temp[i] != '\0')
            {
                stack[top++] = temp[i];
            }
        }

        printf("stack:%s,top:%d\n", stack, top);
        i = k - 1; // 注意这里要减1，因为要先执行i++
    }

    int res = atoi(stack);
    return res;
}

// 解析@
char *decodeA(char *phoneInfo, int len, int *size)
{
    char *stack = (char *)malloc(len);
    memset(stack, 0, len);
    int top = 0;
    for (int i = 0; i < len; i++)
    {
        if (phoneInfo[i] != '@')
        {
            stack[top++] = phoneInfo[i];
            continue;
        }
        char t_left[6] = {0};
        int tl = 0;
        while (top > 0 && stack[top - 1] != '$')
        {
            t_left[tl++] = stack[--top];
        }
        char left[6] = {0};
        int l = 0;
        for (int t = tl - 1; t >= 0; t--)
        {
            left[l++] = t_left[t];
        }
        int x = atoi(left);
        // 取右边
        char right[6] = {0};
        int r = 0, k = 0;
        for (k = i + 1; k < len; k++)
        {
            if (phoneInfo[k] == '@' || phoneInfo[k] == '$')
            {
                break;
            }
            right[r++] = phoneInfo[k];
        }
        int y = atoi(right);
        int ret = getRetA(x, y);
        char temp[6] = {0};
        sprintf(temp, "%d", ret);
        for (size_t i = 0; i < 6; i++)
        {
            if (temp[i] != '\0')
            {
                stack[top++] = temp[i];
            }
        }
        i = k - 1;
    }
    *size = top;
    return stack;
}
// 解析$
char *decodeB(char *phoneInfo, int len, int *size)
{
    char *stack = (char *)malloc(len);
    memset(stack, 0, len);
    int top = 0;
    for (int i = 0; i < len; i++)
    {
        if (phoneInfo[i] != '$')
        {
            stack[top++] = phoneInfo[i];
            continue;
        }
        char t_left[6] = {0};
        int tl = 0;
        while (top > 0 && stack[top - 1] != '$')
        {
            t_left[tl++] = stack[--top];
        }
        char left[6] = {0};
        int l = 0;
        for (int t = tl - 1; t >= 0; t--)
        {
            left[l++] = t_left[t];
        }
        int x = atoi(left);
        // 取右边
        char right[6] = {0};
        int r = 0, k = 0;
        for (k = i + 1; k < len; k++)
        {
            if (phoneInfo[k] == '$')
            {
                break;
            }
            right[r++] = phoneInfo[k];
        }
        int y = atoi(right);
        int ret = getRetB(x, y);
        char temp[6] = {0};
        sprintf(temp, "%d", ret);
        for (size_t i = 0; i < 6; i++)
        {
            if (temp[i] != '\0')
            {
                stack[top++] = temp[i];
            }
        }
        i = k - 1; // 注意这里要减1，因为要先执行i++
    }
    *size = top;
    return stack;
}

int PhoneInfoDecode2(char *phoneInfo)
{
    // 先解析@
    int len = strlen(phoneInfo);
    int size = 0;
    char *decodeAStr = (char *)decodeA(phoneInfo, len, &size);
    printf("decodeAStr:%s\n", decodeAStr);
    char temp_info[size];
    for (int i = 0; i < size; i++)
    {
        temp_info[i] = decodeAStr[i];
    }
    // 再解析$
    int b_size = 0;
    char *decodeBStr = (char *)decodeB(temp_info, size, &b_size);
    printf("decodeBStr:%s\n", decodeBStr);
    int res = atoi(decodeBStr);
    return res;
}

char *decodeCommon(char *phoneInfo, int len, char divide, int *size)
{
    char *stack = (char *)malloc(len);
    memset(stack, 0, len);
    int top = 0;
    for (int i = 0; i < len; i++)
    {
        if (phoneInfo[i] != divide)
        {
            stack[top++] = phoneInfo[i];
            continue;
        }
        char t_left[CHAR_LEN] = {0};
        int tl = 0;
        while (top > 0 && stack[top - 1] != '$')
        {
            t_left[tl++] = stack[--top];
        }
        char left[CHAR_LEN] = {0};
        int l = 0;
        for (int t = tl - 1; t >= 0; t--)
        {
            left[l++] = t_left[t];
        }
        int x = atoi(left);
        // 取右边
        char right[CHAR_LEN] = {0};
        int r = 0, k = 0;
        for (k = i + 1; k < len; k++)
        {
            if (phoneInfo[k] == '@' || phoneInfo[k] == '$')
            {
                break;
            }
            right[r++] = phoneInfo[k];
        }
        int y = atoi(right);
        int ret = (divide == '@') ? getRetA(x, y) : getRetB(x, y);
        char temp[CHAR_LEN] = {0};
        sprintf(temp, "%d", ret);
        for (size_t i = 0; i < CHAR_LEN; i++)
        {
            if (temp[i] != '\0')
            {
                stack[top++] = temp[i];
            }
        }
        i = k - 1;
    }
    *size = top;
    return stack; 
}

int PhoneInfoDecode3(char *phoneInfo)
{
    // 先解析@
    int len = strlen(phoneInfo);
    int size = 0;
    char *decodeAStr = (char *)decodeCommon(phoneInfo, len, '@', &size);
    printf("decodeAStr:%s\n", decodeAStr);
    char temp_info[size];
    for (int i = 0; i < size; i++)
    {
        temp_info[i] = decodeAStr[i];
    }
    // 再解析$
    int b_size = 0;
    char *decodeBStr = (char *)decodeCommon(temp_info, size, '$', &b_size);
    printf("decodeBStr:%s\n", decodeBStr);
    int res = atoi(decodeBStr);
    return res;
}

int main()
{
    int arr[] = {2, 3, 1, 6, 1, 10, 2, 5, 9, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int median = MedianNum(arr, n);
    printf("Median number is: %d\n", median);

    // char str[] = "103$104@105@2$106@107";
    // char *token;
    // char delimiters[] = "@";

    // token = strtok(str, delimiters);
    // while (token != NULL)
    // {
    //     printf("%s\n", token);
    //     token = strtok(NULL, delimiters);
    // }

    char str[] = "103$104@105@2$106@107";
    char str1[] = "11@2$3@14";
    int res = PhoneInfoDecode3(str);
    printf("res:%d\n", res);
    res = PhoneInfoDecode3(str1);
    printf("res:%d\n", res);

    return 0;
}