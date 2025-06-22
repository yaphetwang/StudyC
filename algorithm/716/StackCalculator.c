#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_NUM 20
#define STACK_CAP 32
#define CAL_LEN 4

int stacks[STACK_NUM][STACK_CAP] = {0};
int stacks_idx[STACK_NUM] = {0};

/*
模拟计算器
a-t 20个栈， 0-19
*/

void PSH(int *stack, int *stacks_idx, int stack_num, int num)
{
    if (stacks_idx[stack_num] > 32)
    {
        return;
    }

    stack[stacks_idx[stack_num]] = num;
    stacks_idx[stack_num]++;
}

void POP(int *stack, int *stacks_idx, int stack_num)
{
    if (stacks_idx[stack_num] == 0)
    {
        return;
    }

    stack[stacks_idx[stack_num] - 1] = 0;
    stacks_idx[stack_num]--;
}

void ADD(int *stack_a, int *stack_b, int *stacks_idx, int stack_num_a, int stack_num_b)
{
    int add = stack_a[stacks_idx[stack_num_a] - 1] + stack_b[stacks_idx[stack_num_b] - 1];
    add = add >= 1024 ? add % 1024 : add;
    stack_a[stacks_idx[stack_num_a] - 1] = add;
}

void MUL(int *stack_a, int *stack_b, int *stacks_idx, int stack_num_a, int stack_num_b)
{
    // printf("stack_num_a:%d,idx:%d,num:%d\n", stack_num_a, stacks_idx[stack_num_a], stack_a[stacks_idx[stack_num_a] - 1]);
    // printf("stack_num_b:%d,idx:%d,num:%d\n", stack_num_b, stacks_idx[stack_num_b], stack_b[stacks_idx[stack_num_b] - 1]);
    int mul = stack_a[stacks_idx[stack_num_a] - 1] * stack_b[stacks_idx[stack_num_b] - 1];
    mul = mul >= 1024 ? mul % 1024 : mul;
    stack_a[stacks_idx[stack_num_a] - 1] = mul;
}

void DIV(int *stack_a, int *stack_b, int *stacks_idx, int stack_num_a, int stack_num_b)
{
    int num_a = stack_a[stacks_idx[stack_num_a] - 1];
    int num_b = stack_b[stacks_idx[stack_num_b] - 1];
    int div_a = num_a / num_b;
    int div_b = num_a % num_b;
    stack_a[stacks_idx[stack_num_a] - 1] = div_a;
    stack_b[stacks_idx[stack_num_b] - 1] = div_b;
}

static int *StackCalculator(char **instructions, size_t instructionsSize, size_t *returnSize)
{
    for (int i = 0; i < instructionsSize; i++)
    {
        char cal[CAL_LEN];
        char stack_a;
        char stack_b;
        sscanf(instructions[i], "%s %c %c", cal, &stack_a, &stack_b);
        int stack_idx_a = stack_a;
        int stack_idx_b = stack_b;
        if (!strcmp(cal, "PSH"))
        {
            // 重新来一次读取 num
            int num;
            sscanf(instructions[i], "%s %c %d", cal, &stack_a, &num);
            PSH(stacks[stack_idx_a - 97], stacks_idx, stack_idx_a - 97, num);
        }

        if (!strcmp(cal, "POP"))
        {
            POP(stacks[stack_idx_a - 97], stacks_idx, stack_idx_a - 97);
        }

        if (!strcmp(cal, "ADD"))
        {
            ADD(stacks[stack_idx_a - 97], stacks[stack_idx_b - 97], stacks_idx, stack_idx_a - 97, stack_idx_b - 97);
        }

        if (!strcmp(cal, "MUL"))
        {
            MUL(stacks[stack_idx_a - 97], stacks[stack_idx_b - 97], stacks_idx, stack_idx_a - 97, stack_idx_b - 97);
        }

        if (!strcmp(cal, "DIV"))
        {
            DIV(stacks[stack_idx_a - 97], stacks[stack_idx_b - 97], stacks_idx, stack_idx_a - 97, stack_idx_b - 97);
        }
    }

    int res_idx = 0;
    int *res = (int *)malloc(sizeof(int) * STACK_NUM);
    memset(res, 0, sizeof(int) * STACK_NUM);

    for (int i = 0; i < STACK_NUM; i++)
    {
        int idx = stacks_idx[i];
        int num = idx == 0 ? -1 : stacks[i][idx - 1];
        res[res_idx++] = num;
    }

    *returnSize = res_idx;
    return res;
}

int main()
{
    char ss[] = "PSH t 400";
    char cal[CAL_LEN];
    char stack_idx_c;
    char num_c;
    // sscanf_s(ss, "%s %c %c", cal, (unsigned)sizeof(cal), &stack_idx_c, 1, &num_c, 1); // 不对，要按照ss内容的实际格式来格式化
    sscanf_s(ss, "%s %c %c", cal, strlen(cal), &stack_idx_c, 1, &num_c, 1); //  strlen(cal) 可以吗？？？
    printf("%s\n", cal);
    printf("%c\n", stack_idx_c);
    printf("%c\n", num_c);
    if (strcmp(cal, "PSH") == 0)
    {
        int stack_idx = stack_idx_c;
        int num;
        sscanf_s(ss, "%s %c %d", cal, (unsigned)sizeof(cal), &stack_idx_c, 1, &num);
        printf("%s\n", cal);
        printf("%d\n", stack_idx);
        printf("%d\n", num);
    }
    printf("%s\n", "test end");

    char *cals[7] = {
        "PSH a 8",
        "PSH d 3",
        "PSH c 3",
        "ADD a c",
        "DIV a c",
        "MUL d c",
        "POP c",
    };

    // char *cals[6] = {
    //     "PSH a 9",
    //     "PSH t 400",
    //     "MUL t a",
    //     "DIV t a",
    //     "PSH a 30",
    //     "MUL a t",
    // };

    size_t returnSize;
    size_t calsSize = sizeof(cals) / sizeof(cals[0]);
    printf("calsSize:%d\n", calsSize);
    int *res = (int *)StackCalculator(cals, calsSize, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d", res[i]);
        printf("%s", i == returnSize - 1 ? " " : ",");
    }
}