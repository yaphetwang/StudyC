#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
LCR 037. 行星碰撞

给定一个整数数组 asteroids，表示在同一行的小行星。

对于数组中的每一个元素，其绝对值表示小行星的大小，
正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。
每一颗小行星以相同的速度移动。

找出碰撞后剩下的所有小行星。
碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。
两颗移动方向相同的行星，永远不会发生碰撞。

输入：asteroids = [5,10,-5]
输出：[5,10]
解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。
*/

/**
 * 精简版 栈 解法
 */
int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize)
{
    int *stack = (int *)malloc(asteroidsSize * sizeof(int));
    memset(stack, 0, asteroidsSize * sizeof(int));
    int top = 0;

    for (int i = 0; i < asteroidsSize; i++)
    {
        bool live = true;
        /* 通过while循环条件 精确控制符合条件的比较 */
        while (live && top > 0 && stack[top - 1] > 0 && asteroids[i] < 0)
        {
            live = stack[top - 1] < -asteroids[i];
            if (stack[top - 1] <= -asteroids[i])
            {
                top--;
            }
        }

        if (live)
        {
            stack[top++] = asteroids[i];
        }
    }

    *returnSize = top;

    return stack;
}

/**
 * 笨拙版本  栈 解法
 */
int *asteroidCollision2(int *asteroids, int asteroidsSize, int *returnSize)
{
    int index = 0;
    int *res = (int *)malloc(sizeof(int) * asteroidsSize);
    memset(res, 0, sizeof(int) * asteroidsSize);

    int topIndex = -1; // 栈顶坐标初始值为-1
    int *stack = (int *)malloc(asteroidsSize * sizeof(int));
    memset(stack, 0, sizeof(int) * asteroidsSize);

    for (int i = 0; i < asteroidsSize; i++)
    {
        if (topIndex == -1)
        {
            /* 第一个直接放进去 */
            stack[++topIndex] = asteroids[i];
            continue;
        }

        if (stack[topIndex] > 0 && asteroids[i] < 0)
        {
            /* 一个大于0，一个小于0 才会撞*/
            if (abs(stack[topIndex]) > abs(asteroids[i]))
            {
                continue;
            }
            else if (abs(stack[topIndex]) == abs(asteroids[i]))
            {
                // stack[topIndex] = 0;
                topIndex--;
            }
            else
            {
                // stack[topIndex] = 0;
                topIndex--;
                if (topIndex == -1)
                {
                    stack[++topIndex] = asteroids[i];
                    continue;
                }
                while (topIndex >= 0)
                {
                    if (stack[topIndex] > 0 && asteroids[i] < 0)
                    {
                        if (abs(stack[topIndex]) > abs(asteroids[i]))
                        {
                            // 只要asteroids[i] 爆炸就break
                            break;
                        }
                        else if (abs(stack[topIndex]) == abs(asteroids[i]))
                        {
                            // stack[topIndex] = 0;
                            topIndex--;
                            break;
                        }
                        else
                        {
                            // 后面根据栈顶坐标取值，不需要重置初始值
                            // stack[topIndex] = 0;
                            topIndex--;
                            if (topIndex == -1)
                            {
                                stack[++topIndex] = asteroids[i];
                                break;
                            }
                        }
                    }
                    else
                    {
                        stack[++topIndex] = asteroids[i];
                        break;
                    }
                }
            }
        }
        else
        {
            stack[++topIndex] = asteroids[i];
        }
    }

    // topIndex初始值为-1，所以topIndex+1才是栈的有效长度
    for (int i = 0; i < topIndex + 1; i++)
    {
        if (stack[i] != 0)
        {
            res[index++] = stack[i];
        }
    }

    *returnSize = index;

    return res;
}

int main()
{
    int asteroids[] = {5, 10, -5};
    int asteroids1[] = {8, -8};
    int asteroids2[] = {10, 2, -5};
    int asteroids3[] = {-2, -1, 1, 2};
    int asteroidsSize = sizeof(asteroids) / sizeof(asteroids[0]);
    int *returnSize = malloc(sizeof(int));
    int *result = (int *)asteroidCollision2(asteroids, asteroidsSize, returnSize);
    for (int i = 0; i < (*returnSize); i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
    return 0;
}