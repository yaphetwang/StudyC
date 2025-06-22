#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
二进制编辑器
*/

#define BINARY_LEN 1000
int len = 0;
int idx = 0;

void cmd_0(char *stack)
{
    if (idx == 0)
    {
        return;
    }
    if (idx == 1 && stack[idx - 1] == '0')
    {
        return;
    }

    stack[idx++] = '0';
    len++;
}

void cmd_1(char *stack)
{
    if (idx == 1 && stack[idx - 1] == '0')
    {
        stack[idx - 1] = '1';
        return;
    }

    stack[idx++] = '1';
    len++;
}

void cmd_B(char *stack)
{
    if (idx == 0)
    {
        return;
    }

    // 删除并整体左移
    for (int i = idx - 1; i < len - 1; i++)
    {
        stack[i] = stack[i + 1];
    }

    len--;
    idx--;

    // 判断是否有前导0
    int index = 0;
    if (stack[0] == '0')
    {
        for (int i = 0; i < len; i++)
        {
            if (stack[i] != 0)
            {
                index = i;
                break;
            }
        }
    }

    if (index > 0)
    {
        len -= index;
        for (int i = index; i < len - 1; i++)
        {
            stack[i - index] = stack[i];
        }

        idx = 0;
        return;
    }
    else
    {
        len = 0;
        idx = 0;
    }
}

void cmd_L(char *stack)
{
    if (idx == 0)
    {
        return;
    }

    idx--;
}

void cmd_R(char *stack)
{
    if (idx == len)
    {
        return;
    }

    idx++;
}

static char *BinaryEditor(const char *inputStr, const char *cmds)
{
    int str_len = strlen(inputStr);
    int cmd_len = strlen(cmds);

    char *stack = (char *)malloc(sizeof(char) * BINARY_LEN);
    memset(stack, 0, sizeof(char) * BINARY_LEN);

    for (int i = 0; i < str_len; i++)
    {
        stack[idx++] = inputStr[i];
    }

    len = idx;

    for (int c = 0; c < cmd_len; c++)
    {
        if (cmds[c] == '0')
        {
            cmd_0(stack);
            printf("%s\n", "cmd 0");
            printf("idx:%d\n", idx);
            printf("len:%d\n", len);
            printf("stack:%s\n", stack);
        }

        if (cmds[c] == '1')
        {
            cmd_1(stack);
            printf("%s\n", "cmd 1");
            printf("idx:%d\n", idx);
            printf("len:%d\n", len);
            printf("stack:%s\n", stack);
        }

        if (cmds[c] == 'B')
        {
            cmd_B(stack);
            printf("%s\n", "cmd B");
            printf("idx:%d\n", idx);
            printf("len:%d\n", len);
            printf("stack:%s\n", stack);
        }

        if (cmds[c] == 'L')
        {
            cmd_L(stack);
            printf("%s\n", "cmd L");
            printf("idx:%d\n", idx);
            printf("len:%d\n", len);
            printf("stack:%s\n", stack);
        }

        if (cmds[c] == 'R')
        {
            cmd_R(stack);
            printf("%s\n", "cmd R");
            printf("idx:%d\n", idx);
            printf("len:%d\n", len);
            printf("stack:%s\n", stack);
        }
    }

    printf("%s\n", "cmd_end========");
    printf("len:%d\n", len);
    printf("stack:%s\n", stack);

    char *res = (char *)malloc(sizeof(char) * BINARY_LEN);
    memset(res, 0, sizeof(char) * BINARY_LEN);
    if (len == 0)
    {
        return res;
    }

    for (int i = 0; i < len; i++)
    {
        res[i] = stack[i];
    }

    return res;
}

int main()
{
    char b_str[] = "10";
    // char cmd_str[] = "0LLB0R1";
    // char *res = (char *)BinaryEditor(b_str, cmd_str);
    // printf("%s\n", res);

    char cmd_str2[] = "0LLBB1RRRBB";
    char *res2 = (char *)BinaryEditor(b_str, cmd_str2);
    printf("%s\n", res2);
}